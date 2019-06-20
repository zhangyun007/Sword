#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <atlimage.h>

using namespace Gdiplus;

#pragma comment(lib, "gdiplus.lib") 
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib,"User32.lib")

VOID OnPaint(HDC hdc)
{
   Graphics graphics(hdc);
   Pen      pen(Color(255, 0, 0, 255));
   graphics.DrawLine(&pen, 0, 0, 200, 200);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
   HWND                hWnd;
   MSG                 msg;
   WNDCLASS            wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;
   
   // Initialize GDI+.
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
   
   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT("GettingStarted");
   
   RegisterClass(&wndClass);
   
   hWnd = CreateWindow(
      TEXT("GettingStarted"),   // window class name
      TEXT("Getting Started"),  // window caption
      WS_OVERLAPPEDWINDOW,      // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
      CW_USEDEFAULT,            // initial x size
      CW_USEDEFAULT,            // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters
      
   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);
   
   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain


void SaveDC2BMP(HWND hwnd, TCHAR *path)
{
    HBITMAP hBitmap;
    HDC hdc, hTempDC;
    RECT rect;
    int w, h;
    
    
    hdc = ::GetDC(hwnd);
    ::GetClientRect(hwnd, &rect);
 
    w = rect.right - rect.left;
    h = rect.bottom - rect.top;
 
    hTempDC = ::CreateCompatibleDC(hdc);
    hBitmap = ::CreateCompatibleBitmap(hdc, w, h);
    ::SelectObject(hTempDC, hBitmap);
 
    ::BitBlt(hTempDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
 
    CImage image;
    image.Attach(hBitmap);
    image.Save(path);
    
    ::DeleteDC(hTempDC);
    ::DeleteObject(hBitmap);
    ::ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
   HDC          hdc;
   PAINTSTRUCT  ps;
   
   switch(message)
   {
   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      OnPaint(hdc);
      EndPaint(hWnd, &ps);

	  //获取可执行文件所在的目录
	  char dir[64];
	  GetCurrentDirectory(64, dir);
	  
	  char file[74];
	  strcpy(file, dir);
	  strcat(file, "\\test.bmp");
	  //MessageBox(hWnd, file, "提示", MB_OK); 
	  
	  //保存图片到磁盘文件
	  SaveDC2BMP(hWnd, file);
	  
      return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc
