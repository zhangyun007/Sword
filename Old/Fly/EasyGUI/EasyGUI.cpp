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

struct MyHWnd {
	HWND curr;				//窗口句柄
	char str[64];			//窗口要显示的文本
	struct MyHWnd *parent;	//父窗口
	struct MyHWnd *child;	//第一个子窗口
	struct MyHWnd *next;	//兄弟窗口
};

struct MyHWnd *first;


void Draw_Text(HWND hWnd, char *str) {
	HDC          hdc;
	PAINTSTRUCT  ps;
	
	hdc = BeginPaint(hWnd, &ps);
	
	Graphics graphics(hdc);
	
	Pen      pen(Color(255, 0, 0, 255));
	graphics.DrawLine(&pen, 0, 0, 200, 200);
   
	SolidBrush brush(Color::Red);  
	Font *f = new Font(L"Times new roman", 16);
	graphics.DrawString(L"AAAAA", 5, f, PointF(0,0), &brush);
	
	EndPaint(hWnd, &ps);
}

void Create_Window(struct MyHWnd *tmp, json j) { 

	HWND 		hwnd;
	
	cout << "in top level\n"<< j << endl;
	
	if (j["Name"] == "Window") {			
		string str = j["Title"];
		
		if (tmp->parent == NULL) {
			hwnd = CreateWindow(
				TEXT("MyClass"),   			// window class name
				TEXT(str.c_str()),  		// window caption
				WS_OVERLAPPEDWINDOW,     	// window style
				CW_USEDEFAULT,           	// initial x position
				CW_USEDEFAULT,           	// initial y position
				CW_USEDEFAULT,           	// initial x size
				CW_USEDEFAULT,           	// initial y size
				NULL,						// parent window handle
				NULL,                     	// window menu handle
				NULL,          			  	// program instance handle
				NULL);                    	// creation parameters			
		} else {
			hwnd = CreateWindow(
				TEXT("MyClass"),   			// window class name
				TEXT(str.c_str()),  		// window caption
				WS_OVERLAPPEDWINDOW | WS_CHILD,      	// window style
				CW_USEDEFAULT,            	// initial x position
				CW_USEDEFAULT,            	// initial y position
				CW_USEDEFAULT,            	// initial x size
				CW_USEDEFAULT,            	// initial y size
				tmp->parent->curr,        	// parent window handle
				NULL,                     	// window menu handle
				NULL,          			  	// program instance handle
				NULL);                    	// creation parameters
		}
		tmp->curr = hwnd;
	} 
	
	//创建子窗口 -- 列表循环
	for (auto i: j["Child"]) {
		
		cout << " ---- in for level\n"<< i << endl;
		
		//可能有很多并列的子窗口，是否应该放到WndProc中的WM_PAINT中处理？
		if (i["Name"] == "Window") {
			if (tmp->child == NULL) {
				//第一个子窗口
				tmp->child = (struct MyHWnd*)malloc(sizeof(struct MyHWnd));
				tmp->child ->curr = NULL;
				tmp->child ->parent = tmp;
				tmp->child ->child = NULL;
				tmp->child ->next = NULL;
				Create_Window(tmp->child, i);
			} else {
				//第一个子窗口的兄弟窗口
				tmp->child->next = (struct MyHWnd*)malloc(sizeof(struct MyHWnd));
				tmp->child->next->curr = NULL;
				tmp->child->next->parent = tmp;
				tmp->child->next->child = NULL;
				tmp->child->next->next = NULL;
				Create_Window(tmp->child->next, i);
			}
		}
		if (i["Name"] == "Text") {
			//strcpy(tmp->str, i["Caption"]);
		}	
	}
}

/*
 * 显示/绘制窗口的顺序：先父后子，先兄后弟。
 */
void Show_Window(struct MyHWnd *tmp) {
	
	ShowWindow(tmp->curr, 1);
	UpdateWindow(tmp->curr);
	
	if (tmp->str != "") {
		Draw_Text(tmp->curr, tmp->str);
	}
	
	//子窗口
	if (tmp->child != NULL) {
		Show_Window(tmp->child);
	}
	
	//兄弟窗口
	if (tmp->next != NULL) {
		Show_Window(tmp->next);
	}
}

int main() {
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	MSG                 msg;
	WNDCLASS            wndClass;
	
	// read a JSON file
	std::ifstream i("test.json");
	json j;
	i >> j;
	
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	wndClass.style          = CS_HREDRAW | CS_VREDRAW;
	//一个类公用一个窗口处理过程
	wndClass.lpfnWndProc    = DefWindowProc;
	wndClass.cbClsExtra     = 0;
	wndClass.cbWndExtra     = 0;
	wndClass.hInstance      = NULL;
	wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName   = NULL;
	wndClass.lpszClassName  = TEXT("MyClass");
	
	RegisterClass(&wndClass);
	
	first = (struct MyHWnd *)malloc(sizeof(struct MyHWnd));
	first->curr = NULL;
	first->parent = NULL;
	first->child = NULL;
	first->next = NULL;
	
	//绘制第一个窗口
	Create_Window(first, j[0]);
	Show_Window(first);
	
	//消息循环
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	GdiplusShutdown(gdiplusToken);
	
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{   
   switch(message) {
		//设置Edit控件的文本
		case WM_SETTEXT:
		//子窗口的绘制应该放在WM_PAINT消息中
		case WM_PAINT:
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
}
