#include "cGame.h"

#include <windows.h>

cGame::cGame()
{
    char textureFileName[128];
    char modelFileName[128];
    m_logger = std::make_unique<cLogger>(cLogger::LogLevel::Info);
    m_renderer = std::make_unique<cRenderer>();
    m_display = std::make_unique<cWindow>(*m_renderer);
    m_model = new cModel;
    strcpy_s(textureFileName, "Asset/Textures/DOHA.tga");
    strcpy_s(modelFileName, "Asset/Models/DOHA.txt");
    bool result = m_model->initialize(m_renderer->getRsc().device, m_renderer->getRsc().context, textureFileName, modelFileName);
    if (!result)
    {
        MessageBox(static_cast<HWND>(m_display->getHandle().winHandle), L"Could not initialize the model object.", L"Error", MB_OK);
    }
    m_logger->log(cLogger::LogLevel::Info, "Game initialized");
    m_light = new cLight;
    m_light->setDiffuseColor(1.0f,1.0f,1.0f,1.0f);
    m_light->setDirection(0.0f,0.0f,1.0f);
    m_camera = new cCamera;
    m_camera->setPosition(0.0f,0.0f,-1.0f);
}

cGame::~cGame()
{
    m_logger->log(cLogger::LogLevel::Info, "Game deinitializing");
    m_model = nullptr;
    m_camera = nullptr;
    m_light = nullptr;
}

void cGame::run()
{
    MSG msg{};
    while (m_isRunning)
    {
        m_renderer->render(m_model, m_camera, m_light);
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
