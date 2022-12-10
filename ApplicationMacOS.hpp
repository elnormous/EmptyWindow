//
//  EmptyWindow
//

#ifndef APPLICATIONMACOS_HPP
#define APPLICATIONMACOS_HPP

#import <Cocoa/Cocoa.h>
#include "Application.hpp"

namespace emptywindow
{
    class ApplicationMacOS: public Application
    {
    public:
        ApplicationMacOS();
        ~ApplicationMacOS();

        void run();

    private:
        NSAutoreleasePool* pool = nil;

        NSObject<NSApplicationDelegate>* appDelegate = nil;
        NSScreen* screen = nil;
        NSWindow* window = nil;
        NSView* content = nil;
        NSObject<NSWindowDelegate>* windowDelegate = nil;
    };
}

#endif
