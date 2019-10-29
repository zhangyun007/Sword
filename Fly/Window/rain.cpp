//WinXP用DirectX9.0,Win7不支持9.0
//Dirext11 SDK下载地址：http://download.microsoft.com/download/F/1/7/F178BCE4-FA19-428F-BB60-F3DEE1130BFA/DXSDK_Feb10.exe

#pragma once

#include <Windows.h>

#pragma region Undefine Windows Macros
// Only undefine, if DXGIType.h has not been included yet
    #ifndef __dxgitype_h__
        #undef DXGI_STATUS_OCCLUDED
        #undef DXGI_STATUS_CLIPPED
        #undef DXGI_STATUS_NO_REDIRECTION
        #undef DXGI_STATUS_NO_DESKTOP_ACCESS
        #undef DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE
        #undef DXGI_STATUS_MODE_CHANGED
        #undef DXGI_STATUS_MODE_CHANGE_IN_PROGRESS
        #undef DXGI_ERROR_INVALID_CALL
        #undef DXGI_ERROR_NOT_FOUND
        #undef DXGI_ERROR_MORE_DATA
        #undef DXGI_ERROR_UNSUPPORTED
        #undef DXGI_ERROR_DEVICE_REMOVED
        #undef DXGI_ERROR_DEVICE_HUNG
        #undef DXGI_ERROR_DEVICE_RESET
        #undef DXGI_ERROR_WAS_STILL_DRAWING
        #undef DXGI_ERROR_FRAME_STATISTICS_DISJOINT
        #undef DXGI_ERROR_GRAPHICS_VIDPN_SOURCE_IN_USE
        #undef DXGI_ERROR_DRIVER_INTERNAL_ERROR
        #undef DXGI_ERROR_NONEXCLUSIVE
        #undef DXGI_ERROR_NOT_CURRENTLY_AVAILABLE
        #undef DXGI_ERROR_REMOTE_CLIENT_DISCONNECTED
        #undef DXGI_ERROR_REMOTE_OUTOFMEMORY
        #undef D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS
        #undef D3D11_ERROR_FILE_NOT_FOUND
        #undef D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS
        #undef D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD
        #undef D3D10_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS
        #undef D3D10_ERROR_FILE_NOT_FOUND
    #endif
#pragma endregion

#include <D3D11.h>
#include <d3dx11.h>

#include <strsafe.h>
#include <time.h>

#define PARTICLENUM 5000
struct CUSTOMVERTEX
{ 
    float x,y,z;   //顶点位置
    float u,v;   ///顶点纹理坐标
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)
// 雨点粒子结构
struct RainParticle
{ 
    float x,y,z;          //位置
    float fDspeed;     //下降速度
};
struct RAINVERTEX
{
    D3DXVECTOR3 VpOS;
    DWORD dwColor;
};
#define D3DFVF_RAINVERTEX (D3DFVF_XYZ |D3DFVF_DIFFUSE)
RainParticle rain[PARTICLENUM];        // 雨点粒子数组    
LPDIRECT3D9 g_pD3D = NULL;         // D3D对象
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;    // D3D渲染设备
LPDIRECT3DVERTEXBUFFER9 g_pRainVB = NULL;   //雨点粒子缓冲区
D3DXMATRIX g_matRain;                 // 雨点世界矩阵
D3DXVECTOR3 g_RainDir;                // 雨点的下降方向
DWORD iTime = 0;
HRESULT InitD3D(HWND hWnd)
{
    if(NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp,sizeof(d3dpp));
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&g_pd3dDevice)))
        return E_FAIL;
    if(FAILED(g_pd3dDevice->CreateVertexBuffer(sizeof(RAINVERTEX),0,D3DFVF_RAINVERTEX,D3DPOOL_MANAGED,&g_pRainVB,NULL)))
        return E_FAIL;
    //填充雨点顶点缓冲区
    RAINVERTEX * pRainVertices;
    g_pRainVB->Lock(0,0,(void**)&pRainVertices,0);
    pRainVertices[0].VpOS = D3DXVECTOR3(0,5,0);
    pRainVertices[0].dwColor = 0xffffffff;
    pRainVertices[1].VpOS = D3DXVECTOR3(1,0,0);
    pRainVertices[1].dwColor = 0xffffffff;
    g_pRainVB->Unlock();
    g_RainDir = D3DXVECTOR3(1,0,0) - D3DXVECTOR3(0,5,0);
    D3DXVec3Normalize(&g_RainDir,&g_RainDir);
    srand((unsigned)time(NULL));
    //初始化雨点位置和方向
    //使得雨点的x位置在[-200,200]之间，y的位置在[-200,200]之间，z的位置在[0,250]之间，控制速度。
    for(int i=0;i<PARTICLENUM;i++)
    {
        rain[i].x = float(rand()%400-200);
        rain[i].y = float(rand()%400-200);
        rain[i].z = 0.0f + float(rand()%250);
        rain[i].fDspeed =10.0f + (rand()%40);
    }
    g_pd3dDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE,true);
    iTime = timeGetTime();
    D3DXMATRIXA16 matProj;
    float fAspectRatio = 3.0/4;
    D3DXMatrixPerspectiveFovLH(&matProj,D3DX_PI/3,fAspectRatio,1.0,500.0f);
    g_pd3dDevice->SetTransform(D3DTS_PROJECTION,&matProj);
    D3DXVECTOR3 vEyept(0.0f,0.0f,1000.0f);
    D3DXVECTOR3 vLookatpt(0.0f,0.0f,0.0f);
    D3DXVECTOR3 vUpVec(0.0f,1.0f,0.0f);
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH(&matView,&vEyept,&vLookatpt,&vUpVec);
    return S_OK;
}
void Cleanup()
{
    if(g_pd3dDevice != NULL)
        g_pd3dDevice->Release();


    if(g_pD3D != NULL)
        g_pD3D->Release();
}
void Render()
{
    if(NULL == g_pd3dDevice)
        return ;
    //通过速度计算出雨点新位置
    for(int i=0;i<PARTICLENUM;i++)
    {
        if(rain[i].y < -200)
            rain[i].y = 250.0f;
        if(rain[i].x > 200)
            rain[i].x = -200.0f;
        if(rain[i].z>300)
            rain[i].z = float(rand()%500-250);
        rain[i].x += rain[i].fDspeed * g_RainDir.x * 0.03;
        rain[i].y += rain[i].fDspeed * g_RainDir.y * 0.03;
        rain[i].z += rain[i].fDspeed * g_RainDir.z * 0.03;
    }
    g_pd3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_ARGB(0,45,50,170),1.0f,0);

    if(SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        g_pd3dDevice->SetTexture(0,NULL);
        for(int i=0;i<PARTICLENUM;i++)
        {
            //最后使用旋转矩阵，将粒子的为孩子不断更新，并且渲染。
            D3DXMatrixTranslation(&g_matRain,rain[i].x,rain[i].y,rain[i].z);
            g_pd3dDevice->SetTransform(D3DTS_WORLD,&g_matRain);


            g_pd3dDevice->SetStreamSource(0,g_pRainVB,0,sizeof(RAINVERTEX));
            g_pd3dDevice->SetFVF(D3DFVF_RAINVERTEX);
            g_pd3dDevice->DrawPrimitive(D3DPT_LINELIST,0,1);
        }
        g_pd3dDevice->EndScene();
    }
        g_pd3dDevice->Present(NULL,NULL,NULL,NULL);
}
LRESULT WINAPI MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY:
        Cleanup();
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd,msg,wParam,lParam);
}
INT WINAPI WinMain(HINSTANCE hInst,HINSTANCE,LPSTR,INT)
{
    WNDCLASSEX wc = {sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0L,0L,GetModuleHandle(NULL),NULL,NULL,NULL,NULL,L"Directx",NULL};
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindow(L"Directx",L"粒子系统雨点",WS_OVERLAPPEDWINDOW,100,100,600,600,NULL,NULL,wc.hInstance,NULL);
    if(SUCCEEDED(InitD3D(hWnd)))
    {
        ShowWindow(hWnd,SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
        MSG msg;
        ZeroMemory(&msg,sizeof(msg));
        while(msg.message != WM_QUIT)
        {
            if(PeekMessage(&msg,NULL,0U,0U,PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                Render();
            }
        }


    }
    UnregisterClass(L"Directx",wc.hInstance);
    return 0;
}