#include "cModel.h"

#include <fstream>
#include <iterator>

cModel::cModel()
{
}

cModel::~cModel()
{
    delete m_Texture;
    m_Texture = nullptr;
    delete m_model;
    m_model = nullptr;
}

bool cModel::initialize(ID3D11Device* _device, ID3D11DeviceContext* _context, char* _textureFileName, char* _model)
{
    bool mresult = loadModel(_model);
    if (!mresult)
    {
        return false;
    }
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
    VERTEX* vertices;
    unsigned long* indices;
    int i;

    vertices = new VERTEX[m_vertexCount];
    indices = new unsigned long[m_indexCount];
    for (i = 0; i < m_vertexCount; ++i)
    {
        vertices[i].POSITION = DirectX::XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
        vertices[i].TEXTURE = DirectX::XMFLOAT2(m_model[i].u, m_model[i].v);
        vertices[i].NORMAL = DirectX::XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

        indices[i] = i;
    }
    
    D3D11_BUFFER_DESC vbd;
    SecureZeroMemory(&vbd, sizeof(D3D11_BUFFER_DESC));
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.ByteWidth = sizeof(VERTEX) * m_vertexCount;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA vd;
    SecureZeroMemory(&vd, sizeof(D3D11_SUBRESOURCE_DATA));
    vd.pSysMem = vertices;
    vd.SysMemPitch = 0;
    vd.SysMemSlicePitch = 0;

    D3D11_BUFFER_DESC ibd;
    SecureZeroMemory(&ibd, sizeof(D3D11_BUFFER_DESC));
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = sizeof(unsigned long) * m_indexCount;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;

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

bool cModel::loadModel(char* _model)
{
    std::ifstream fin;
    char input;
    int i;

    fin.open(_model);
    if (fin.fail())
    {
        return false;
    }

    fin.get(input);
    while (input != ':')
    {
        fin.get(input);
    }

    fin >> m_vertexCount;

    m_indexCount = m_vertexCount;

    m_model = new MODEL[m_vertexCount];

    fin.get(input);
    while (input != ':')
    {
        fin.get(input);
    }
    fin.get(input);
    fin.get(input);

    for (i = 0; i < m_vertexCount; i++)
    {
        fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
        fin >> m_model[i].u >> m_model[i].v;
        fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
    }
    fin.close();
    return true;
}
