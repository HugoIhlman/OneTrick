#pragma once
#include <memory>

#include "../Math/cVector3.h"

class cLogger;

class cCamera;

class cCameraController
{
public:
    cCameraController(cCamera* _camera, std::shared_ptr<cLogger> _logger);
    ~cCameraController();
    
    void update();
    
    void inputs();
    
    void look();
    
    void move();
    
private:
    OT::cVector3f inputDir;
    OT::cVector3f lookDir;
    OT::cVector3f moveDir;
    
    std::shared_ptr<cLogger> m_logger = {};
    
    cCamera* m_camera;
};
