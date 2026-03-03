#include "cRenderer.h"

#include <DirectXMath.h>
#include <stdexcept>

#include "Core.h"


cRenderer::cRenderer()
{
    D3D_FEATURE_LEVEL featureLevel = {};
    UINT creteDeviceFlags = {};

#ifdef _DEBUG
    creteDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    auto hresult = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creteDeviceFlags, NULL,
        0, D3D11_SDK_VERSION, &m_d3dDevice, &featureLevel, &m_d3dDeviceContext);
    if (FAILED(hresult))
    {
        throw std::runtime_error("D3D11CreateDevice failed.");
    }
    m_d3dDevice.As(&m_dxgiDevice);

    m_dxgiDevice->GetAdapter(&m_dxgiAdapter);

    m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), &m_dxgiFactory);
    
}

cRenderer::~cRenderer()
{
    m_swap_chain = nullptr;
}

void cRenderer::render()
{
    m_d3dDeviceContext->ClearRenderTargetView(m_swap_chain->backBuffer, color);
    UINT stride = sizeof(OT::VERTEX);
    UINT offset = 0;
    m_d3dDeviceContext->IASetVertexBuffers(0,1,&m_swap_chain->vBuffer, &stride, &offset);
    m_d3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_d3dDeviceContext->Draw(3,0);
    m_swap_chain->getSwapChain()->Present(1,0);
}

void cRenderer::createSwapChain(const OT::swapchaindsc& desc)
{
    m_swap_chain = std::make_shared<cSwapChain>(desc,getRsc());
}

