//
//  EmptyWindow
//

#ifndef APPLICATIONWINDOWS_H
#define APPLICATIONWINDOWS_H

#include <Windows.h>
#include "Application.hpp"

namespace emptywindow
{
    class ApplicationWindows: public Application
    {
    public:
        ApplicationWindows();
        virtual ~ApplicationWindows();

        void run();

    private:
        ATOM windowClass = 0;
        HWND window = 0;
    };
}

#endif
