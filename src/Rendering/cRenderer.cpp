#include "cRenderer.h"

#include <DirectXMath.h>
#include <stdexcept>

#include "cCamera.h"
#include "cLight.h"
#include "Core.h"


cRenderer::cRenderer(std::vector<cModel*> _models)
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

    shader = new cShader(getRsc());
    shader->createShader();
    for (auto model : _models)
    {
        bool result = model->initialize(getRsc().device,getRsc().context);
        if (!result)
        {
            std::string msg = "Model failed to initialize: " + std::string(model->getName());
            throw std::runtime_error(msg);
        }
    }
    
    m_models = _models;
}

cRenderer::~cRenderer()
{
    m_swap_chain = nullptr;
}

void cRenderer::render(cCamera* _camera, cLight* _light)
{
    OT::cMatrix4x4f view, proj;

   
    m_d3dDeviceContext->ClearRenderTargetView(m_swap_chain->backBuffer, color.ToVector().data());
    m_d3dDeviceContext->ClearDepthStencilView(m_swap_chain->m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f,0xFF);
    
    _camera->render();
    m_swap_chain->getProjectionMatrix(proj);
    view = _camera->viewMatrix;

    for (auto model : m_models)
    {
        
        model->render(m_d3dDeviceContext.Get());
        
        shader->setParams(m_d3dDeviceContext.Get(), model->m_world, view, proj, model->GetTexture(), _light->getDirection(), _light->getDiffuseColor());

        m_d3dDeviceContext->PSSetSamplers(0,1,shader->getSamplerState());

        int id = model->getIndexCount();

        m_d3dDeviceContext->DrawIndexed(id, 0,0);
    }
    m_swap_chain->getSwapChain()->Present(1,0);
}

void cRenderer::createSwapChain(const OT::swapchaindsc& desc)
{
    m_swap_chain = std::make_shared<cSwapChain>(desc,getRsc());
}

