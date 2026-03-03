#include "cShader.h"

#include <fstream>

#include "d3dcompiler.h"

cShader::cShader(OT::renderdsc _rsc): factory(_rsc.factory), device(_rsc.device), context(_rsc.context)
{
}

void cShader::createShader()
{
    ID3D10Blob *VS, *PS;
    ID3D10Blob* errorBlob = nullptr;
    
    auto vhr = D3DCompileFromFile(L"src/Assets/Shaders/VSbob.hlsl",0,0, "main", "vs_4_0",0, 0,&VS, &errorBlob);
    auto phr = D3DCompileFromFile(L"src/Assets/Shaders/PSbob.hlsl",0,0, "main", "ps_4_0",0, 0,&PS, &errorBlob);
    if (FAILED(vhr) || FAILED(phr))
    {
        if (errorBlob)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
        }
    }

    device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &vs);
    device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &ps);

    context->VSSetShader(vs,0,0);
    context->PSSetShader(ps, 0,0);

    D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"COLOR", 0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
    context->IASetInputLayout(pLayout);
}

void cShader::renderShape()
{
}
