#pragma once
#include "Core.h"
class cShader
{
public:
    cShader(OT::renderdsc _rsc);

    void createShader();
    void renderShape();
private:
    ID3D11InputLayout* pLayout;
    ID3D11VertexShader* vs;
    ID3D11PixelShader* ps;

    IDXGIFactory* factory;
    ID3D11Device* device;
    ID3D11DeviceContext* context;
};
