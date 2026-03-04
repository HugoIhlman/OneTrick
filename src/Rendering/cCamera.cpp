#include "cCamera.h"

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
    DirectX::XMFLOAT3 up, position, at;
    DirectX::XMVECTOR upVector, positionVector, atVector;
    float yaw, pitch, roll;
    DirectX::XMMATRIX rotationMatrix;

    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;

    upVector = DirectX::XMLoadFloat3(&up);

    position.x = m_posX;
    position.y = m_posY;
    position.z = m_posZ;

    positionVector = DirectX::XMLoadFloat3(&position);

    at.x = 0.0f;
    at.y = 0.0f;
    at.z = 1.0f;

    atVector = DirectX::XMLoadFloat3(&at);

    pitch = m_rotX * 0.0174532925f;
    yaw = m_rotY * 0.0174532925f;
    roll = m_rotZ * 0.0174532925f;

    rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll);

    atVector = DirectX::XMVector3TransformCoord(atVector, rotationMatrix);
    upVector = DirectX::XMVector3TransformCoord(upVector, rotationMatrix);

    viewMatrix = DirectX::XMMatrixLookAtLH(positionVector, atVector, upVector);
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
