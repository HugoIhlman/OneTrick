#pragma once
#include <d3d11.h>
#include <memory>
#include <wrl.h>
#include "cSwapChain.h"
using Microsoft::WRL::ComPtr;

class cRenderer
{
public:
    cRenderer();
    ~cRenderer();
    

    void render();
    OT::renderdsc getRsc(){return {m_dxgiFactory.Get(), m_d3dDevice.Get(), m_d3dDeviceContext.Get()};}
    void createSwapChain(const OT::swapchaindsc& desc);
private:
    ComPtr<ID3D11Device> m_d3dDevice = {};
    ComPtr<ID3D11DeviceContext> m_d3dDeviceContext = {};
    ComPtr<IDXGIDevice> m_dxgiDevice = {};
    ComPtr<IDXGIAdapter> m_dxgiAdapter = {};
    ComPtr<IDXGIFactory> m_dxgiFactory = {};

    

    const FLOAT color[4] = {0.0f,0.2f,0.4f,1.0f};

    std::shared_ptr<cSwapChain> m_swap_chain = {};

};

