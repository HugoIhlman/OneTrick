#pragma once
#include <DirectXMath.h>

#include "Core.h"
#include "cTexture.h"

class cModel
{
public:
    cModel();
    ~cModel();
    bool initialize(ID3D11Device* _device, ID3D11DeviceContext* _context, char* _textureFileName, char* _modelFileName);
    void render(ID3D11DeviceContext* _context);
    ID3D11ShaderResourceView* GetTexture(){return m_Texture->getTexture();};
    int getIndexCount(){return m_indexCount;}
private:
    bool initializeBuffers(ID3D11Device* _device);
    void renderBuffers(ID3D11DeviceContext* _context);
    bool loadTexture(ID3D11Device*, ID3D11DeviceContext*,char*);
    bool loadModel(char*);
    struct VERTEX
    {
        DirectX::XMFLOAT3 POSITION;
        DirectX::XMFLOAT2 TEXTURE;
        DirectX::XMFLOAT3 NORMAL;
    };

    struct MODEL
    {
        float x,y,z;
        float u,v;
        float nx,ny,nz;
    };

    ID3D11Buffer* m_vertexBuffer;
    ID3D11Buffer* m_indexBuffer;

    int m_vertexCount;
    int m_indexCount;
    cTexture* m_Texture;
    MODEL* m_model;

};
