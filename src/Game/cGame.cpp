#include "cGame.h"

#include <windows.h>

cGame::cGame()
{
    m_model = new cModel("Asset/Textures/DOHA.tga", "Asset/Models/DOHA.txt");
    m_cube = new cModel("Asset/Textures/snurran.tga", "Asset/Models/cube.txt" );
    std::vector<cModel*> models = {m_model, m_cube};
    m_logger = std::make_unique<cLogger>(cLogger::LogLevel::Info);
    m_renderer = std::make_unique<cRenderer>(models);
    m_display = std::make_unique<cWindow>(*m_renderer);
    m_model->setPosition(OT::cVector3f(0.0f,0.0f, 5.0f));
    m_model->setScale(OT::cVector3f(7.0f, 7.0f, 7.0f));
    m_cube->setPosition(OT::cVector3f(0.0f,-1.5f, 5.0f));
    m_cube->setScale(OT::cVector3f(5.0f,1.0f,5.0f));
    m_cube->setRotation(OT::cVector3f(0.0f,1.0f,0.0f), 45.0f);
    m_logger->log(cLogger::LogLevel::Info, "Game initialized");
    m_light = new cLight;
    m_light->setDiffuseColor(1.0f,1.0f,1.0f,1.0f);
    m_light->setDirection(0.2f,-1.0f,1.0f);
    m_camera = new cCamera;
    m_camera->setPosition(0.0f,0.0f,0.0f);
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
    float rotation = 0.0f;
    while (m_isRunning)
    {
        rotation -= 0.016f *40.0f;
        if (rotation < 0.0f)
            rotation += 360.0f;
        m_renderer->render(m_camera, m_light);
        m_model->setRotation(OT::cVector3f(0.0f, 1.0f, 0.0f), rotation);
        
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
