#include "main.h"

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
        L"WindowClass",
        L"Our First Direct3D Program",
        WS_OVERLAPPEDWINDOW,
        300, 300,
        800, 600,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hWnd, nCmdShow);

    // set up and initialize Direct3D
    initD3D(hWnd);

    // enter the main loop:
    MSG msg;
    while (TRUE)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        if (!IsWindow(hWnd))
            break;

        render_frame();
    }

    // clean up DirectX and COM
    cleanD3D();

    return msg.wParam;
}
