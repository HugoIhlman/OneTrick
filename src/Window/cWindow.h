#pragma once
#include <d3d11.h>
#include <memory>

#include "Core.h"


class cRenderer;
class cSwapChain;

class cWindow
{
public:
    cWindow(cRenderer& _renderer);
    ~cWindow();

    OT::swapchaindsc getHandle() {return {m_handle};}
   
    std::shared_ptr<cSwapChain> getSwapChain(){return m_swap_chain;}
private:
    void* m_handle{};
    std::shared_ptr<cSwapChain> m_swap_chain = {};
};
