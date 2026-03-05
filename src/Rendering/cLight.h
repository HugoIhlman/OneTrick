#pragma once
#include <DirectXMath.h>

class cLight
{
public:
    cLight();
    ~cLight();

    void setDiffuseColor(float,float,float,float);
    void setDirection(float,float,float);

    DirectX::XMFLOAT4 getDiffuseColor(){return m_diffuseColor;}
    DirectX::XMFLOAT3 getDirection(){return m_direction;}
private:
    DirectX::XMFLOAT4 m_diffuseColor;
    DirectX::XMFLOAT3 m_direction;
};
