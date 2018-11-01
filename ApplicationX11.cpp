//
//  EmptyWindow
//

#include <iostream>
#include <stdexcept>
#include <X11/Xutil.h>
#include "ApplicationX11.hpp"

namespace emptywindow
{
    ApplicationX11::ApplicationX11()
    {
        if (!XInitThreads())
            throw std::runtime_error("Failed to initialize thread support");

        display = XOpenDisplay(nullptr);

        if (!display)
            throw std::runtime_error("Failed to open display");

        Screen* screen = XDefaultScreenOfDisplay(display);
        int screenIndex = XScreenNumberOfScreen(screen);
        visual = DefaultVisual(display, screenIndex);
        depth = DefaultDepth(display, screenIndex);

        uint32_t width = static_cast<uint32_t>(XWidthOfScreen(screen) * 0.6F);
        uint32_t height = static_cast<uint32_t>(XHeightOfScreen(screen) * 0.6F);

        XSetWindowAttributes swa;
        swa.background_pixel = XWhitePixel(display, screenIndex);
        swa.border_pixel = 0;
        swa.event_mask = KeyPressMask | ExposureMask | StructureNotifyMask;

        window = XCreateWindow(display,
            RootWindow(display, screenIndex),
            0, 0, width, height,
            0, depth, InputOutput, visual,
            CWBorderPixel | CWBackPixel | CWEventMask, &swa);

        XSetStandardProperties(display,
            window, "EmptyWindow", "EmptyWindow", None,
            nullptr, 0, nullptr);

        XMapWindow(display, window);

        protocolsAtom = XInternAtom(display, "WM_PROTOCOLS", False);
        deleteAtom = XInternAtom(display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(display, window, &deleteAtom, 1);
    }

    ApplicationX11::~ApplicationX11()
    {
        if (display)
        {
            if (window) XDestroyWindow(display, window);

            XCloseDisplay(display);
        }
    }

    void ApplicationX11::run()
    {
        int running = 1;
        XEvent event;

        while (running)
        {
            while (XPending(display))
            {
                XNextEvent(display, &event);

                switch (event.type)
                {
                    case ClientMessage:
                        if (event.xclient.message_type == protocolsAtom &&
                            static_cast<Atom>(event.xclient.data.l[0]) == deleteAtom)
                            running = 0;
                        break;
                    case KeyPress:
                        break;
                    case Expose:
                        break;
                    case ConfigureNotify:
                        break;
                }
            }
        }
    }
}

int main()
{
    try
    {
        emptywindow::ApplicationX11 application;
        application.run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        return EXIT_FAILURE;
    }
}
