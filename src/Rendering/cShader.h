#pragma once
#include "Core.h"
class cShader
{
public:
    cShader(OT::renderdsc _rsc);

    void createShader();
    void createShape(ID3D11DeviceContext* _context);
    bool setParams(ID3D11DeviceContext* _context, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture);
    ID3D11SamplerState** getSamplerState(){return &m_samplerState;}
private:

    struct MatrixBufferType
    {
        DirectX::XMMATRIX world;
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX projection;
    };
    
    ID3D11InputLayout* pLayout;
    ID3D11VertexShader* vs;
    ID3D11PixelShader* ps;

    IDXGIFactory* factory;
    ID3D11Device* device;
    ID3D11DeviceContext* context;
    ID3D11Buffer* mbuffer;
    ID3D11SamplerState* m_samplerState;
};
