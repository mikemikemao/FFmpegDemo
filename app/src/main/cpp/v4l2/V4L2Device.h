//
// Created by pirate on 2022/3/3.
//

#ifndef FFMPEGDEMO_V4L2DEVICE_H
#define FFMPEGDEMO_V4L2DEVICE_H
#include <linux/videodev2.h>
#include <string.h>
#include <sys/poll.h>
#include "LogUtil.h"
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <cstring>
#include <errno.h>
#include <cstdlib>
#include <cassert>
#include <vector>

using namespace std;
#ifndef V4L2DEVICE_BUF_COUNT
# define V4L2DEVICE_BUF_COUNT 5
#endif

#ifndef V4L2DEVICE_PIXEL_FORMAT
# warning V4L2DEVICE_PIXEL_FORMAT not defined, using default value (V4L2_PIX_FMT_NV21)
# define V4L2DEVICE_PIXEL_FORMAT V4L2_PIX_FMT_NV21
#endif

class V4L2Device {
public:
    struct Resolution {
        unsigned width;
        unsigned height;
    };
    class VBuffer {
    public:
        uint8_t *buf;
        uint32_t len;
        uint32_t pixFmt;
    private:
        VBuffer(): buf(NULL), len(0) {}
        ~VBuffer();
        bool map(int fd, unsigned offset, unsigned len);
        void unmap();
        friend class V4L2Device;
    };
    V4L2Device(const char *devNode = "/dev/video0");
    ~V4L2Device();
    const vector<V4L2Device::Resolution> & availableResolutions();
    V4L2Device::Resolution sensorResolution();
    bool setResolution(unsigned width, unsigned height);
    bool connect();
    bool disconnect();
    bool isConnected() const { return mFd >= 0; }
    bool setStreaming(bool enable);
    bool isStreaming() const { return mStreaming; }
    const V4L2Device::VBuffer *readLock();
    bool unlock(const VBuffer *buf);
private:
    bool iocStreamOff();
    void cleanup();
    bool setResolutionAndAllocateBuffers(unsigned width, unsigned height);
    bool iocSFmt(unsigned width, unsigned height);
    bool iocReqBufs(unsigned *count);
    bool iocQueryBuf(unsigned id, unsigned *offset, unsigned *len) ;
    bool queueBuffer(unsigned id);
    bool iocStreamOn();
    int  dequeueBuffer();
private:
    int mFd;
    bool mConnected;
    bool mStreaming;
    const char *mDevNode;
    struct v4l2_format mFormat;
    VBuffer mBuf[V4L2DEVICE_BUF_COUNT];
    vector<V4L2Device::Resolution> mAvailableResolutions;
    V4L2Device::Resolution mForcedResolution;
};


#endif //FFMPEGDEMO_V4L2DEVICE_H
