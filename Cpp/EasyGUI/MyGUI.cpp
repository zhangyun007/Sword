#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

#include "../TinyTL/TObject.hpp"
#include "../TinyTL/MyLib.hpp"

//用于函数SetConsoleOutputCP(65001);更改cmd编码为utf8

using namespace Gdiplus;
using namespace std;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "gdi32.lib")

#define IDT_TIMER1 12

// 字符串常量
vector<string> Val;

//存储@var部分的变量和值
map<string, string> var;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class GUI_Element {
public:  
  
  unsigned short Level;         //控件在第几Level？
  string Name;                  //控件名称 ，可能的Val为"<window>" "<text>" "<div>" ...
  map<string, string> Property; //控件属性  titile=1, 1为Val的index.
  vector<string> Val;           // GUI描述中的字符串
  
  class GUI_Element *parent;    //父节点
  class GUI_Element *child;     //第一个子节点
  class GUI_Element *brother;   //第一个兄弟节点

  GUI_Element(string line);  
  
  /*将带空格的字符串存储到vector<string> val中，并用对应的vector下标来替换字符串。
  这么做的目的是为了方便做词法分析：以空格为间隔。*/
  string String_2_Int(string line);
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
  
  string tmp = Skip_Blank(l.substr(s.length()));
  Name = Get_First(tmp);
  
  tmp = Skip_Blank(tmp.substr(Name.length()));
  string f = Get_First(tmp);
  //不是最后一个单词
  while (f != tmp) {
    for (int i=0; i<f.length(); i++) {
      if (f[i]=='=') {
        //cout << f.substr(i+1, f.length()) << "\n";
        Property[f.substr(0, i)] = f.substr(i+1, f.length());
        break;
      }
    }
    tmp = Skip_Blank(tmp.substr(f.length()));
    f = Get_First(tmp);
  }
  for (int i=0; i<f.length(); i++) {
    if (f[i]=='=') {
      Property[f.substr(0, i)] = f.substr(i+1, f.length());
    }
  }
  cout << Level << ", "<< Name << "\n";
  for(auto iter = Property.begin(); iter != Property.end(); iter++) {
    cout << iter->first << " : " << iter->second << endl;
  }
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

struct Window_Element {
  HWND  hwnd;
  class GUI_Element *head;
};

vector<struct Window_Element *> v;

//绘制Window
void Draw_Window(struct Window_Element *w) {
  
  class GUI_Element *tmp = w->head;
  
  //绘制顶层窗口
  if (tmp->Name == "WINDOW") {
    cout << "will create a window\n";
    MSG         msg;
    string      title;
    
    if (Is_Int(tmp->Property["name"]))
      title=tmp->Val[atoi(tmp->Property["name"].c_str())];
    
    w->hwnd = CreateWindow(
      TEXT("MyClass"),   			  // window class name
      TEXT(title.c_str()),  		        
      WS_OVERLAPPEDWINDOW,     	// window style
      CW_USEDEFAULT,           	// initial x position
      CW_USEDEFAULT,           	// initial y position
      CW_USEDEFAULT,           	// initial x size
      CW_USEDEFAULT,           	// initial y size
      NULL,						            // parent window handle
      NULL,                     	// window menu handle
      NULL,          			  	    // program instance handle
      NULL);                    	// creation parameters			
      
    /*
    SetTimer(w.hwnd,             // handle to main window 
      IDT_TIMER1,            // timer identifier 
      1000,                 // 10-second interval 
      (TIMERPROC) NULL);     // no timer callback 

    SetWindowText(w.hwnd, "aaa");    */

    cout << "hwnd =" << w->hwnd << "\n";
  
    //发送一个WM_PAINTER消息，绘制子控件。
    InvalidateRect(w->hwnd, NULL, TRUE);

    ShowWindow(w->hwnd, 1);
    UpdateWindow(w->hwnd);

    //消息循环
    while(GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    
  }
}

//读取GUI描述文件，生成图形程序。
void read_gui(char *gui){
  ifstream in(gui);
  string line;
      
  MyAssert(Get_First("hedllo world"), "hedllo");
  
  if (in) {
      
    class GUI_Element *last = NULL;
    // line中不包括每行的换行符
    while (getline (in, line)) { 
    
      line = Skip_Blank(line);
      cout << line << endl;
          
      // ；开头表示注释
      if (line[0] == ';')
        continue;                
        
      //变量定义
      if (line=="@var") {
        while (getline (in, line)) {
          line = Skip_Blank(line);
          if (line[0] == ';')
            continue;   
          if (line=="end")
            break;
          string f = Get_First(line);
          //不是最后一个单词
          while (f != line) {
            for (int i=0; i<f.length(); i++) {
              if (f[i]=='=') {
                //cout << f.substr(i+1, f.length()) << "\n";
                var[f.substr(0, i)] = f.substr(i+1, f.length());
                break;
              }
            }
            line = Skip_Blank(line.substr(f.length()));
            f = Get_First(line);
          }
          for (int i=0; i<f.length(); i++) {
            if (f[i]=='=') {
              var[f.substr(0, i)] = f.substr(i+1, f.length());
            }
          }
        }
      }

      //图形描述
      if (line=="@gui") {        
        while (getline (in, line)) {
          line = Skip_Blank(line);
          
          if (line[0] == ';')
            continue;   
          
          if (line=="end")
            break;          

          if (line!="") {
            class GUI_Element *con = new GUI_Element(line);
            
            //顶层控件
            if (con->Level == 1 && con->Name=="WINDOW") {
              con->parent=NULL;
              con->child=NULL;
              con->brother=NULL;
              last = con;
              struct Window_Element *e = (struct Window_Element *)malloc(sizeof(struct Window_Element));
              e->hwnd = 0;
              e->head = con;
              v.push_back(e);
              continue;
            } 
            
            //非顶层控件
            if (last != NULL) {
              //last的子控件
              if (con->Level - last->Level == 1) {
                con->parent=last;
                con->child=NULL;
                con->brother=NULL;
                last->child = con;
                last = con;
                continue;
              }

              //last的兄弟控件
              if (con->Level == last->Level) {
                last->brother=con;
                
                con->parent=last->parent;
                con->child=NULL;
                con->brother=NULL;
                last = con;
                continue;
              }
              //last上层控件
              if (con->Level < last->Level && con->Level > 1) {
                while (con->Level != last->Level)
                  last = last->parent;
                last->brother = con;
                con->parent=last->parent;
                con->child=NULL;
                con->brother=NULL;
                last = con;
                continue;
              }
              //控件层次错误
              cout << con->Level  << "..\n";
              cout << last->Level  << "..\n";
              if (con->Level - last->Level > 1) {
                cout << "Level error.\n";
                return;
              }
            }
          }
        }
      }
      
      //初始化函数
      if (line=="@init") {
        while (getline (in, line)) {
          line = Skip_Blank(line);
          if (line[0] == ';')
            continue;
          if (line=="end")
            break;
        }      
      }
    }
  } else {
      cout <<"no such file" << endl;
  }  
}

int main(int argc, char **argv) {
  SetConsoleOutputCP(65001);
  if (argc == 1) {
    cout << "Need file name as args.\n";
    exit(1);
  }
  cout << argv[1] << "\n";
  read_gui(argv[1]);
  
  WNDCLASS            wndClass;
  
  wndClass.style          = CS_HREDRAW | CS_VREDRAW;
  //同一窗口类公用一个窗口处理过程
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
  
  Draw_Window(v[0]);

  return 0;
}

//绘制Window以外的子控件。同一层，后绘制的可能会覆盖先绘制的;  先父后子，先兄后弟。
void Draw_Element(struct Window_Element *w, HDC hdc) { 
  class GUI_Element *tmp = w->head;
  tmp = tmp->child;
  
  //绘制子控件
  while (tmp != NULL) {
    
     //使用gdi函数绘制矩形
    if (tmp->Name == "REGTANGLE") {
      cout << "regtangel ...\n";
      Rectangle(hdc,0,0,100,100);
      Rectangle(hdc,50,50,200,200);          
    }
    
    //绘制文本
    if (tmp->Name == "TEXT") {
      cout << "text ...\n";
      string s;
      if (Is_Int(tmp->Property["caption"]))
        s = tmp->Val[atoi(tmp->Property["caption"].c_str())];
      cout << s << "___\n";
      TextOut(hdc, 0, 0, s.c_str(), s.length());
    }
    tmp = tmp->child;
  }
}

//找到hwnd对应的Window_Element的数组下标，如果返回-1表示没有找到。
int Find_Window(HWND hwnd) {
  for (int i=0; i< v.size(); i++){
    cout << v[i]->hwnd << " --- " << hwnd << " find .... \n";
    if (v[i]->hwnd == hwnd) {
      return i;
    }
  }
  return -1;
}

//同一个窗口类公用一个窗口处理过程
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
  switch(message) {
    //设置Edit控件的文本
		case WM_SETTEXT:
      return 0;
    case WM_TIMER: 
      //InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    // WINDOW以外图形元素的绘制
		case WM_PAINT:
      PAINTSTRUCT pt;
      HDC hdc;
      
      cout << "paint hwnd =" << hWnd << "\n";
      hdc=BeginPaint(hWnd,&pt);
      SetTextColor(hdc,RGB(255,0,0));
      SetBkColor(hdc,RGB(0,255,0));
      SetBkMode(hdc,TRANSPARENT);
      
      int i;
      i = Find_Window(hWnd);
      Draw_Element(v[i], hdc);
      
      EndPaint(hWnd,&pt);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}