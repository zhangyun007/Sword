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

#define Safe_Release(p) if((p)) (p)->Release();

// window handles, class and caption text.
HWND g_hwnd;
HINSTANCE g_inst;
static char g_class_name[] = "ParticleClass";
static char g_caption[]    = "Particle Demo";

// the Direct3D and device object
IDirect3D9* g_d3d = NULL;
IDirect3DDevice9* g_d3d_device = NULL;

// the particle vertex buffer and texture
IDirect3DVertexBuffer9* g_particle_vb = NULL;
IDirect3DTexture9*      g_particle_texture = NULL;

// The particle vertex format and descriptor
typedef struct
{
    float x, y, z;      // 3D coordinates    
    D3DCOLOR diffuse;   // color
    float u, v;         // texture coordinates
} VERTEX;

#define VERTEX_FVF   (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// create a structure for tracking particles
struct PARTICLE
{
    float x_pos, y_pos, z_pos;  // coordinate
    float x_add, y_add, z_add;  // movement values
    float red, green, blue;     // colors
    long  timer, counter;       // current and update counter

    PARTICLE()
    {
        // position particle at origin
        x_pos = y_pos = z_pos = 0.0;

        // get a random update counter
        counter = rand() % 50 + 10;
        timer = 0;

        // get a random speed
        x_add = (float)(rand() % 11) - 5.0;
        y_add = (float)(rand() % 11) - 5.0;
        z_add = (float)(rand() % 11) - 5.0;

        // get a random color
        red   = (float)(rand() % 101) / 100.0;
        green = (float)(rand() % 101) / 100.0;
        blue  = (float)(rand() % 101) / 100.0;
    }
};

PARTICLE* g_particles = NULL;

//--------------------------------------------------------------------------------
// Window procedure.
//--------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------
// Copy vertex data into vertex buffer, create texture from file.
//--------------------------------------------------------------------------------
BOOL Setup_Particles()
{
    BYTE* vertex_ptr;

    VERTEX verts[] = {
        { -50.0f, 50.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f },
        {  50.0f, 50.0f, 0.0f, 0xFFFFFFFF, 1.0f, 0.0f },
        { -50.0f,  0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 1.0f },
        {  50.0f,  0.0f, 0.0f, 0xFFFFFFFF, 1.0f, 1.0f }
    };    

    // create vertex buffers and stuff in data       
    if(FAILED(g_d3d_device->CreateVertexBuffer(sizeof(verts), 0, VERTEX_FVF, D3DPOOL_DEFAULT, &g_particle_vb, NULL)))   
        return FALSE;   

    // locks a range of vertex data and obtains a pointer to the vertex buffer memory
    if(FAILED(g_particle_vb->Lock(0, 0, (void**)&vertex_ptr, 0)))
        return FALSE;

    memcpy(vertex_ptr, verts, sizeof(verts));

    // unlocks vertex data
    g_particle_vb->Unlock();    

    // get textures    
    D3DXCreateTextureFromFile(g_d3d_device, "Particle.bmp", &g_particle_texture);    
    
    // create some particles
    g_particles = new PARTICLE[512];

    return TRUE;
}

//--------------------------------------------------------------------------------
// Initialize d3d, d3d device, vertex buffer, texutre; set render state for d3d;
// set perspective matrix.
//--------------------------------------------------------------------------------
BOOL Do_Init()
{
    D3DPRESENT_PARAMETERS present_param;
    D3DDISPLAYMODE  display_mode;
    D3DXMATRIX mat_proj, mat_view;    

    // do a windowed mode initialization of Direct3D
    if((g_d3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return FALSE;

    // retrieves the current display mode of the adapter
    if(FAILED(g_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode)))
        return FALSE;

    ZeroMemory(&present_param, sizeof(present_param));

    // initialize d3d presentation parameter
    present_param.Windowed               = TRUE;
    present_param.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    present_param.BackBufferFormat       = display_mode.Format;
    present_param.EnableAutoDepthStencil = TRUE;
    present_param.AutoDepthStencilFormat = D3DFMT_D16;

    // creates a device to represent the display adapter
    if(FAILED(g_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hwnd,
                                  D3DCREATE_SOFTWARE_VERTEXPROCESSING, &present_param, &g_d3d_device)))
        return FALSE;     

    // set render state

    // enable d3d lighting
    g_d3d_device->SetRenderState(D3DRS_LIGHTING, TRUE);
    // enable z-buffer
    g_d3d_device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // set ambient light to highest level (to see particles)
    g_d3d_device->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);

    // create and set the projection matrix

    // builds a left-handed perspective projection matrix based on a field of view
    D3DXMatrixPerspectiveFovLH(&mat_proj, D3DX_PI/4.0, 1.0, 1.0, 1000.0);

    // sets a single device transformation-related state
    g_d3d_device->SetTransform(D3DTS_PROJECTION, &mat_proj);

    // create and set the view transformation
    D3DXMatrixLookAtLH(&mat_view, &D3DXVECTOR3(0.0f, 0.0f, -500.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
                       &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

    g_d3d_device->SetTransform(D3DTS_VIEW, &mat_view);

    // create the meshes
    Setup_Particles();    

    return TRUE;
}

//--------------------------------------------------------------------------------
// Release all d3d resource.
//--------------------------------------------------------------------------------
BOOL Do_Shutdown()
{
    delete[] g_particles;

    Safe_Release(g_particle_vb);
    Safe_Release(g_particle_texture);    
    Safe_Release(g_d3d_device);
    Safe_Release(g_d3d);

    return TRUE;
}

//--------------------------------------------------------------------------------
// Render a frame.
//--------------------------------------------------------------------------------
BOOL Do_Frame()
{
    D3DXMATRIX mat_view, mat_world, mat_transposed, mat_transform;
    static D3DMATERIAL9 s_material;
    static BOOL  s_is_mat_init = TRUE;
    static DWORD s_counter = timeGetTime();

    // limit to 30fps
    if(timeGetTime() < s_counter+33)
        return TRUE;

    s_counter = timeGetTime();

    // configure the material if first time called
    if(s_is_mat_init = TRUE)
    {
        s_is_mat_init = FALSE;
        ZeroMemory(&s_material, sizeof(s_material));
        s_material.Diffuse.a = s_material.Ambient.a = 0.5f;
    }

    // clear device back buffer
    g_d3d_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 64, 128, 255), 1.0f, 0);    

    // Begin scene
    if(SUCCEEDED(g_d3d_device->BeginScene()))
    {
        // set the particle source, shader, texture.            
        g_d3d_device->SetStreamSource(0, g_particle_vb, 0, sizeof(VERTEX));
        g_d3d_device->SetFVF(VERTEX_FVF);
        g_d3d_device->SetTexture(0, g_particle_texture);

        // get and set the transposed view matrix (billboard technique)
        g_d3d_device->GetTransform(D3DTS_VIEW, &mat_view);
        D3DXMatrixTranspose(&mat_transposed, &mat_view);

        // enable alpha blending
        g_d3d_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
        g_d3d_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        g_d3d_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);    

        // loop through all particles and draw them
        for(short i = 0; i < 512; i++)
        {
            // move particle first
            g_particles[i].x_pos += g_particles[i].x_add;
            g_particles[i].y_pos += g_particles[i].y_add;
            g_particles[i].z_pos += g_particles[i].z_add;

            // reverse movements if past counter
            if((g_particles[i].timer += 1) >= g_particles[i].counter)
            {
                g_particles[i].timer = 0;
                g_particles[i].x_add *= -1.0f;
                g_particles[i].y_add *= -1.0f;
                g_particles[i].z_add *= -1.0f;
            }

            // setup the particle's world transformation
            D3DXMatrixTranslation(&mat_transform, g_particles[i].x_pos, g_particles[i].y_pos, g_particles[i].z_pos);
            D3DXMatrixMultiply(&mat_world, &mat_transform, &mat_transposed);
            g_d3d_device->SetTransform(D3DTS_WORLD, &mat_world);

            // set the particle's material
            s_material.Diffuse.r = s_material.Ambient.r = g_particles[i].red;
            s_material.Diffuse.g = s_material.Ambient.g = g_particles[i].green;
            s_material.Diffuse.b = s_material.Ambient.b = g_particles[i].blue;
                
            // Sets the material properties for the device
            g_d3d_device->SetMaterial(&s_material);

            // draw the particle
            g_d3d_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        }        

        // release texture
        g_d3d_device->SetTexture(0, NULL);

        // end the scene
        g_d3d_device->EndScene();
    }

    // present the contents of the next buffer in the sequence of back buffers owned by the device
    g_d3d_device->Present(NULL, NULL, NULL, NULL);

    return TRUE;
}

//--------------------------------------------------------------------------------
// Main function, routine entry.
//--------------------------------------------------------------------------------
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
    if(Do_Init() == FALSE)
        return FALSE;

    // start message pump, waiting for signal to quit.
    ZeroMemory(&msg, sizeof(MSG));

    while(msg.message != WM_QUIT)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        // draw a frame
        if(Do_Frame() == FALSE)
            break;
    }

    // run shutdown function
    Do_Shutdown();

    UnregisterClass(g_class_name, inst);
    
    return (int) msg.wParam;
}