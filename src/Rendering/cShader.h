#pragma once
#include "Core.h"
#include "../Math/cMatrix4x4.h"

class cShader
{
public:
    cShader(OT::renderdsc _rsc);

    void createShader();
    void createShape(ID3D11DeviceContext* _context);
    bool setParams(ID3D11DeviceContext* _context, OT::cMatrix4x4f worldMatrix, OT::cMatrix4x4f viewMatrix,
        OT::cMatrix4x4f projectionMatrix, ID3D11ShaderResourceView* texture, OT::cVector3f lightDirection, OT::cVector4f diffuseColor);
    ID3D11SamplerState** getSamplerState(){return &m_samplerState;}
private:

    struct MatrixBufferType
    {
        OT::cMatrix4x4f world;
        OT::cMatrix4x4f view;
        OT::cMatrix4x4f projection;
    };

    struct LightBufferType
    {
        OT::cVector4f diffuseColor;
        OT::cVector3f direction;
        float padding;
    };
    
    ID3D11InputLayout* pLayout;
    ID3D11VertexShader* vs;
    ID3D11PixelShader* ps;

    IDXGIFactory* factory;
    ID3D11Device* device;
    ID3D11DeviceContext* context;
    ID3D11Buffer* mbuffer;
    ID3D11SamplerState* m_samplerState;
    ID3D11Buffer* m_lightBuffer;
};
