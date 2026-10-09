#include "cCamera.h"

#include "../Math/cMatrix4x4.h"
#include "../Math/cVector3.h"
#include "../Math/cVector4.h"

cCamera::cCamera()
{
    m_posX = 0.f;
    m_posY = 0.f;
    m_posZ = 0.f;

    m_rotX = 0.f;
    m_rotY = 0.f;
    m_rotZ = 0.f;
}

cCamera::~cCamera()
{
}

void cCamera::render()
{
    OT::cVector3f up, position, at;

    up = {0.0f,1.0f,0.0f};

    position = {m_posX,m_posY,m_posZ};

    at = {0.0f,0.0f,1.0f};
    
    world = rotation * translation;

    viewMatrix = world;
    viewMatrix.invert();
}

void cCamera::setPosition(OT::cVector3f _trans)
{
    translation.translate(_trans);
}

void cCamera::setRotation(OT::cVector3f _rot)
{
    rotation.rotate(OT::cVector3f(1.0f,0.0f,0.0f), -_rot.y, true);
    rotation.rotate(OT::cVector3f(0.0f,1.0f,0.0f), -_rot.x, false);
}
