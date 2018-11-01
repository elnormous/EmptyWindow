//
//  EmptyWindow
//

#include <iostream>
#include <stdexcept>
#include <string>
#include <Bitmap.h>
#include <Window.h>
#include "ApplicationHaiku.hpp"

namespace emptywindow
{
    class AppView: public BView
    {
    public:
        AppView(ApplicationHaiku& initApplication, const BRect& frame, const std::string& title):
            BView(frame, title.c_str(), B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_FRAME_EVENTS),
            application(initApplication)
        {
        }

        virtual void FrameResized(float, float) override
        {
        }

        virtual void Draw(BRect) override
        {
        }

    private:
        ApplicationHaiku& application;
    };

    ApplicationHaiku::ApplicationHaiku():
        BApplication("application/x-vnd.EmptyWindow")
    {
        BRect frame(100, 100, 100 + 640, 100 + 480);
        window = new BWindow(frame, "EmptyWindow", B_TITLED_WINDOW,
                             B_ASYNCHRONOUS_CONTROLS | B_QUIT_ON_WINDOW_CLOSE);

        BRect bounds = window->Bounds();

        view = new AppView(*this, bounds, "render");
        window->AddChild(view);

        bitmap = new BBitmap(bounds, 0, B_RGB32);

        window->Show();
        SetPulseRate(100000);
    }

    ApplicationHaiku::~ApplicationHaiku()
    {
    }

    void ApplicationHaiku::run()
    {
        Run();
    }

    void ApplicationHaiku::Pulse()
    {
    	if (window->Lock())
    	{
            view->Invalidate();
            window->Unlock();
    	}
    }
}

int main()
{
    try
    {
        emptywindow::ApplicationHaiku application;
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
