//
//  EmptyWindow
//

#include <iostream>
#include <stdexcept>
#include <Strsafe.h>
#include "ApplicationWindows.hpp"

namespace
{
    LRESULT CALLBACK windowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        emptywindow::ApplicationWindows* applicationWindows = (emptywindow::ApplicationWindows*)GetWindowLongPtr(window, GWLP_USERDATA);
        if (!applicationWindows) return DefWindowProcW(window, msg, wParam, lParam);

        switch (msg)
        {
            case WM_PAINT:
            {
                break;
            }

            case WM_SIZE:
            {
                break;
            }

            case WM_DESTROY:
            {
                PostQuitMessage(0);
                break;
            }
        }

        return DefWindowProcW(window, msg, wParam, lParam); 
    }

    const LPCWSTR WINDOW_CLASS_NAME = L"EmptyWindow";
}

namespace emptywindow
{
    ApplicationWindows::ApplicationWindows()
    {
        HINSTANCE instance = GetModuleHandleW(nullptr);

        WNDCLASSEXW wc;
        wc.cbSize = sizeof(wc);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = windowProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = instance;
        // Application icon should be the first resource
        //wc.hIcon = LoadIconW(instance, MAKEINTRESOURCEW(101));
        wc.hIcon = nullptr;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW);
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = WINDOW_CLASS_NAME;
        wc.hIconSm = nullptr;

        windowClass = RegisterClassExW(&wc);
        if (!windowClass)
            throw std::system_error{static_cast<int>(GetLastError()), std::system_category(), "Failed to register window class"};

        DWORD windowStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPSIBLINGS | WS_BORDER | WS_DLGFRAME | WS_THICKFRAME | WS_GROUP | WS_TABSTOP | WS_SIZEBOX | WS_MAXIMIZEBOX;
        DWORD windowExStyle = WS_EX_APPWINDOW;

        window = CreateWindowExW(windowExStyle, WINDOW_CLASS_NAME, L"EmptyWindow", windowStyle,
                                 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                 nullptr, nullptr, instance, nullptr);

        if (!window)
            throw std::system_error{static_cast<int>(GetLastError()), std::system_category(), "Failed to create window"};

        ShowWindow(window, SW_SHOW);
        SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)this);
    }

    ApplicationWindows::~ApplicationWindows()
    {
        if (window) DestroyWindow(window);
        if (windowClass) UnregisterClassW(WINDOW_CLASS_NAME, GetModuleHandleW(nullptr));
    }

    void ApplicationWindows::run()
    {
        MSG msg;
        for (;;)
        {
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT) return;
            }

            InvalidateRect(window, nullptr, FALSE);
        }
    }
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        emptywindow::ApplicationWindows application;
        application.run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (...)
    {
        return EXIT_FAILURE;
    }
}
