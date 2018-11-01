//
//  EmptyWindow
//

#ifndef APPLICATIONIOS_H
#define APPLICATIONIOS_H

#import <UIKit/UIKit.h>
#include "Application.hpp"

namespace emptywindow
{
    class ApplicationIOS: public Application
    {
    public:
        ApplicationIOS();
        virtual ~ApplicationIOS();

        void createWindow();

        void run(int argc, char* argv[]);

    private:
        NSAutoreleasePool* pool = nil;

        UIScreen* screen = nil;
        UIWindow* window = nil;
        UIView* content = nil;
        UIViewController* viewController = nil;
    };
}

#endif
