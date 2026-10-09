#pragma once
#include <d3d11.h>
#include <memory>
#include <wrl.h>

#include "cModel.h"
#include "cShader.h"
#include "cSwapChain.h"
#include "../Math/cVector4.h"
class cLight;
class cCamera;
using Microsoft::WRL::ComPtr;

class cRenderer
{
public:
    cRenderer(std::vector<cModel*> _models);
    ~cRenderer();
    

    void render(cCamera* _camera, cLight* _light);
    OT::renderdsc getRsc(){return {m_dxgiFactory.Get(), m_d3dDevice.Get(), m_d3dDeviceContext.Get()};}
    void createSwapChain(const OT::swapchaindsc& desc);
    void resize() {m_swap_chain->resize();}
private:
    ComPtr<ID3D11Device> m_d3dDevice = {};
    ComPtr<ID3D11DeviceContext> m_d3dDeviceContext = {};
    ComPtr<IDXGIDevice> m_dxgiDevice = {};
    ComPtr<IDXGIAdapter> m_dxgiAdapter = {};
    ComPtr<IDXGIFactory> m_dxgiFactory = {};

    cShader* shader;
    
    const OT::cVector4f color = {0.2f,0.2f,0.3f,1.0f};
    std::shared_ptr<cSwapChain> m_swap_chain = {};
    
    std::vector<cModel*> m_models;

    float rotation = 0.0f;

};

