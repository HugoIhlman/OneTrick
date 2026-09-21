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
    float yaw, pitch, roll;
    OT::cMatrix4x4f rotationMatrix, translationMatrix, worldMatrix;

    up = {0.0f,1.0f,0.0f};

    position = {m_posX,m_posY,m_posZ};

    at = {0.0f,0.0f,1.0f};

    
 
    pitch = m_rotX;
    yaw = m_rotY;
    roll = m_rotZ;

    rotationMatrix = rotationMatrix.rotate(OT::cVector3f(1.f,0.f,0.f), pitch);
    rotationMatrix = rotationMatrix.rotate(OT::cVector3f(0.f,1.f,0.f), yaw);
    rotationMatrix = rotationMatrix.rotate(OT::cVector3f(0.f,0.f,1.f), roll);
    at = at.tranformVec(rotationMatrix);
    up = up.tranformVec(rotationMatrix);
    at = position + at;
    
    

    viewMatrix = viewMatrix.lookAt(position, at, up);
}

void cCamera::setPosition(float x, float y, float z)
{
    m_posX = x;
    m_posY = y;
    m_posZ = z;
}

void cCamera::setRotation(float x, float y, float z)
{
    m_rotX = x;
    m_rotY = y;
    m_rotZ = z;
}
