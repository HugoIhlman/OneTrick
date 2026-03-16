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
        {"TEXCOORD", 0,DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    unsigned int numElements = sizeof(ied)/sizeof(ied[0]);
    device->CreateInputLayout(ied, numElements, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
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

    D3D11_BUFFER_DESC lightBufferDesc;
    SecureZeroMemory(&lightBufferDesc, sizeof(D3D11_BUFFER_DESC));
    lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    lightBufferDesc.ByteWidth = sizeof(LightBufferType);
    lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    lightBufferDesc.MiscFlags = 0;
    lightBufferDesc.StructureByteStride = 0;

    device->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer);
    

    device->CreateSamplerState(&samplerDesc, &m_samplerState);
    

    device->CreateBuffer(&matrixBufferDesc, NULL, &mbuffer);
}

void cShader::createShape(ID3D11DeviceContext* _context)
{
   
}

bool cShader::setParams(ID3D11DeviceContext* _context, OT::cMatrix4x4f worldMatrix, OT::cMatrix4x4f viewMatrix,
        OT::cMatrix4x4f projectionMatrix, ID3D11ShaderResourceView* texture, OT::cVector3f lightDirection, OT::cVector4f diffuseColor);
{
    MatrixBufferType* matrix_data;
    LightBufferType* light_data;
    unsigned int bufferNumber;
    D3D11_MAPPED_SUBRESOURCE ms;
    worldMatrix.transpose();
    viewMatrix
    projectionMatrix.transpose();
    _context->Map(mbuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
    matrix_data = (MatrixBufferType*)ms.pData;
    matrix_data->world = worldMatrix;
    matrix_data->view = viewMatrix;
    matrix_data->projection = projectionMatrix;
    _context->Unmap(mbuffer, NULL);
    bufferNumber = 0;
    _context->VSSetConstantBuffers(bufferNumber, 1, &mbuffer);
    _context->PSSetShaderResources(0, 1, &texture);
    _context->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
    light_data = (LightBufferType*)ms.pData;
    light_data->diffuseColor = diffuseColor;
    light_data->direction = lightDirection;
    light_data->padding = 0.0f;
    _context->Unmap(m_lightBuffer, 0);
    bufferNumber = 0;
    _context->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);
    return true;
}
