#include <windows.h>
#include <stdio.h>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma warning(disable : 4305 4244)

#define WINDOW_WIDTH    400
#define WINDOW_HEIGHT   400

// window handles, class and caption text.
HWND g_hwnd;
HINSTANCE g_inst;
static char g_class_name[] = "ParticleClass";
static char g_caption[]    = "Particle Demo";

LPDIRECT3D9			g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pDevice = NULL;

HRESULT InitD3D(HWND hwnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}
 
	D3DPRESENT_PARAMETERS d3dpparams;
	ZeroMemory(&d3dpparams, sizeof(d3dpparams));
	d3dpparams.Windowed = true;
	d3dpparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpparams.BackBufferFormat = D3DFMT_UNKNOWN;
 
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									hwnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&d3dpparams,
									&g_pDevice)))
	{
		return E_FAIL;
	}
 
	return S_OK;
}

void Cleanup()
{
	if (NULL != g_pDevice)
	{
		g_pDevice->Release();
	}
	if (NULL != g_pD3D)
	{
		g_pD3D->Release();
	}
}

void Render()
{
	if (NULL == g_pDevice)
	{
		return;
	}
 
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 0), 1.0f, 0);
 
	if (SUCCEEDED(g_pDevice->BeginScene()))
	{
		// render ...
		
		g_pDevice->EndScene();		
	}
 
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}

long WINAPI Window_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return (long) DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR cmd_line, int cmd_show)
{
    WNDCLASSEX  win_class;
    MSG         msg;

    g_inst = inst;

    // create window class and register it
    win_class.cbSize        = sizeof(win_class);
    win_class.style         = CS_CLASSDC;
    win_class.lpfnWndProc   = Window_Proc;
    win_class.cbClsExtra    = 0;
    win_class.cbWndExtra    = 0;
    win_class.hInstance     = inst;
    win_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    win_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
    win_class.hbrBackground = NULL;
    win_class.lpszMenuName  = NULL;
    win_class.lpszClassName = g_class_name;
    win_class.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(! RegisterClassEx(&win_class))
        return FALSE;

    // create the main window
    g_hwnd = CreateWindow(g_class_name, g_caption, WS_CAPTION | WS_SYSMENU, 0, 0,
                          WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, inst, NULL);

    if(g_hwnd == NULL)
        return FALSE;

    ShowWindow(g_hwnd, SW_NORMAL);
    UpdateWindow(g_hwnd);

    // initialize game
    if(InitD3D(g_hwnd) == E_FAIL)
        return FALSE;

    // start message pump, waiting for signal to quit.
    ZeroMemory(&msg, sizeof(MSG));

    while(msg.message != WM_QUIT)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
			Render();
		}
    }

    // run shutdown function
    Cleanup();

    UnregisterClass(g_class_name, inst);
    
    return (int) msg.wParam;
}