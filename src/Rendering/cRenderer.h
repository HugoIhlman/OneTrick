#pragma once
#include <d3d11.h>

struct resource
{
    ID3D11Device& device;
    IDXGIFactory& factory;
};

class cRenderer
{
public:
    cRenderer();
    ~cRenderer();
    

    void render();
    resource getResource();
private:
    ID3D11Device* m_d3dDevice = {};
    ID3D11DeviceContext* m_d3dDeviceContext = {};
    IDXGIDevice* m_dxgiDevice = {};
    IDXGIAdapter* m_dxgiAdapter = {};
    IDXGIFactory* m_dxgiFactory = {};

};

