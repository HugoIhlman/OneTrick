#pragma once
#include <d3d11.h>

class cTexture
{
    struct TargaHeader
    {
        unsigned char data1[12];
        unsigned short width;
        unsigned short height;
        unsigned char bpp;
        unsigned char data2;
    };
public:
    cTexture();
    ~cTexture();

    bool init(ID3D11Device*, ID3D11DeviceContext*, char*);

    ID3D11ShaderResourceView* getTexture(){return m_textureView;}
    int getWidth(){return m_width;}
    int getHeight(){return m_height;}

private:
    bool loadTarga(char*);

    unsigned char* m_targaData;
    ID3D11Texture2D* m_texture;
    ID3D11ShaderResourceView* m_textureView;
    int m_height, m_width;
};
