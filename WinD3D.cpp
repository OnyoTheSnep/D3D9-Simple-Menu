#include "main.h"
#include "Example.h"

LPDIRECT3D9 d3d = nullptr;
LPDIRECT3DDEVICE9 d3ddev = nullptr;
Menu* menu;

// --  --  --  --  --  --  --  --  --  --  --  --

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
    {
        DestroyWindow(hWnd);
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    } 

    break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);     // create the Direct3D interface
    D3DPRESENT_PARAMETERS d3dpp;                // create a struct to hold various device information
    ZeroMemory(&d3dpp, sizeof(d3dpp));          // clear out the struct for use

    d3dpp.Windowed = TRUE;                      // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   // discard old frames
    d3dpp.hDeviceWindow = hWnd;                 // set the window to be used by Direct3D

    d3d->CreateDevice(D3DADAPTER_DEFAULT, 
        D3DDEVTYPE_HAL, hWnd, 
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
        &d3dpp, &d3ddev);                       // create a device class using this information and the info from the d3dpp stuct
}

void render_frame(void)
{
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0); // clear the window to a deep blue
    d3ddev->BeginScene(); // begins the 3D scene

    // do 3D rendering on the back buffer here
    doOnce(menu);
    menu->Render();
    menu->KeyboardCapture(200/*250*/);
    // end rendering

    d3ddev->EndScene(); // ends the 3D scene
    d3ddev->Present(NULL, NULL, NULL, NULL); // displays the created frame on the screen
}

void cleanD3D(void)
{
    d3ddev->Release();  // close and release the 3D device
    d3d->Release();     // close and release Direct3D
}