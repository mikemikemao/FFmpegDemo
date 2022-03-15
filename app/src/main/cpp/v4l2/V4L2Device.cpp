//
// Created by pirate on 2022/3/3.
//


#include "V4L2Device.h"

static inline int openFd(const char *path) {
    assert(path);
    int flags = O_RDWR;
    int fd = open(path, flags);
    LOGCATD("open %s = %d", path, fd);
    return fd;
}

static inline void closeFd(int *fd) {
    assert(fd);
    close(*fd);
    LOGCATD("close %d", *fd);
    *fd = -1;
}
/**************************************************************************************************
 *
 * 应用接口
 */

V4L2Device::V4L2Device(const char *devNode)
        : mFd(-1)
        , mConnected(false)
        , mStreaming(false)
        , mDevNode(devNode){
    memset(&mFormat, 0, sizeof(mFormat));
    mForcedResolution.width=0;
    mForcedResolution.height=0;
}

V4L2Device::~V4L2Device() {
    if(isStreaming()) {
        iocStreamOff();
    }
    cleanup();
}

/**
 * 获取可用的分辨率
 * @return
 */
const vector<V4L2Device::Resolution> & V4L2Device::availableResolutions() {
    if(!mAvailableResolutions.empty()) {
        return mAvailableResolutions;
    }
    if(mForcedResolution.width > 0 && mForcedResolution.height > 0) {
        LOGCATD("Using forced resolution: %ux%u", mForcedResolution.width, mForcedResolution.height);
        mAvailableResolutions.push_back(mForcedResolution);
    } else{
        int fd;
        bool fdNeedsClose = false;
        vector<V4L2Device::Resolution> formats;
        if(mFd >= 0) {
            fd = mFd;
        } else {
            fd = openFd(mDevNode);
            fdNeedsClose = true;
        }
        if(fd < 0) {
            LOGCATE("Could not open %s: %s (%d)", mDevNode, strerror(errno), errno);
            return mAvailableResolutions;
        }

        struct v4l2_frmsizeenum frmSize;
        frmSize.pixel_format = V4L2DEVICE_PIXEL_FORMAT;
        frmSize.index = 0;
        errno = 0;
        while(ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmSize) >= 0) {
            LOGCATD("%s: Found resolution: %dx%d", mDevNode, frmSize.discrete.width, frmSize.discrete.height);
            ++frmSize.index;
            mForcedResolution.width = frmSize.discrete.width;
            mForcedResolution.height = frmSize.discrete.height;
            mAvailableResolutions.push_back(mForcedResolution);
        }
        if(errno && errno != EINVAL) {
            LOGCATE("Get available formats: %s (%d)", strerror(errno), errno);
        }
        if(fdNeedsClose) {
            closeFd(&fd);
        }
    }
    return mAvailableResolutions;
}

/**
 * 获取最大的分辨率
 */
V4L2Device::Resolution V4L2Device::sensorResolution() {
    const vector<V4L2Device::Resolution> &formats = availableResolutions();
    V4L2Device::Resolution max = {0, 0};
    for(size_t i = 0; i < formats.size(); ++i) {
        if(formats[i].width > max.width)
            max.width = formats[i].width;
        if(formats[i].height > max.height)
            max.height = formats[i].height;
    }
    return max;
}


/**
 * 设置分辨率
 */
bool V4L2Device::setResolution(unsigned width, unsigned height) {
    if(mFormat.fmt.pix.width == width && mFormat.fmt.pix.height == height)
        return true;
    LOGCATD("New resolution: %dx%d", width, height);
    if(isConnected()) {
        disconnect();
        mFormat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        mFormat.fmt.pix.pixelformat = V4L2DEVICE_PIXEL_FORMAT;
        mFormat.fmt.pix.width = width;
        mFormat.fmt.pix.height = height;
        connect();
        return true;
    } else {
        mFormat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        mFormat.fmt.pix.pixelformat = V4L2DEVICE_PIXEL_FORMAT;
        mFormat.fmt.pix.width = width;
        mFormat.fmt.pix.height = height;
        return true;
    }
}



/**
 * 连接设备 分配内存 查询内存
 */
bool V4L2Device::connect() {
    if(isConnected())
        return true;

    mFd = openFd(mDevNode);
    if(mFd < 0) {
        LOGCATE("Could not open %s: %s (%d)", mDevNode, strerror(errno), errno);
        return false;
    }
    unsigned width;
    unsigned height;
    if(mFormat.type) {
        width = mFormat.fmt.pix.width;
        height = mFormat.fmt.pix.height;
    } else {
        auto resolutions = availableResolutions();
        if(resolutions.empty()) {
            LOGCATE("No available resolutions found, aborting");
            closeFd(&mFd);
            return false;
        }
        auto defaultRes = resolutions[0];
        width = resolutions[0].width;
        height = resolutions[0].height;
        LOGCATD("Using default resolution: %dx%d", defaultRes.width, defaultRes.height);
    }
    if(!setResolutionAndAllocateBuffers(width, height)) {
        LOGCATE("Could not set resolution");
        closeFd(&mFd);
        return false;
    }
    mConnected = true;
    return true;
}

/**
 * 断开连接
 */
bool V4L2Device::disconnect() {
    if(!isConnected())
        return false;
    setStreaming(false);
    cleanup();
    return true;
}

/**
 * 设置是否取流
 * @param enable
 * @return
 */
bool V4L2Device::setStreaming(bool enable) {
    if(enable == mStreaming)
        return true;

    if(!isConnected())
        return !enable;

    if(enable) {
        if(!iocStreamOn()) {
            LOGCATE("Could not start streaming: %s (%d)", strerror(errno), errno);
            return false;
        }
    } else {
        if(!iocStreamOff()) {
            LOGCATE("Could not stop streaming: %s (%d)", strerror(errno), errno);
            return false;
        }
    }
    mStreaming = enable;
    return true;
}


/**
 * 锁住并读取图像数据
 */
const V4L2Device::VBuffer * V4L2Device::readLock() {
    assert(isConnected());
    assert(isStreaming());
    int id = 0;
    //等待到数据
    if((id = dequeueBuffer()) < 0) {
        LOGCATE("Could not dequeue buffer: %s (%d)", strerror(errno), errno);
        return NULL;
    }
    auto buf = &mBuf[id];
    return buf;
}


/**
 * 解锁
 */
bool V4L2Device::unlock(const VBuffer *buf) {
    if(!buf)
        return false;

    for(unsigned i = 0; i <V4L2DEVICE_BUF_COUNT; ++i) {
        if(mBuf[i].buf == buf->buf) {
            if(!queueBuffer(i)) {
                LOGCATE("Could not queue buffer %d: %s (%d)", i, strerror(errno), errno);
                return false;
            }
            return true;
        }
    }
    return false;
}


/********************************************************************************************************
 * 中间层
 * @return
 */
bool V4L2Device::setResolutionAndAllocateBuffers(unsigned width, unsigned height) {
    assert(!mStreaming);

    for(int i = 0; i < V4L2DEVICE_BUF_COUNT; ++i) {
        mBuf[i].unmap();
    }

    if(!iocSFmt(width, height)) {
        LOGCATE("Could not set pixel format to %dx%d: %s (%d)", width, height, strerror(errno), errno);
        return false;
    }

    unsigned bufCount = V4L2DEVICE_BUF_COUNT;
    if(!iocReqBufs(&bufCount)) {
        LOGCATE("Could not request buffer: %s (%d)", strerror(errno), errno);
        return false;
    }

    unsigned bufLen[V4L2DEVICE_BUF_COUNT] = {0};

    for(unsigned i = 0; i < bufCount; ++i) {
        unsigned offset;
        if(!iocQueryBuf(i, &offset, &bufLen[i])) {
            LOGCATE("Could not query buffer %d: %s (%d)", i, strerror(errno), errno);
            return false;
        }

        if(!mBuf[i].map(mFd, offset, bufLen[i])) {
            LOGCATE("Could not allocate buffer %d (len = %d): %s (%d)", i, bufLen[i], strerror(errno), errno);
            while(i--) mBuf[i].unmap();
            return false;
        }

        if(!queueBuffer(i)) {
            LOGCATE("Could not queue buffer: %s (%d)", strerror(errno), errno);
            do mBuf[i].unmap(); while(i--);
            return false;
        }
    }
    mConnected = true;
    return true;
}
/********************************************************************************************************
 * 硬件交互层
 * @return
 */
/**
* 开启视频流
* @return
*/
bool V4L2Device::iocStreamOn() {
    assert(mFd >= 0);
    assert(mFormat.type);

    errno = 0;
    unsigned type = mFormat.type;
    if(ioctl(mFd, VIDIOC_STREAMON, &type) == 0) {
        mStreaming = true;
    } else {
        LOGCATE("%s: %s (%d)", __FUNCTION__, strerror(errno), errno);
    }
    return !errno;
}
/**
 * 关掉视频流
 * @return
 */
bool V4L2Device::iocStreamOff() {
    assert(mFd >= 0);
    assert(mFormat.type);
    errno = 0;
    unsigned type = mFormat.type;
    if(ioctl(mFd, VIDIOC_STREAMOFF, &type) == 0) {
        mStreaming = false;
    } else {
        LOGCATE("%s: %s (%d)", __FUNCTION__, strerror(errno), errno);
    }
    return !errno;
}


/**
 * Wait for a buffer to be ready
 */
int V4L2Device::dequeueBuffer() {
    assert(mFd >= 0);

    struct v4l2_buffer bufInfo;

    memset(&bufInfo, 0, sizeof(bufInfo));
    bufInfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    bufInfo.memory = V4L2_MEMORY_MMAP;
    bufInfo.index = 0;
    do {

    } while((errno = 0, ioctl(mFd, VIDIOC_DQBUF, &bufInfo)) < 0 && (errno == EINVAL || errno == EAGAIN));
    if(errno)
        return -1;
    return (int)bufInfo.index;
}

/**
 * unmap内存 关掉资源
 */
void V4L2Device::cleanup() {
    for(int i = 0; i < V4L2DEVICE_BUF_COUNT; ++i) {
        mBuf[i].unmap();
    }
    closeFd(&mFd);
    mConnected = false;
}

/**
 * 设置分辨率
 * @param width
 * @param height
 * @return
 */
bool V4L2Device::iocSFmt(unsigned width, unsigned height) {
    assert(mFd >= 0);
    assert(!mStreaming);

    struct v4l2_format format;
    memset(&format, 0, sizeof(format));

    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    format.fmt.pix.pixelformat = V4L2DEVICE_PIXEL_FORMAT;
    format.fmt.pix.width = width;
    format.fmt.pix.height = height;
    errno = 0;
    if(ioctl(mFd, VIDIOC_S_FMT, &format) == 0) {
        mFormat = format;
    } else {
        LOGCATE("%s(w=%u, h=%u): %s (%d)", __FUNCTION__, width, height, strerror(errno), errno);
    }
    return !errno;
}

bool V4L2Device::iocReqBufs(unsigned *count) {
    assert(mFd >= 0);
    assert(count);

    struct v4l2_requestbuffers bufRequest;
    memset(&bufRequest, 0, sizeof(bufRequest));

    bufRequest.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    bufRequest.memory = V4L2_MEMORY_MMAP;
    bufRequest.count = *count;

    errno = 0;
    if(ioctl(mFd, VIDIOC_REQBUFS, &bufRequest) == 0) {
        *count = bufRequest.count;
    } else {
        LOGCATE("%s(count=%u): %s (%d)", __FUNCTION__, *count, strerror(errno), errno);
    }

    return !errno;
}

bool V4L2Device::iocQueryBuf(unsigned id, unsigned *offset, unsigned *len) {
    assert(mFd >= 0);
    assert(offset);
    assert(len);

    struct v4l2_buffer bufInfo;
    memset(&bufInfo, 0, sizeof(bufInfo));

    bufInfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    bufInfo.memory = V4L2_MEMORY_MMAP;
    bufInfo.index = id;

    errno = 0;
    if(ioctl(mFd, VIDIOC_QUERYBUF, &bufInfo) == 0) {
        *offset = bufInfo.m.offset;
        *len = bufInfo.length;
    } else {
        LOGCATD("%s(id=%u): %s (%d)", __FUNCTION__, id, strerror(errno), errno);
    }

    return !errno;
}

bool V4L2Device::queueBuffer(unsigned id) {
    assert(mFd >= 0);

    struct v4l2_buffer bufInfo;
    memset(&bufInfo, 0, sizeof(bufInfo));
    bufInfo.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
    bufInfo.memory = V4L2_MEMORY_MMAP;
    bufInfo.index = id;

    if(ioctl(mFd, VIDIOC_QBUF, &bufInfo) < 0)
        return false;

    return true;
}


/******************************************************************************\
                              V4l2Device::VBuffer
\******************************************************************************/

/**
 * \class V4l2Device::VBuffer
 *
 * Video buffer abstraction.
 */

V4L2Device::VBuffer::~VBuffer() {
    if(buf) {
        LOGCATD("V4l2Device::VBuffer: Memory leak!");
        //abort();
    }
}

bool V4L2Device::VBuffer::map(int fd, unsigned offset, unsigned len) {
    assert(!this->buf);

    errno = 0;
    this->buf = (uint8_t*)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
    if(this->buf == MAP_FAILED) {
        return false;
    }
    memset(this->buf, 0, len);
    this->len = len;
    this->pixFmt = V4L2DEVICE_PIXEL_FORMAT;

    return true;
}

void V4L2Device::VBuffer::unmap() {
    if(buf) {
        munmap(buf, len);
        buf         = NULL;
        len         = 0;
    }
}
