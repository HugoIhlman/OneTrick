#include "cModel.h"

#include <iterator>

cModel::cModel()
{
}

cModel::~cModel()
{
    delete m_Texture;
    m_Texture = nullptr;
}

bool cModel::initialize(ID3D11Device* _device, ID3D11DeviceContext* _context, char* _textureFileName)
{
    bool result = initializeBuffers(_device);
    if (!result)
    {
        return false;
    }
    bool tresult = loadTexture(_device, _context, _textureFileName);
    if (!tresult)
    {
        return false;
    }
    return true;
}

void cModel::render(ID3D11DeviceContext* _context)
{
    renderBuffers(_context);
}

bool cModel::initializeBuffers(ID3D11Device* _device)
{
    VERTEX vertices[3] = {
        {DirectX::XMFLOAT3(-0.3f,-0.3f,0.0f), DirectX::XMFLOAT2(0.0f,1.0f)},
        {DirectX::XMFLOAT3(0.0f,0.3f,0.0f), DirectX::XMFLOAT2(0.5f,0.0f)},
        {DirectX::XMFLOAT3(0.3f,-0.3f,0.0f), DirectX::XMFLOAT2(1.0f,1.0f)}
    };
    unsigned long indices[3];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    D3D11_BUFFER_DESC vbd;
    SecureZeroMemory(&vbd, sizeof(D3D11_BUFFER_DESC));
    vbd.Usage = D3D11_USAGE_DYNAMIC;
    vbd.ByteWidth = sizeof(vertices) * 3;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA vd;
    SecureZeroMemory(&vd, sizeof(D3D11_SUBRESOURCE_DATA));
    vd.pSysMem = vertices;
    vd.SysMemPitch = 0;
    vd.SysMemSlicePitch = 0;

    D3D11_BUFFER_DESC ibd;
    SecureZeroMemory(&ibd, sizeof(D3D11_BUFFER_DESC));
    ibd.Usage = D3D11_USAGE_DYNAMIC;
    ibd.ByteWidth = sizeof(unsigned long) * 3;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA id;
    SecureZeroMemory(&id, sizeof(D3D11_SUBRESOURCE_DATA));
    id.pSysMem = indices;
    id.SysMemPitch = 0;
    id.SysMemSlicePitch = 0;

    auto vres = _device->CreateBuffer(&vbd, &vd, &m_vertexBuffer);
    if (FAILED(vres))
    {
        return false;
    }
    auto ires = _device->CreateBuffer(&ibd, &id, &m_indexBuffer);
    if (FAILED(ires))
    {
        return false;
    }
    
    return true;
}

void cModel::renderBuffers(ID3D11DeviceContext* _context)
{
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    _context->IASetVertexBuffers(0,1,&m_vertexBuffer, &stride, &offset);
    _context->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    _context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool cModel::loadTexture(ID3D11Device* _device, ID3D11DeviceContext* _context, char* _filename)
{
    m_Texture = new cTexture;

    bool result = m_Texture->init(_device, _context, _filename);
    if (!result)
    {
        return false;
    }
    return true;
}
