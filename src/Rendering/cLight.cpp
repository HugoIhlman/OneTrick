#include "cLight.h"

cLight::cLight()
{
}

cLight::~cLight()
{
}

void cLight::setDiffuseColor(float r, float g, float b, float a)
{
    m_diffuseColor = DirectX::XMFLOAT4(r,g,b,a);
}

void cLight::setDirection(float x, float y, float z)
{
    m_direction = DirectX::XMFLOAT3(x,y,z);
}
