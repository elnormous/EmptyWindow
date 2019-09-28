//
//  EmptyWindow
//

#ifndef APPLICATIONANDROID_H
#define APPLICATIONANDROID_H

#include <jni.h>
#include "Application.hpp"

namespace emptywindow
{
    class ApplicationAndroid: public Application
    {
    public:
        ApplicationAndroid(JavaVM* initJavaVM);
        ~ApplicationAndroid();

        void init(jint initWidth, jint initHeight);
        void onDraw(jobject bitmap);
        void onSizeChanged(jint newWidth, jint newHeight);

    private:
        JavaVM* javaVM;
    };
}

#endif
