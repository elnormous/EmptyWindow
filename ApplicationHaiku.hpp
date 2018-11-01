//
//  EmptyWindow
//

#ifndef APPLICATIONHAIKU_H
#define APPLICATIONHAIKU_H

#include <Application.h>
#include "Application.hpp"

namespace emptywindow
{
    class AppWindow;
    class AppView;

    class ApplicationHaiku: public Application, public BApplication
    {
    public:
        ApplicationHaiku();
        virtual ~ApplicationHaiku();

        void run();

        virtual void Pulse() override;

    private:
        BWindow* window = nullptr;
        AppView* view = nullptr;
        BBitmap* bitmap = nullptr;
    };
}

#endif
