#include "cGame.h"

#include <windows.h>

cGame::cGame()
{
    m_display = new cWindow();
}

cGame::~cGame()
{
    delete m_display;
}

void cGame::run()
{
    MSG msg{};
    while (m_isRunning)
    {
        while (PeekMessage(&msg, NULL, 0,0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                m_isRunning = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Sleep(1);
    }
}
