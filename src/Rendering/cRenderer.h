#pragma once
#include <d3d11.h>
#include <memory>
#include <wrl.h>

#include "cModel.h"
#include "cShader.h"
#include "cSwapChain.h"
class cLight;
class cCamera;
using Microsoft::WRL::ComPtr;

class cRenderer
{
public:
    cRenderer();
    ~cRenderer();
    

    void render(cModel* _model, cCamera* _camera, cLight* _light);
    OT::renderdsc getRsc(){return {m_dxgiFactory.Get(), m_d3dDevice.Get(), m_d3dDeviceContext.Get()};}
    void createSwapChain(const OT::swapchaindsc& desc);
private:
    ComPtr<ID3D11Device> m_d3dDevice = {};
    ComPtr<ID3D11DeviceContext> m_d3dDeviceContext = {};
    ComPtr<IDXGIDevice> m_dxgiDevice = {};
    ComPtr<IDXGIAdapter> m_dxgiAdapter = {};
    ComPtr<IDXGIFactory> m_dxgiFactory = {};

    cShader* shader;
    
    const FLOAT color[4] = {0.0f,0.2f,0.4f,1.0f};

    std::shared_ptr<cSwapChain> m_swap_chain = {};

    float rotation = 0.0f;

};

