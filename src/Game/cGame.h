#pragma once
#include "../Window/cWindow.h"

class cGame
{
public:
    cGame();
    ~cGame();
    void run();

private:
    cWindow* m_display = {};
    bool m_isRunning = true;
};
