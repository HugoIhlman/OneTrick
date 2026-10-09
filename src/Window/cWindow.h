#pragma once
#include <d3d11.h>
#include <memory>
#include "SDL3/SDL.h"

#include "Core.h"


class cRenderer;
class cSwapChain;

class cWindow
{
public:
    cWindow(cRenderer& _renderer);
    ~cWindow();

    OT::swapchaindsc getHandle() {return {m_handle};}
    SDL_Window* getWindow(){return _window;}
   
    std::shared_ptr<cSwapChain> getSwapChain(){return m_swap_chain;}
    
    void Resize(int width, int height) {SDL_SetWindowSize(_window, width, height);};
private:
    void* m_handle{};
    std::shared_ptr<cSwapChain> m_swap_chain = {};
    SDL_Window* _window = nullptr;
    
};
