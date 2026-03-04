#include "cShader.h"

#include <fstream>
#include <iostream>

#include "d3dcompiler.h"

cShader::cShader(OT::renderdsc _rsc): factory(_rsc.factory), device(_rsc.device), context(_rsc.context)
{
}

void cShader::createShader()
{
    ID3D10Blob *VS, *PS;
    ID3D10Blob* errorBlob = nullptr;
    VS = 0;
    PS = 0;
    
    auto vhr = D3DCompileFromFile(L"src/Assets/Shaders/VSbob.hlsl",0,0, "main", "vs_5_0",D3D10_SHADER_ENABLE_STRICTNESS, 0,&VS, &errorBlob);
    if (FAILED(vhr))
    {
        std::clog << (char*)errorBlob->GetBufferPointer() << "\n";
        
    }
    auto phr = D3DCompileFromFile(L"src/Assets/Shaders/PSbob.hlsl",0,0, "main", "ps_5_0",D3D10_SHADER_ENABLE_STRICTNESS, 0,&PS, &errorBlob);
    if (FAILED(phr))
    {
        std::clog << (char*)errorBlob->GetBufferPointer() << "\n";
    }

    device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &vs);
    device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &ps);

    context->VSSetShader(vs,0,0);
    context->PSSetShader(ps, 0,0);

    D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
        {"TEXCOORD", 0,DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
    context->IASetInputLayout(pLayout);

    D3D11_BUFFER_DESC matrixBufferDesc;
    SecureZeroMemory(&matrixBufferDesc, sizeof(D3D11_BUFFER_DESC));
    matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
    matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    matrixBufferDesc.MiscFlags = 0;
    matrixBufferDesc.StructureByteStride = 0;

    D3D11_SAMPLER_DESC samplerDesc;
    SecureZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
    samplerDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MaxAnisotropy = 1;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
    samplerDesc.BorderColor[0] = 0;
    samplerDesc.BorderColor[1] = 0;
    samplerDesc.BorderColor[2] = 0;
    samplerDesc.BorderColor[3] = 0;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    device->CreateSamplerState(&samplerDesc, &m_samplerState);
    

    device->CreateBuffer(&matrixBufferDesc, NULL, &mbuffer);
}

void cShader::createShape(ID3D11DeviceContext* _context)
{
   
}

bool cShader::setParams(ID3D11DeviceContext* _context, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
    MatrixBufferType* data;
    unsigned int bufferNumber;
    D3D11_MAPPED_SUBRESOURCE ms;
    worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);
    viewMatrix = DirectX::XMMatrixTranspose(viewMatrix);
    projectionMatrix = DirectX::XMMatrixTranspose(projectionMatrix);
    _context->Map(mbuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
    data = (MatrixBufferType*)ms.pData;
    data->world = worldMatrix;
    data->view = viewMatrix;
    data->projection = projectionMatrix;
    _context->Unmap(mbuffer, NULL);
    bufferNumber = 0;
    _context->VSSetConstantBuffers(bufferNumber, 1, &mbuffer);
    _context->PSSetShaderResources(0, 1, &texture);
    return true;
}
