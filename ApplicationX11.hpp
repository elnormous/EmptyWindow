//
//  EmptyWindow
//

#ifndef APPLICATIONX11_HPP
#define APPLICATIONX11_HPP

#include <X11/Xlib.h>
#include "Application.hpp"

namespace emptywindow
{
    class ApplicationX11: public Application
    {
    public:
        ApplicationX11();
        ~ApplicationX11();

        void run();

    private:
        Visual* visual;
        int depth;
        Display* display;
        ::Window window;
        Atom protocolsAtom;
        Atom deleteAtom;
    };
}

#endif
