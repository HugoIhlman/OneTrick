#include "cGame.h"

#include <string>
#include <windows.h>

#include "cCameraController.h"

cGame::cGame()
{
    m_model = new cModel("Asset/Textures/DOHA.tga", "Asset/Models/DOHA.txt");
    m_cube = new cModel("Asset/Textures/snurran.tga", "Asset/Models/cube.txt" );
    std::vector<cModel*> models = {m_model, m_cube};
    m_logger = std::make_shared<cLogger>(cLogger::LogLevel::Info);
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
    m_cameraController = new cCameraController(m_camera, m_logger);
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
    float rotation = 0.0f;
    while (m_isRunning)
    {
        rotation -= 0.016f *40.0f;
        if (rotation < 0.0f)
            rotation += 360.0f;
        m_renderer->render(m_camera, m_light);
        m_model->setRotation(OT::cVector3f(0.0f, 1.0f, 0.0f), rotation);
        m_cameraController->update();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                m_isRunning = false;
                break;
            }
            if (event.type == SDL_EVENT_WINDOW_RESIZED)
            {
                SDL_GetWindowSizeInPixels(m_display->getWindow(), &OT::SCREEN_WIDTH, &OT::SCREEN_HEIGHT);
                m_renderer->resize();
            }
            if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.key == SDLK_ESCAPE)
                {
                    m_mouseHidden = !m_mouseHidden;
                    SDL_SetWindowRelativeMouseMode(m_display->getWindow(), m_mouseHidden);
                }
                if (event.key.key == SDLK_F11)
                {
                    m_fullscreen = !m_fullscreen;
                    SDL_SetWindowFullscreen(m_display->getWindow(), m_fullscreen);
                    SDL_GetWindowSizeInPixels(m_display->getWindow(), &OT::SCREEN_WIDTH, &OT::SCREEN_HEIGHT);
                    m_renderer->resize();
                }
            }
        }
        Sleep(1);
    }
}
