#include "cGame.h"

#include <windows.h>

cGame::cGame()
{
    m_logger = std::make_unique<cLogger>(cLogger::LogLevel::Info);
    m_renderer = std::make_unique<cRenderer>();
    m_display = std::make_unique<cWindow>(*m_renderer);
    
    m_logger->log(cLogger::LogLevel::Info, "Game initialized");
}

cGame::~cGame()
{
    m_logger->log(cLogger::LogLevel::Info, "Game deinitializing");
}

void cGame::run()
{
    MSG msg{};
    while (m_isRunning)
    {
        m_renderer->render();
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
