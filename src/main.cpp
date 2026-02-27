
#include <iostream>
#include <DirectXMath.h>
#include <string>
#include "Game/cGame.h"


int main()
{
    try
    {
        cGame game{};
        game.run();
    }
    catch (const std::runtime_error&)
    {
        return EXIT_FAILURE;
    }
    catch (const std::exception&)
    {
        return EXIT_FAILURE;
    }
   
   
    return EXIT_SUCCESS;
}
