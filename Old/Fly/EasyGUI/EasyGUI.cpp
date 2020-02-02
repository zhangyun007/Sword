#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace Gdiplus;
using namespace std;

#include "json.hpp"
// for convenience
using json = nlohmann::json;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib") 
#pragma comment(lib, "gdiplus.lib") 
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/*
 *绘制矩形区域的顺序：先父后子，先兄后弟。
 */
void Draw_Window(json j, HINSTANCE hInstance, int iCmdShow) {
	if (j["TopLevel"][0]["Name"] == "Div") {			
		string str = j["TopLevel"][0]["Title"];
		cout << str << "\n";
		
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
   	
		if (j["TopLevel"][0]["Child"]["Name"] == "Text") {
			cout << "Text!!!\n";
		}	
		
		GdiplusShutdown(gdiplusToken);
	} 
}

VOID OnPaint(HDC hdc)
{
   Graphics graphics(hdc);
   Pen      pen(Color(255, 0, 0, 255));
   graphics.DrawLine(&pen, 0, 0, 200, 200);
}

int WINAPI WinMain(
                HINSTANCE hInstance,     // handle to current instance
                HINSTANCE hPrevInstance, // handle to previous instance
                LPSTR lpCmdLine,         // command line
                int nCmdShow             // show state
){
	
	//system("chcp 65001");
	
	// read a JSON file
	std::ifstream i("test.json");
	json j;
	i >> j;
	
	cout << j["TopLevel"][0]["Name"];
	
	Draw_Window(j, hInstance, nCmdShow);

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
	  
      return 0;
   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
}
