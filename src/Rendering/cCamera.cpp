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

    

    pitch = m_rotX * 0.0174532925f;
    yaw = m_rotY * 0.0174532925f;
    roll = m_rotZ * 0.0174532925f;

    rotationMatrix = rotationMatrix.convertDXMatrix(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
    at = at.tranformVec(rotationMatrix);
    up = up.tranformVec(rotationMatrix);
    at = position + at;
    
    

    viewMatrix = viewMatrix.lookAt();
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
