#include "cCameraController.h"

#include <string>
#include <SDL3/SDL_events.h>

#include "cCamera.h"
#include "cLogger.h"

cCameraController::cCameraController(cCamera* _camera, std::shared_ptr<cLogger> _logger)
{
    m_camera = _camera;
    m_logger = _logger;
}

cCameraController::~cCameraController()
{
}

void cCameraController::update()
{
    inputs();
    look();
    move();
}

void cCameraController::inputs()
{
    float x, y;
    const bool* keyState = SDL_GetKeyboardState(nullptr);
    SDL_GetRelativeMouseState(&x, &y);
    lookDir.x += (x * 1.0f / 60.0f) * 2;
    lookDir.y += (y * 1.0f / 60.0f) * 2;
    
    if (keyState[SDL_SCANCODE_W])
    {
        inputDir.y += 1;
    }   
    else if (keyState[SDL_SCANCODE_S])
    {
        inputDir.y -= 1;
    }
    else
    {
        inputDir.y = 0;
    }
    if (keyState[SDL_SCANCODE_A])
    {
        inputDir.x -= 1;
    }   
    else if (keyState[SDL_SCANCODE_D])
    {
        inputDir.x += 1;
    }
    else
    {
        inputDir.x = 0;
    }
    
    inputDir.normalize();
}

void cCameraController::look()
{
    m_camera->setRotation(lookDir);
}

void cCameraController::move()
{
    moveDir = m_camera->world.at() * inputDir.y + m_camera->world.left() * inputDir.x;
    //moveDir = moveDir.normalize();
    m_camera->setPosition((moveDir * 0.1f) + m_camera->world.pos());
}
