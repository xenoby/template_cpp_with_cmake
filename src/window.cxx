#include "window.h"

static TCHAR winClass[] = _T("Sample Window Class");
static TCHAR winName[] = _T("Sample Window Name");

Window::Window()
    : m_width(800)
    , m_height(600)
{
    m_run = RegAndCreateWnd(GetModuleHandle(NULL));
    Run();
}

Window::Window(HINSTANCE hInstance)
    : m_width(800)
    , m_height(600)
{
    m_run = RegAndCreateWnd(hInstance);
    Run();
}

bool Window::RegAndCreateWnd(HINSTANCE hInstance)
{
    /* The Window structure */
	m_wincl.hInstance = hInstance;
	m_wincl.lpszClassName = (TCHAR*)winClass;
	m_wincl.lpfnWndProc = WindowProcedure;
	m_wincl.style = CS_DBLCLKS;
	m_wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	m_wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	m_wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wincl.lpszMenuName = NULL;                 /* No menu */
	m_wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	m_wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default colour as the background of the window */
	m_wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx(&m_wincl))
		return false;

	/* The class is registered, let's create the program*/
	m_hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		(TCHAR*)winClass,         /* Classname */
		(TCHAR*)winName,       /* Title Text */
		WS_OVERLAPPEDWINDOW, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		m_width,                 /* The programs width */
		m_height,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
		);

	SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);

	m_hdc = GetDC(m_hwnd);

	/* Make the window visible on the screen */
	ShowWindow(m_hwnd, SW_SHOW);
    return true;
}

WPARAM Window::Run()
{
    while (m_run)
	{
		if (PeekMessage(&m_messages, NULL, 0, 0, PM_REMOVE))
		{
			switch (m_messages.message)
			{
			case WM_DESTROY:
				PostQuitMessage(m_messages.wParam);
				break;
			case WM_QUIT:
				return m_messages.wParam;
			default:
				TranslateMessage(&m_messages);
				DispatchMessage(&m_messages);
			}
		}
		else
		{
			
		}
	}

    return S_OK;
}

LRESULT CALLBACK Window::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Window *this_ptr = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if(this_ptr)
	{
		switch (message)                  /* handle the messages */
		{
			case WM_CREATE: break;
			case WM_DESTROY:				
				PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
				break;
			case WM_SETFOCUS: break;
			case WM_KILLFOCUS: break;
			case WM_ACTIVATEAPP: break;
			case WM_ENTERSIZEMOVE: break;
			case WM_EXITSIZEMOVE: break;
			case WM_SIZING: break;
			case WM_TIMER: break;
			case WM_PAINT: break;
			case WM_ERASEBKGND: break;
			default:                      /* for messages that we don't deal with */
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}