#pragma once
#include <d3d11.h>
#include <dxgi.h>

namespace Ot
{
    class cWindow;
    class cGame;
    class cRenderer;
    class cSwapChain;
    class cLogger;

    struct swapchaindsc
    {
        void* winHandle;
    };
    struct renderdsc
    {
        IDXGIFactory* factory;
        ID3D11Device* device;
        ID3D11DeviceContext* context;
    };
}
