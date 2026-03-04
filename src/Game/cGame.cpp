#include "cGame.h"

#include <windows.h>

cGame::cGame()
{
    char textureFileName[256];
    m_logger = std::make_unique<cLogger>(cLogger::LogLevel::Info);
    m_renderer = std::make_unique<cRenderer>();
    m_display = std::make_unique<cWindow>(*m_renderer);
    m_model = new cModel;
    strcpy_s(textureFileName, "Asset/Textures/cat.tga");
    m_model->initialize(m_renderer->getRsc().device, m_renderer->getRsc().context, textureFileName);
    m_logger->log(cLogger::LogLevel::Info, "Game initialized");
    m_camera = new cCamera;
    m_camera->setPosition(0.0f,0.0f,-5);
}

cGame::~cGame()
{
    m_logger->log(cLogger::LogLevel::Info, "Game deinitializing");
    m_model = nullptr;
    m_camera = nullptr;
}

void cGame::run()
{
    MSG msg{};
    while (m_isRunning)
    {
        m_camera->render();
        m_renderer->render(m_model, m_camera);
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
