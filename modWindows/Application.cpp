#include "Application.h"

Application::Application(const HINSTANCE _instance) :
    instance(_instance)
{
}

Application::~Application()
{
}

ATOM Application::registerMainWindowClass(WNDPROC mainWindowProcedure)
{
    WNDCLASS windowClass;

    windowClass.style = 0;
    windowClass.lpfnWndProc = mainWindowProcedure;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = instance;
    windowClass.hIcon = LoadIcon((HINSTANCE)NULL,
        IDI_APPLICATION);
    windowClass.hCursor = LoadCursor((HINSTANCE)NULL,
        IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    windowClass.lpszMenuName = L"MainMenu";
    windowClass.lpszClassName = L"MainWindowClass";

    return RegisterClass(&windowClass);
}

WPARAM Application::run(std::function<void()> task)
{
    MSG msg = {};
    BOOL bRet;

    std::chrono::time_point<std::chrono::system_clock> begin = std::chrono::system_clock::now();

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            std::chrono::time_point<std::chrono::system_clock> checkPoint = std::chrono::system_clock::now();

            std::chrono::duration<double> duration = checkPoint - begin;

            //if (duration.count() > 1.0 / 2)
            {
                begin = checkPoint;

                task();
            }
            //else
            //{
            //    std::this_thread::sleep_for(std::chrono::microseconds(10));
            //}
        }
    }

    return msg.wParam;
}