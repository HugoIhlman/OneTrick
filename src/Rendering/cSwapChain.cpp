#include "cSwapChain.h"

#include <algorithm>
#include <stdexcept>


cSwapChain::cSwapChain(Ot::swapchaindsc swp, Ot::renderdsc rnd): factory(rnd.factory), device(rnd.device), m_handle(swp.winHandle), context(rnd.context)
{
    DXGI_SWAP_CHAIN_DESC dxgi_swap_chain_desc;

    SecureZeroMemory(&dxgi_swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));
    dxgi_swap_chain_desc.BufferDesc.Width = 0;
    dxgi_swap_chain_desc.BufferDesc.Height = 0;
    dxgi_swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    dxgi_swap_chain_desc.BufferCount = 2;
    dxgi_swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    dxgi_swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    dxgi_swap_chain_desc.OutputWindow = static_cast<HWND>(m_handle);
    dxgi_swap_chain_desc.Windowed = TRUE;
    dxgi_swap_chain_desc.SampleDesc.Count = 4;
    dxgi_swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;

    
    
    auto hr = factory->CreateSwapChain(device, &dxgi_swap_chain_desc, &m_swapchain);
    if (FAILED(hr))
    {
        throw std::runtime_error("CreateSwapChain Failed.");
    }


    ID3D11Texture2D* pbackBuffer;
    m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pbackBuffer);

    device->CreateRenderTargetView(pbackBuffer, NULL, &backBuffer);
    pbackBuffer->Release();

    context->OMSetRenderTargets(1, &backBuffer, NULL);

    D3D11_VIEWPORT viewport;
    SecureZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Height = 720;
    viewport.Width = 1280;

    context->RSSetViewports(1, &viewport);
}

cSwapChain::~cSwapChain()
{
}
