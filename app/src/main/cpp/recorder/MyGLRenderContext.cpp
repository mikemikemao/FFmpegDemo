//
// Created by pirate on 2022/3/12.
//

#include "MyGLRenderContext.h"
MyGLRenderContext* MyGLRenderContext::m_pContext = nullptr;

MyGLRenderContext::MyGLRenderContext()
{
    m_pCurSample = new TriangleSample();
    m_pBeforeSample = nullptr;
}

MyGLRenderContext::~MyGLRenderContext()
{
    if (m_pCurSample)
    {
        delete m_pCurSample;
        m_pCurSample = nullptr;
    }

    if (m_pBeforeSample)
    {
        delete m_pBeforeSample;
        m_pBeforeSample = nullptr;
    }
}

MyGLRenderContext *MyGLRenderContext::GetInstance()
{
    LOGCATE("MyGLRenderContext::GetInstance");
    if (m_pContext == nullptr)
    {
        m_pContext = new MyGLRenderContext();
    }
    return m_pContext;
}

void MyGLRenderContext::DestroyInstance()
{
    LOGCATE("MyGLRenderContext::DestroyInstance");
    if (m_pContext)
    {
        delete m_pContext;
        m_pContext = nullptr;
    }
}

void MyGLRenderContext::OnSurfaceCreated()
{
    LOGCATE("MyGLRenderContext::OnSurfaceCreated");
    glClearColor(1.0f,1.0f,1.0f, 1.0f);
}

void MyGLRenderContext::OnSurfaceChanged(int width, int height)
{
    LOGCATE("MyGLRenderContext::OnSurfaceChanged [w, h] = [%d, %d]", width, height);
    glViewport(0, 0, width, height);
    m_ScreenW = width;
    m_ScreenH = height;
}

void MyGLRenderContext::OnDrawFrame()
{
    LOGCATE("MyGLRenderContext::OnDrawFrame");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if (m_pBeforeSample)
    {
        m_pBeforeSample->Destroy();
        delete m_pBeforeSample;
        m_pBeforeSample = nullptr;
    }

    if (m_pCurSample)
    {
        m_pCurSample->Init();
        m_pCurSample->Draw(m_ScreenW, m_ScreenH);
    }
}


void MyGLRenderContext::SetParamsInt(int paramType, int value0, int value1) {
    LOGCATE("MyGLRenderContext::SetParamsInt paramType = %d, value0 = %d, value1 = %d", paramType,
            value0, value1);
    if (paramType == SAMPLE_TYPE) {
        m_pBeforeSample = m_pCurSample;

        LOGCATE("MyGLRenderContext::SetParamsInt 0 m_pBeforeSample = %p", m_pBeforeSample);
        switch (value0) {
            case SAMPLE_TYPE_KEY_TRIANGLE:
                m_pCurSample = new TriangleSample();
                break;
            case SAMPLE_TYPE_KEY_TEXTURE_MAP:
                m_pCurSample = new TextureMapSample();
                break;
            case SAMPLE_TYPE_KEY_YUV_TEXTURE_MAP :
                m_pCurSample = new NV21TextureMapSample();
                break;
            case SAMPLE_TYPE_KEY_VAO :
                m_pCurSample = new VaoSample();
                break;
            case SAMPLE_TYPE_KEY_FBO :
                m_pCurSample = new FBOSample();
                break;
            default:
                m_pCurSample = nullptr;
                break;
        }
        LOGCATE("MyGLRenderContext::SetParamsInt m_pBeforeSample = %p, m_pCurSample=%p", m_pBeforeSample, m_pCurSample);
    }

}



void MyGLRenderContext::SetImageData(int format, int width, int height, uint8_t *pData)
{
    LOGCATE("MyGLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p", format, width, height, pData);
    NativeImage nativeImage;
    nativeImage.format = format;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = pData;

    switch (format)
    {
        case IMAGE_FORMAT_NV12:
        case IMAGE_FORMAT_NV21:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            break;
        case IMAGE_FORMAT_I420:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
            break;
        default:
            break;
    }

    if (m_pCurSample)
    {
        m_pCurSample->LoadImage(&nativeImage);
    }

}