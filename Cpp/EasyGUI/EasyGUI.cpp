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

struct MyHWnd *head;


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
  
	if (j[0] == "Window") {			
		string str = j["title"];
		
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
	
  //窗口组件的各种属性处理
  cout << j[1] << '\n';
  
  /*
	//创建窗口子控件 -- 列表循环  
  for (i=2; i<len(j); i++) {
    
		//可能有很多并列的子窗口，是否应该放到WndProc中的WM_PAINT中处理？
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
	}*/
}

/*
 * 显示/绘制窗口的顺序：先父后子，先兄后弟。
 */
void Show_Window(struct MyHWnd *tmp) {
	
	ShowWindow(tmp->curr, 1);
	UpdateWindow(tmp->curr);
		
	//子窗口
	if (tmp->child != NULL) {
		Show_Window(tmp->child);
	}
	
	//兄弟窗口
	if (tmp->next != NULL) {
		Show_Window(tmp->next);
	}
}

string to_uper(string s){
  transform(s.begin(), s.end(), s.begin(), ::toupper);
  return s;
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

  cout << j;
  return 0;
  
	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	wndClass.style          = CS_HREDRAW | CS_VREDRAW;
	//一个属于同一个窗口类的窗口公用一个窗口处理过程。
	wndClass.lpfnWndProc    = WndProc;
	wndClass.cbClsExtra     = 0;
	wndClass.cbWndExtra     = 0;
	wndClass.hInstance      = NULL;
	wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName   = NULL;
	wndClass.lpszClassName  = TEXT("MyClass");
	
	RegisterClass(&wndClass);
	
	head = (struct MyHWnd *)malloc(sizeof(struct MyHWnd));
	head->curr = NULL;
  strcpy(head->str, "");
	head->parent = NULL;
	head->child = NULL;
	head->next = NULL;
  
  if (j["first"][0] != "WINDOW" ) {
    cout << "顶层图形组件必须为Window\n";
    exit(1);
  }
	//创建并显示第一个窗口，json文件里剩余的窗口，通常在用户点击鼠标、键盘时创建。
	Create_Window(head, j["first"]);
	Show_Window(head);
	
	//消息循环
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	GdiplusShutdown(gdiplusToken);
  
  free(head);
	
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
      {
        PAINTSTRUCT pt;
        HDC hdc;
        hdc=BeginPaint(hWnd,&pt);
        
        SetTextColor(hdc,RGB(255,0,0));
        SetBkColor(hdc,RGB(0,255,0));
        SetBkMode(hdc,TRANSPARENT);
        //为什么矩形绘制成功，但是字体没有绘制呢？
        TextOut(hdc,0,0,TEXT("WM_PAINT"),strlen("WM_PAINT"));
        Rectangle(hdc,0,0,100,100);
        EndPaint(hWnd,&pt);
      }
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
}
