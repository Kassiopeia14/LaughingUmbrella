#include <iostream>
#include "../modHTTP/POST_HTTPRequest.h"
#include "../modWindows/Application.h"
#include "../modWindows/MainWindow.h"

#include "UmbrellaPainter.h"
#include "../modMessageBusClient/MessageBusClient.h"
#include "WorldPresenter.h"

int APIENTRY WinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    LPSTR commandLine,
    int showCommand)
{
    std::atomic<bool> running(true);

    WorldPresenter worldPresenter;

    worldPresenter.setEpoch(0);

    UmbrellaPainter painter(worldPresenter);

    Application application(instance);
    ATOM classAtom = application.registerMainWindowClass(MainWindow<UmbrellaPainter>::getWindowProcedure());

    MainWindow<UmbrellaPainter> mainWindow(instance, running);

    mainWindow.setPainter(painter);

    HWND mainWindowHandle = mainWindow.getHandle();

    painter.initialize(mainWindowHandle);

    mainWindow.show(showCommand);

    mainWindow.update();

    return application.run([&]() -> void
        {
            painter.draw();
            mainWindow.invalidate();
        });
}