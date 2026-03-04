#pragma once
#include <DirectXMath.h>

class cCamera
{
public:
    cCamera();
    ~cCamera();
    void render();
    DirectX::XMMATRIX getViewMatrix(){return viewMatrix;}

    void setPosition(float,float,float);
    void setRotation(float,float,float);

    DirectX::XMFLOAT3 getPosition(){return DirectX::XMFLOAT3(m_posX,m_posY,m_posZ);}
    DirectX::XMFLOAT3 getRotation(){return DirectX::XMFLOAT3(m_rotX,m_rotY,m_rotZ);}

private:
    DirectX::XMMATRIX viewMatrix;

    float m_posX, m_posY, m_posZ;
    float m_rotX, m_rotY, m_rotZ;
    
};
