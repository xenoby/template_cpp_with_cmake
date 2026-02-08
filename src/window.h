#ifndef WIN32_WINDOW_CLASS_H
#define WIN32_WINDOW_CLASS_H

#include <windows.h>
#include <tchar.h>

class Window {
private:
    WNDCLASSEX m_wincl;
    HINSTANCE m_hinst;
    MSG m_messages;
    HWND m_hwnd;
    HDC m_hdc;

private:
    size_t m_width;
    size_t m_height;
    TCHAR m_winAppName;
    TCHAR m_winClassName;
    bool m_run;

public:
    Window();
    Window(HINSTANCE hInstance);

private:
    WPARAM WINAPI Run();
    bool RegAndCreateWnd(HINSTANCE hInstance);
    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};
#endif
