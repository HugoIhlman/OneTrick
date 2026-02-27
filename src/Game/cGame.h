#pragma once
#include <memory>

#include "../Rendering/cRenderer.h"
#include "../Window/cWindow.h"

class cGame
{
public:
    cGame();
    ~cGame();
    void run();

private:
    std::unique_ptr<cRenderer> m_renderer = {};
    std::unique_ptr<cWindow> m_display = {};
    bool m_isRunning = true;
};
