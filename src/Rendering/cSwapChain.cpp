#include "cSwapChain.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include "Core.h"
#include "cShader.h"


cSwapChain::cSwapChain(OT::swapchaindsc swp, OT::renderdsc rnd): factory(rnd.factory), device(rnd.device), m_handle(swp.winHandle), context(rnd.context)
{
    DXGI_SWAP_CHAIN_DESC dxgi_swap_chain_desc;

    SecureZeroMemory(&dxgi_swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC));
    dxgi_swap_chain_desc.BufferDesc.Width = SCREEN_WIDTH;
    dxgi_swap_chain_desc.BufferDesc.Height = SCREEN_HEIGHT;
    dxgi_swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    dxgi_swap_chain_desc.BufferCount = 1;
    dxgi_swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    dxgi_swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    dxgi_swap_chain_desc.OutputWindow = static_cast<HWND>(m_handle);
    dxgi_swap_chain_desc.Windowed = TRUE;
    dxgi_swap_chain_desc.SampleDesc.Count = 1;
    dxgi_swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    dxgi_swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    
    
    auto hr = factory->CreateSwapChain(device, &dxgi_swap_chain_desc, &m_swapchain);
    if (FAILED(hr))
    {
        throw std::runtime_error("CreateSwapChain Failed.");
    }


    ID3D11Texture2D* pbackBuffer;
    m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pbackBuffer);

    device->CreateRenderTargetView(pbackBuffer, NULL, &backBuffer);
    pbackBuffer->Release();



    D3D11_TEXTURE2D_DESC depthBufferDesc;
    SecureZeroMemory(&depthBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
    depthBufferDesc.Height = SCREEN_HEIGHT;
    depthBufferDesc.Width = SCREEN_WIDTH;
    depthBufferDesc.MipLevels = 1;
    depthBufferDesc.ArraySize = 1;
    depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferDesc.SampleDesc.Count = 1;
    depthBufferDesc.SampleDesc.Quality = 0;
    depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferDesc.CPUAccessFlags = 0;
    depthBufferDesc.MiscFlags = 0;
    device->CreateTexture2D(&depthBufferDesc, NULL, &depthStencil);

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    SecureZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

    depthStencilDesc.StencilEnable = true;
    depthStencilDesc.StencilReadMask = 0xFF;
    depthStencilDesc.StencilWriteMask = 0xFF;

    
    depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
    depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

   
    depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
    depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

    device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
    context->OMSetDepthStencilState(m_depthStencilState, 1);

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    SecureZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    device->CreateDepthStencilView(depthStencil, &depthStencilViewDesc, &m_depthStencilView);

    context->OMSetRenderTargets(1, &backBuffer, m_depthStencilView);

    D3D11_RASTERIZER_DESC rasterDesc;
    SecureZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
    rasterDesc.AntialiasedLineEnable = false;
    rasterDesc.CullMode = D3D11_CULL_BACK;
    rasterDesc.DepthBias = 0;
    rasterDesc.DepthBiasClamp = 0.0f;
    rasterDesc.DepthClipEnable = true;
    rasterDesc.FillMode = D3D11_FILL_SOLID;
    rasterDesc.FrontCounterClockwise = false;
    rasterDesc.MultisampleEnable = false;
    rasterDesc.ScissorEnable = false;
    rasterDesc.SlopeScaledDepthBias = 0.0f;
    
    device->CreateRasterizerState(&rasterDesc, &m_rasterState);

    context->RSSetState(m_rasterState);

    D3D11_VIEWPORT viewport;
    SecureZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Height = SCREEN_HEIGHT;
    viewport.Width = SCREEN_WIDTH;
    viewport.MaxDepth = 1.0f;
    viewport.MinDepth = 0.0f;

    context->RSSetViewports(1, &viewport);
    float fov = 3.141592654f / 4.0f;
    float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

    auto dxMatrix = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, 0.1f, 1000.f);
    projectionMatrix = projectionMatrix.convertDXMatrix(dxMatrix);
}

cSwapChain::~cSwapChain()
{
}
