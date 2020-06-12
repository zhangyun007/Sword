#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

#include "../TinySTL/TObject.hpp"

//用于函数SetConsoleOutputCP(65001);更改cmd编码为utf8

using namespace Gdiplus;
using namespace std;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "gdi32.lib")

#define IDT_TIMER1 12
    
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
        
//得到一行文本的头一个单词。
string Get_First(string line) {
  string s = "";
  for (int i=0; i<line.length(); i++) {
    if (line[i] != ' ' && line[i] != '\t')
      s += line[i];
    else
      break;
  }
  return s;
}

//去掉line开头的空白字符。
string skip_blank(string line) {
  for (int i=0; i<line.length(); i++) {
    if (line[i]!=' ' && line[i]!='\t')
      return line.substr(i, line.length()-i);
  }
  return line;
}

class GUI_Element {
public:  
  unsigned short Level;   //控件在第几Level？
  string Name;  //控件名称 ，可能的Val为"<window>" "<text>" "<div>" ...
  map<string, string> Property; //控件属性  titile=1, 1为Val的index.
  vector<string> Val;           // GUI描述中的字符串
  
  HWND 		hwnd;                   //当前控件的句柄
  
  class GUI_Element *parent;      //父节点
  class GUI_Element *child;      //第一个子节点
  class GUI_Element *brother;    //第一个兄弟节点

  GUI_Element(string line);  
  
  /*将带空格的字符串存储到vector<string> val中，并用对应的vector下标来替换字符串。
  这么做的目的是为了方便做词法分析：以空格为间隔。*/
  string String_2_Int(string line);
  
  //创建并绘制控件
  void Create_Element();
};

//line是文件中的一行：1 window title="第一个窗口"
GUI_Element::GUI_Element(string line) {
  string l = String_2_Int(line);
  
  string s = Get_First(line);
                            
  for (int i=0; i<s.length(); i++){
    if (!isdigit(s[i])) {
      cout << "You should start with Level number.\n";
      return;
    }
  }
  
  Level = atoi(s.c_str());
  
  Name = Get_First(skip_blank(line.substr(s.length())));
  
  cout << Level << ", "<< Name << "\n";
}

//字符串存到vector里，存下标，这样就消除了line中的空格。
string GUI_Element::String_2_Int(string line){
  string str = "";
  string s = "";
  char m[4] = "";
  short n=0;
   
  int i = 0;
  while (1) {
    while (line[i] != '\"') {
      str+=line[i];
      if (i == (line.length()-1))
        return str;
      i++;
    }
    i++;
    
    while (line[i] != '\"') {
      s+=line[i];
      if (i == (line.length()-1)) {
        cout << " “不成对。\n";
        exit(0);
      }
      i++;
    }
    
    Val.push_back(s);
    itoa(n, m, 4);
    str+=m;
    n++;
    
    if (i == (line.length()-1))
      break;
    i++;
  }
  return str;
}

//创建并绘制控件，先父后子，先兄后弟。
void GUI_Element::Create_Element() {
  
  if (Name == "<WINDOW>") {
    cout << "will create a window\n";
    MSG                 msg;
    WNDCLASS            wndClass;
    
    wndClass.style          = CS_HREDRAW | CS_VREDRAW;
    //同一窗口类公用一个窗口处理过程，窗口处理过程要分析gs文件的内容才能知道。
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
    
    hwnd = CreateWindow(
      TEXT("MyClass"),   			  // window class name
      TEXT("First Window"),  		// window caption
      WS_OVERLAPPEDWINDOW,     	// window style
      CW_USEDEFAULT,           	// initial x position
      CW_USEDEFAULT,           	// initial y position
      CW_USEDEFAULT,           	// initial x size
      CW_USEDEFAULT,           	// initial y size
      NULL,						            // parent window handle
      NULL,                     	// window menu handle
      NULL,          			  	    // program instance handle
      NULL);                    	// creation parameters			
      
    SetTimer(hwnd,             // handle to main window 
      IDT_TIMER1,            // timer identifier 
      1000,                 // 10-second interval 
      (TIMERPROC) NULL);     // no timer callback 
    
            SetWindowText(hwnd, "aaa");

    ShowWindow(hwnd, 1);
    UpdateWindow(hwnd);
    
    //消息循环
    while(GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  
  if (Name == "<TEXT>") {
    str = "";
    //找到上Level窗口句柄
    InvalidateRect(parent->hwnd, NULL, TRUE);
  }
}

//读取GUI描述文件和GS脚本文件，生成图形程序。
void read_gui(string gui){
  ifstream in(gui);
  string line;
      
  MyAssert(Get_First("hedllo world"), "hedllo");
  
  if (in) {
      
    int last = -1;
    // line中不包括每行的换行符
    while (getline (in, line)) { 
    
      line = skip_blank(line);
      cout << line << endl;
          
      if (line[0] == ';')
        continue;                
                      
      if (line!="") {
        class GUI_Element con(line);
        
        if (last == -1) {
          if (con.Level == 1) {
              last = 1;
              //... 创建顶Level窗口
              con.Create_Element();
          } else {
            cout << "You should start from Level 1.\n";
            return;
          }
        } else {
          if (con.Level - last == 1) {
              //创建子控件。
              last = con.Level;
          } else {
            //
            if (con.Level < last && con.Level != 1) {
            
            }
            if (con.Level - last > 1) {
                cout << "子控件的Level数错误。\n";
                return;
            }
            if (con.Level == 1) {
                cout << "多余的顶Level控件。\n";
                return;
            }
          }
        }
        cout << con.Level << "\n";
      }
    }        
  } else {
      cout <<"no such file" << endl;
  }  
}

int main() {
  SetConsoleOutputCP(65001);
  read_gui("first.gui");
  return 0;
}

int i = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{  
  switch(message) {
    //设置Edit控件的文本
		case WM_SETTEXT:
      {} 
      return 0;
    case WM_TIMER: 
      {
        ++i;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
      }
      return 0;
    //子窗口的绘制应该放在WM_PAINT消息中
		case WM_PAINT:
      {
        int len;
        cout << "WM_PAINT\n";
        PAINTSTRUCT pt;
        HDC hdc;
        hdc=BeginPaint(hWnd,&pt);
        SetTextColor(hdc,RGB(255,0,0));
        SetBkColor(hdc,RGB(0,255,0));
        SetBkMode(hdc,TRANSPARENT);
        Rectangle(hdc,0,0,100,100);
        char str[16] = {};
        if (i % 2 == 1)
          len = sprintf(str, "%d |", i);
        else
          len = sprintf(str, "%d", i);
        cout << str << "\n";
        TextOut(hdc, 0, 0, str, len);
        EndPaint(hWnd,&pt);
      }
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}