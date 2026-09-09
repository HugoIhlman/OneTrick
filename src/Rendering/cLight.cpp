#include "cLight.h"

cLight::cLight()
{
}

cLight::~cLight()
{
}

void cLight::setDiffuseColor(float r, float g, float b, float a)
{
    m_diffuseColor = OT::cVector4f(r,g,b,a);
}

void cLight::setDirection(float x, float y, float z)
{
    m_direction = OT::cVector3f(x,y,z);
}
