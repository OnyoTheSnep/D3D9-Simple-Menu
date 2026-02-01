#pragma once

// global declarations
extern LPDIRECT3D9 d3d;				// the pointer to our Direct3D interface
extern LPDIRECT3DDEVICE9 d3ddev;	// the pointer to the device class

// function prototypes
void initD3D(HWND hWnd);			// sets up and initializes Direct3D
void render_frame(void);			// renders a single frame
void cleanD3D(void);				// closes Direct3D and releases memory

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
