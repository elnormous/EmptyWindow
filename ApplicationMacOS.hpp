//
//  EmptyWindow
//

#ifndef APPLICATIONMACOS_H
#define APPLICATIONMACOS_H

#import <Cocoa/Cocoa.h>
#include "Application.hpp"

namespace emptywindow
{
    class ApplicationMacOS: public Application
    {
    public:
        ApplicationMacOS();
        virtual ~ApplicationMacOS();

        void run();

    private:
        NSAutoreleasePool* pool = nil;

        NSScreen* screen = nil;
        NSWindow* window = nil;
        NSView* content = nil;
        NSObject<NSWindowDelegate>* windowDelegate = nil;
    };
}

#endif
