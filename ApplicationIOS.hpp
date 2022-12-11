//
//  EmptyWindow
//

#ifndef APPLICATIONIOS_HPP
#define APPLICATIONIOS_HPP

#import <UIKit/UIKit.h>
#include "Application.hpp"

namespace emptywindow
{
    class ApplicationIOS: public Application
    {
    public:
        ApplicationIOS();
        ~ApplicationIOS();

        void createWindow();

        void run(int argc, char* argv[]);

    private:
        NSAutoreleasePool* pool = nil;

        UIScreen* screen = nil;
        UIWindow* window = nil;
        UIView* content = nil;
    };
}

#endif
