#pragma once
#include <wrl.h>
#include "Core.h"
class cSwapChain
{
public:
    cSwapChain(OT::swapchaindsc swp, OT::renderdsc rnd);
    ~cSwapChain();

    IDXGISwapChain* getSwapChain(){return m_swapchain.Get();}
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapchain{};
    ID3D11RenderTargetView* backBuffer;
    ID3D11Buffer* vBuffer;
private:
    IDXGIFactory* factory;
    ID3D11Device* device;
    ID3D11DeviceContext* context;

    

    void* m_handle;
};
