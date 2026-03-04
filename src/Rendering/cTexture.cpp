#include "cTexture.h"

#include <cstdio>
#include <filesystem>

cTexture::cTexture()
{
}

cTexture::~cTexture()
{
}

bool cTexture::init(ID3D11Device* _device, ID3D11DeviceContext* _context, char* _filename)
{
    int height, width;
    unsigned int rowPitch;

    auto loadresult = loadTarga(_filename);
    if (!loadresult)
    {
        return false;
    }

    D3D11_TEXTURE2D_DESC textureDesc;
    textureDesc.Height = m_height;
    textureDesc.Width = m_width;
    textureDesc.MipLevels = 0;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DYNAMIC;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

    auto hRes = _device->CreateTexture2D(&textureDesc, NULL, &m_texture);
    if (FAILED(hRes))
    {
        return false;
    }

    rowPitch = (m_width * 4) * sizeof(unsigned char);

    _context->UpdateSubresource(m_texture, 0, NULL, m_targaData, rowPitch, 0);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = -1;

    auto srvHres = _device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);
    if (FAILED(srvHres))
    {
        return false;
    }
    _context->GenerateMips(m_textureView);

    delete [] m_targaData;
    m_targaData = 0;
    return true;
}

bool cTexture::loadTarga(char* _filename)
{
    FILE* filePtr;
    TargaHeader targaHeader;
    unsigned char* targaImage;
    int bpp, imageSize, index, i, j, k;
    unsigned int count;

    auto openerror = fopen_s(&filePtr, _filename, "rb");
    if (openerror != 0)
    {
        return false;
    }
    count = (unsigned int)fread(&targaHeader, sizeof(TargaHeader), 1, filePtr);
    m_height = (int)targaHeader.height;
    m_width = (int)targaHeader.width;
    bpp = (int)targaHeader.bpp;

    if (bpp != 32)
    {
        return false;
    }

    imageSize = m_width*(m_height) * 4;

    targaImage = new unsigned char[imageSize];

    count = (unsigned int)fread(targaImage, sizeof(BYTE), imageSize, filePtr);
    if (count != imageSize)
    {
        return false;
    }

    auto closeerror = fclose(filePtr);
    if (closeerror != 0)
    {
        return false;
    }

    m_targaData = new unsigned char[imageSize];

    index = 0;

    k = (m_width * m_height * 4) - (m_width * 4);

    for (j = 0; j < m_height; j++)
    {
        for (i = 0; i < m_width; i++)
        {
            m_targaData[index+0] = targaImage[k+2];
            m_targaData[index+1] = targaImage[k+1];
            m_targaData[index+2] = targaImage[k+0];
            m_targaData[index+3] = targaImage[k+3];

            k += 4;
            index += 4;
        }
        k = m_width * 8;
    }

    delete [] targaImage;
    targaImage = nullptr;

    return true;
    
}
