#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <dxgi.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
namespace OT
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
        ID3D11Buffer* vbuffer;
    };

    struct VERTEX
    {
        FLOAT X, Y, Z;
        DirectX::XMFLOAT4 COLOR;
    };
}
