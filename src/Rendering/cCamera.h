#pragma once
#include <DirectXMath.h>

#include "../Math/cMatrix4x4.h"

class cCamera
{
public:
    cCamera();
    ~cCamera();
    void render();
    void getViewMatrix(OT::cMatrix4x4f& _matrix){_matrix = viewMatrix;}

    void setPosition(OT::cVector3f _trans);
    void setRotation(OT::cVector3f _rot);

    DirectX::XMFLOAT3 getPosition(){return DirectX::XMFLOAT3(m_posX,m_posY,m_posZ);}
    DirectX::XMFLOAT3 getRotation(){return DirectX::XMFLOAT3(m_rotX,m_rotY,m_rotZ);}

    OT::cMatrix4x4f viewMatrix;
    OT::cMatrix4x4f world;
    OT::cMatrix4x4f translation;
    OT::cMatrix4x4f rotation;
private:

    float m_posX, m_posY, m_posZ;
    float m_rotX, m_rotY, m_rotZ;
    
};
