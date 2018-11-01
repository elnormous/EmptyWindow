//
//  EmptyWindow
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include <cstdint>

namespace emptywindow
{
    class Application
    {
    public:
        Application();
        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;
    };
}

#endif
