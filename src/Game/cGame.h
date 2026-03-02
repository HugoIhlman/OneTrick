#pragma once
#include <memory>

#include "../Core/cLogger.h"
#include "../Rendering/cRenderer.h"
#include "../Window/cWindow.h"

class cGame
{
public:
    cGame();
    ~cGame();
    void run();

private:
    std::unique_ptr<cLogger> m_logger = {};
    std::unique_ptr<cRenderer> m_renderer = {};
    std::unique_ptr<cWindow> m_display = {};
    bool m_isRunning = true;
};
