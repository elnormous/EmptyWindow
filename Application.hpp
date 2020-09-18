//
//  EmptyWindow
//

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <cstdint>

namespace emptywindow
{
    class Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(Application&&) = delete;
    };
}

#endif
