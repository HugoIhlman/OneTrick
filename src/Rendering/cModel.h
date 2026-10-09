#pragma once
#include <DirectXMath.h>

#include "Core.h"
#include "cTexture.h"
#include "../Math/cMatrix4x4.h"

class cModel
{
public:
    cModel(const char* _texture, const char* _model);
    ~cModel();
    bool initialize(ID3D11Device* _device, ID3D11DeviceContext* _context);
    void render(ID3D11DeviceContext* _context);
    ID3D11ShaderResourceView* GetTexture(){return m_Texture->getTexture();};
    int getIndexCount(){return m_indexCount;}
    void setPosition(OT::cVector3f _pos);
    void setRotation(OT::cVector3f _axis, float _rot);
    void setScale(OT::cVector3f _scale);
    
    char* getName(){return m_modelPath;}
    
    OT::cMatrix4x4f m_world = {};
    OT::cMatrix4x4f m_scale = {};
    OT::cMatrix4x4f m_translation = {};
    OT::cMatrix4x4f m_rotation = {};
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
    
    char* m_texturePath;
    char* m_modelPath;
    
    OT::cMatrix4x4f m_scaleRotate = {};

    int m_vertexCount;
    int m_indexCount;
    cTexture* m_Texture;
    MODEL* m_model;

};
