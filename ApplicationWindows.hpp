//
//  EmptyWindow
//

#ifndef APPLICATIONWINDOWS_HPP
#define APPLICATIONWINDOWS_HPP

#include <Windows.h>
#include "Application.hpp"

namespace emptywindow
{
    class ApplicationWindows: public Application
    {
    public:
        ApplicationWindows();
        ~ApplicationWindows();

        void run();

    private:
        ATOM windowClass = 0;
        HWND window = 0;
    };
}

#endif
