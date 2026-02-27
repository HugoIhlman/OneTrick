#pragma once
#include <d3d11.h>


class cRenderer
{
public:
    cRenderer();
    ~cRenderer();
    

    void render();
private:
    ID3D11Device* m_d3dDevice = {};
    ID3D11DeviceContext* m_d3dDeviceContext = {};

};

