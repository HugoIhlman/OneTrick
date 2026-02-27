#include "cGame.h"

#include <windows.h>

cGame::cGame()
{
    m_renderer = std::make_unique<cRenderer>();
    m_display = std::make_unique<cWindow>();
}

cGame::~cGame()
{
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
