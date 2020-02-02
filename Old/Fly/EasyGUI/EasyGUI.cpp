#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <windows.h>

#include "json.hpp"
// for convenience
using json = nlohmann::json;

using namespace std;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib") 
#pragma comment(lib, "gdiplus.lib") 
#pragma comment(lib, "gdi32.lib")

/*
 *绘制矩形区域的顺序：先父后子，先兄后弟。
 */
void Draw_Window(json j) {
	
	MSG  msg ;    
	
	if (j["TopLevel"][0]["Name"] == "Div") {		
		WNDCLASSW wc = {0};
		wc.lpszClassName = L"DivClass";
		wc.hInstance     = NULL;
		//wc.hbrBackground = GetSysColorBrush(RGB(255, 0, 0));
		//wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
		wc.hbrBackground = CreateSolidBrush(RGB(0xff,0xff,0xff));
		wc.lpfnWndProc   = DefWindowProc;
		wc.hCursor       = LoadCursor(0, IDC_ARROW);
	
		RegisterClassW(&wc);
		
		string str = j["TopLevel"][0]["Title"];
		cout << str << "\n";
		
		// WS_DLGFRAME表示窗口不带标题栏
		HWND hWnd = CreateWindowW(wc.lpszClassName, (LPCWSTR)str.c_str(),
					//WS_POPUP | WS_VISIBLE,
					WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
					CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, 0, 0);  
						
		HDC hdc= GetDC(hWnd);
		//HDC hdc = GetWindowDC(GetDesktopWindow());
		
		if (j["TopLevel"][0]["Child"]["Name"] == "Text") {
			cout << "Text!!!\n";
			HPEN hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HPEN hpen_old = (HPEN)SelectObject(hdc, hpen);
			//参数：桌面句柄，XY坐标，文字，文字宽度
			TextOutA(hdc, 400, 400, "hahahahaah", 12);
			Ellipse(hdc,200,150,300,250);
			ReleaseDC(hWnd, hdc); //一定要释放句柄
		}	
		
		//SW_MAXIMIZE，全屏幕显示（看不见底层的任务栏），不等于窗口最大化。
		ShowWindow(hWnd, SW_MAXIMIZE);
		UpdateWindow(hWnd);
		
		while(GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}		
	} 
}

int main() {
	//system("chcp 65001");
	
	// read a JSON file
	std::ifstream i("test.json");
	json j;
	i >> j;
	
	cout << j["TopLevel"][0]["Name"];
	
	Draw_Window(j);
	
	return 0;
}