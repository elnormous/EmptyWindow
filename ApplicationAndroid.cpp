//
//  EmptyWindow
//

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "ApplicationAndroid.hpp"

std::unique_ptr<emptywindow::ApplicationAndroid> application;

extern "C" JNIEXPORT jint JNIEXPORT JNI_OnLoad(JavaVM* javaVM, void*)
{
    try
    {
        application.reset(new emptywindow::ApplicationAndroid(javaVM));
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT void JNIEXPORT JNI_OnUnload(JavaVM*, void*)
{
    application.reset();
}

extern "C" JNIEXPORT void JNICALL Java_lv_elviss_softwarerenderer_DemoLibJNIWrapper_init(JNIEnv*, jclass, jint width, jint height)
{
    try
    {
        application->init(width, height);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

extern "C" JNIEXPORT void JNICALL Java_lv_elviss_softwarerenderer_DemoLibJNIWrapper_onSizeChanged(JNIEnv*, jclass, jint width, jint height)
{
    try
    {
        application->onSizeChanged(width, height);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

extern "C" JNIEXPORT void JNICALL Java_lv_elviss_softwarerenderer_DemoLibJNIWrapper_onDraw(JNIEnv*, jclass, jobject bitmap)
{
    try
    {
        application->onDraw(bitmap);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

namespace emptywindow
{
    ApplicationAndroid::ApplicationAndroid(JavaVM* initJavaVM):
        javaVM(initJavaVM)
    {
    }

    ApplicationAndroid::~ApplicationAndroid()
    {
    }

    void ApplicationAndroid::init(jint initWidth, jint initHeight)
    {
    }

    void ApplicationAndroid::onDraw(jobject bitmap)
    {
    }

    void ApplicationAndroid::onSizeChanged(jint newWidth, jint newHeight)
    {
    }
}
