#pragma once
#include <DirectXMath.h>

#include "../Math/cVector3.h"
#include "../Math/cVector4.h"

class cLight
{
public:
    cLight();
    ~cLight();

    void setDiffuseColor(float,float,float,float);
    void setDirection(float,float,float);

    OT::cVector4f getDiffuseColor(){return m_diffuseColor;}
    OT::cVector3f getDirection(){return m_direction;}
private:
    OT::cVector4f m_diffuseColor;
    OT::cVector3f m_direction;
};
