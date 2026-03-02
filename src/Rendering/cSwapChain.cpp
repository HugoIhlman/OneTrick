#include "cSwapChain.h"

#include <algorithm>


cSwapChain::cSwapChain(resource& rsrc): factory(&rsrc.factory), device(&rsrc.device)
{
    DXGI_SWAP_CHAIN_DESC dxgi_swap_chain_desc;
    
    factory->CreateSwapChain(device, )
}
