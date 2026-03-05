#pragma once
#include <wrl.h>
#include "Core.h"
class cSwapChain
{
public:
    cSwapChain(OT::swapchaindsc swp, OT::renderdsc rnd);
    ~cSwapChain();

    IDXGISwapChain* getSwapChain(){return m_swapchain.Get();}
    void getProjectionMatrix(DirectX::XMMATRIX& _m){_m = projectionMatrix;}
    void getWorldMatrix(DirectX::XMMATRIX& _m){_m = worldMatrix;}

    
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapchain{};
    ID3D11DepthStencilView* m_depthStencilView;
    ID3D11RenderTargetView* backBuffer;
    ID3D11Buffer* vBuffer;
private:
    IDXGIFactory* factory;
    ID3D11Device* device;
    ID3D11DeviceContext* context;

    ID3D11Texture2D* depthStencil;
    ID3D11DepthStencilState* m_depthStencilState;
    ID3D11RasterizerState* m_rasterState;

    DirectX::XMMATRIX worldMatrix;
    DirectX::XMMATRIX projectionMatrix;

    void* m_handle;
};
