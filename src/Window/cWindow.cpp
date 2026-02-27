#include "cWindow.h"
#include <stdexcept>
#include <Windows.h>

static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_CLOSE:
        {
            PostQuitMessage(0);
            break;
        }
    default:
        return DefWindowProc(hwnd,msg,wparam,lparam);
    }
}

cWindow::cWindow()
{
    auto registerWindowClass = []()
    {
        WNDCLASSEX wclass{};
        wclass.cbSize = sizeof(WNDCLASSEX);
        wclass.lpszClassName = L"DX3DWindow";
        wclass.lpfnWndProc = &WindowProcedure;
        return RegisterClassEx(&wclass);
        
    };
    auto windowClassId = registerWindowClass();

    if (!windowClassId)
        throw std::runtime_error("RegisterClassEX failed.");

    RECT rect = {0,0,1280,720};
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);

    m_handle = CreateWindowEx(NULL, MAKEINTATOM(windowClassId), L"OneTrick",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top, NULL,NULL,NULL,NULL);

    if (!m_handle)
        throw std::runtime_error("CreateWindowEx failed.");

    ShowWindow(static_cast<HWND>(m_handle), SW_SHOW);
}

cWindow::~cWindow()
{
    DestroyWindow(static_cast<HWND>(m_handle));
}
