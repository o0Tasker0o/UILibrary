#include <time.h>
#include "GLView.h"

#define WINDOW_TITLE "UI Library App"
#define WINDOW_CLASS WINDOW_TITLE " Class"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

GLView *gpGLView(NULL);

int gLastMouseX(0);
int gLastMouseY(0);

bool gMiddleMouseDragging(false);

LRESULT CALLBACK WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    int currentMouseX = LOWORD(lp);
    int currentMouseY = HIWORD(lp);

    switch (m)
    {
    case WM_LBUTTONDOWN:
    {
        RECT windowRect;

        GetClientRect(hwnd, &windowRect);
        gpGLView->Update(currentMouseX, currentMouseY, true);
        break;
    }
    case WM_LBUTTONUP:
    {
        RECT windowRect;

        GetClientRect(hwnd, &windowRect);
        gpGLView->Update(currentMouseX, currentMouseY, false);
    }
        break;
    case WM_SIZE:
    {
        RECT windowRect;

        GetClientRect(hwnd, &windowRect);

        if (NULL != gpGLView)
        {
            gpGLView->Resize(windowRect.right, windowRect.bottom);
        }
    }
        break;
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        switch (wp)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return (DefWindowProc(hwnd, m, wp, lp));
}

void SetupPixelFormat(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pfd;

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;

    int pixelFormat(ChoosePixelFormat(hDC, &pfd));

    SetPixelFormat(hDC, pixelFormat, &pfd);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prev, LPSTR cmd, int show)
{
    srand((unsigned int)time(0));

    WNDCLASSEX windowClass;

    memset(&windowClass, 0, sizeof(WNDCLASSEX));

    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WndProc;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = NULL;
    windowClass.hIconSm = NULL;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)COLOR_ACTIVEBORDER;
    windowClass.lpszClassName = WINDOW_CLASS;

    if (!RegisterClassEx(&windowClass))
    {
        return -1;
    }

    HWND hwnd(CreateWindowEx(NULL,
                             WINDOW_CLASS,
                             WINDOW_TITLE,
                             WS_OVERLAPPEDWINDOW,
                             100, 100,
                             WINDOW_WIDTH, WINDOW_HEIGHT,
                             0,
                             0,
                             hInstance,
                             NULL));

    if (!hwnd)
    {
        return -1;
    }

    HDC hDC(GetDC(hwnd));

    SetupPixelFormat(hDC);

    HGLRC hRC(wglCreateContext(hDC));

    if (NULL == hRC)
    {
        return -1;
    }

    if (!wglMakeCurrent(hDC, hRC))
    {
        return -1;
    }

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;

    RECT windowRect;
    GetClientRect(hwnd, &windowRect);

    gpGLView = new GLView();
    if (gpGLView->Initialise(hDC, windowRect.right, windowRect.bottom) == 0)
    {
        while (true)
        {
            if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
                if (WM_QUIT == msg.message)
                {
                    break;
                }

                TranslateMessage(&msg);

                DispatchMessage(&msg);
            }
            else
            {
                gpGLView->Render();
            }
        }
    }

    delete gpGLView;

    wglMakeCurrent(hDC, NULL);

    wglDeleteContext(hRC);

    UnregisterClass(WINDOW_CLASS, windowClass.hInstance);

    return (int)msg.wParam;
}