#pragma once

#include <Windows.h>

template<class Painter>
class MainWindow
{
private:

    std::atomic<bool>& running;

    Painter* painter;

    PAINTSTRUCT paintData;

    HWND handle;

    static LRESULT CALLBACK mainWindowProcedure(
        HWND hwnd,
        UINT uMsg,
        WPARAM wParam,
        LPARAM lParam);

    HWND makeWindow(HINSTANCE applicationInstance);

    static void create(HWND hwnd, LPARAM lParam);

    static bool paint(HWND hwnd);

    static void close(HWND hwnd);

public:

    MainWindow(const HINSTANCE instance, std::atomic<bool>& _running);
    ~MainWindow();

    static WNDPROC getWindowProcedure();
    HWND getHandle() const;

    void setPainter(Painter& painter);

    void show(int showCommand);

    void update();

    void stopApplication();

    void paint();

    void invalidate();

};

template<class Painter>
HWND MainWindow<Painter>::makeWindow(HINSTANCE applicationInstance)
{
    RECT rect{
        .left = 0,
        .top = 0,
        .right = 800,
        .bottom = 800
    };

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

    HWND windowHandle = CreateWindow(L"MainWindowClass", L"BasicWindow",
        WS_OVERLAPPEDWINDOW, 600, 100,
        rect.right - rect.left, rect.bottom - rect.top, (HWND)NULL,
        (HMENU)NULL, applicationInstance, (LPVOID)this);

    return windowHandle;
}

template<class Painter>
void MainWindow<Painter>::create(HWND hwnd, LPARAM lParam)
{
    CREATESTRUCT* createData = (CREATESTRUCT*)lParam;

    MainWindow* window = (MainWindow*)createData->lpCreateParams;

    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
}

template<class Painter>
bool MainWindow<Painter>::paint(HWND hwnd)
{
    MainWindow* window = (MainWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    window->paint();
    return true;
}

template<class Painter>
void MainWindow<Painter>::close(HWND hwnd)
{
    MainWindow* window = (MainWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    window->stopApplication();

    PostQuitMessage(0);
}


template<class Painter>
MainWindow<Painter>::MainWindow(const HINSTANCE instance, std::atomic<bool>& _running):
    running(_running),
    paintData(),
    handle(makeWindow(instance))
{
}

template<class Painter>
MainWindow<Painter>::~MainWindow()
{
}

template<class Painter>
WNDPROC MainWindow<Painter>::getWindowProcedure()
{
    return (WNDPROC)mainWindowProcedure;
}

template<class Painter>
HWND MainWindow<Painter>::getHandle() const
{
    return handle;
}

template<class Painter>
void MainWindow<Painter>::setPainter(Painter& _painter)
{
    painter = &_painter;
}

template<class Painter>
void MainWindow<Painter>::show(int showCommand)
{
    ShowWindow(handle, showCommand);
}

template<class Painter>
void MainWindow<Painter>::update()
{
    UpdateWindow(handle);
}

template<class Painter>
void MainWindow<Painter>::stopApplication()
{
    running.store(false);
}

template<class Painter>
void MainWindow<Painter>::paint()
{
    HDC deviceContext = BeginPaint(handle, &paintData);
    if (painter)
    {
        painter->paint(deviceContext);
    }
    EndPaint(handle, &paintData);
}

template<class Painter>
void MainWindow<Painter>::invalidate()
{
    InvalidateRect(handle, 0, false);
}

template<class Painter>
LRESULT CALLBACK MainWindow<Painter>::mainWindowProcedure(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        create(hwnd, lParam);
        return 0;

    case WM_PAINT:
        paint(hwnd);
        return 0;

    case WM_SIZE:
        return 0;

    case WM_CLOSE:
        close(hwnd);
        return 0;

    case WM_DESTROY:
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


