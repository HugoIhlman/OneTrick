#pragma once
#include <wrl.h>
#include "Core.h"
class cSwapChain
{
public:
    cSwapChain(Ot::swapchaindsc swp, Ot::renderdsc rnd);
    ~cSwapChain();

    IDXGISwapChain* getSwapChain(){return m_swapchain.Get();}
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapchain{};
    ID3D11RenderTargetView* backBuffer;
private:
    IDXGIFactory* factory;
    ID3D11Device* device;
    ID3D11DeviceContext* context;

    

    void* m_handle;
};
