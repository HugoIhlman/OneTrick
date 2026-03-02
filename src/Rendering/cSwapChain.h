#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include "cRenderer.h"
class cSwapChain
{
public:
    cSwapChain(resource& rsrc);
private:
    IDXGIFactory* factory;
    ID3D11Device* device;
};
