#pragma once
#include <DirectXMath.h>

#include "Core.h"
#include "cTexture.h"

class cModel
{
public:
    cModel();
    ~cModel();
    bool initialize(ID3D11Device* _device, ID3D11DeviceContext* _context, char* _textureFileName);
    void render(ID3D11DeviceContext* _context);
    ID3D11ShaderResourceView* GetTexture(){return m_Texture->getTexture();};
private:
    bool initializeBuffers(ID3D11Device* _device);
    void renderBuffers(ID3D11DeviceContext* _context);
    bool loadTexture(ID3D11Device*, ID3D11DeviceContext*,char*);
    struct VERTEX
    {
        DirectX::XMFLOAT3 POSITION;
        DirectX::XMFLOAT2 TEXTURE;
        DirectX::XMFLOAT3 NORMAL;
    };

    ID3D11Buffer* m_vertexBuffer;
    ID3D11Buffer* m_indexBuffer;

    int m_vertexCount;
    int m_indexCount;
    cTexture* m_Texture;

};
