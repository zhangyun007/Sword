#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

//用于函数SetConsoleOutputCP(65001);更改cmd编码为utf8

using namespace Gdiplus;
using namespace std;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//得到一行文本的头一个单词。
string get_first_token(string line) {
  string s = "";
  for (int i=0; i<line.length(); i++) {
    if (line[i] != ' ' && line[i] != '\t')
      s += line[i];
    else
      break;
  }
  return s;
}

class MyControl {
public:  
  unsigned short Level;   //控件在第几层？
  string GraphicControl;  //控件名称 ，可能的值为"<window>" "<text>" "<div>" ...
  map<string, string> property; //控件属性  titile=1, 1为val的index.
  vector<string> val;           // 存储 "...."
  
  /*将带空格的字符串存储到vector<string> val中，并用对应的vector下标来替换字符串。
  这么做的目的是为了方便做词法分析：以空格为间隔。*/
  string replace_string_2_int(string line);
  MyControl(string line);
};

//line是文件中的一行：1 window title="第一个窗口"
MyControl::MyControl(string line) {
  string l = replace_string_2_int(line);
  cout << "++++++" << l << "\n";
  
  string s = get_first_token(line);
                            
  for (int i=0; i<s.length(); i++){
    if (!isdigit(s[i])) {
      cout << "You should start with level number.\n";
      return;
    }
  }
  
  Level = atoi(s.c_str());
}

//字符串存到vector里，存下标，这样就消除了line中的空格。
string MyControl::replace_string_2_int(string line){
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
    
    val.push_back(s);
    itoa(n, m, 4);
    str+=m;
    n++;
    
    if (i == (line.length()-1))
      break;
    i++;
  }
  return str;
}

void create_control(class MyControl con) {
  
  if (con.GraphicControl == "<WINDOW>") {
    HWND 		hwnd;
    
    WNDCLASS            wndClass;
    
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
  }
}

//去掉line开头的空白字符。
string skip_blank(string line) {
  for (int i=0; i<line.length(); i++) {
    if (line[i]!=' ' && line[i]!='\t')
      return line.substr(i, line.length()-i);
  }
  return line;
}

int main() {
    SetConsoleOutputCP(65001);
    ifstream in("first.gui");
    string line;
 
    if (in) {
        
        int last = -1;
        
        // line中不包括每行的换行符
        while (getline (in, line)) { 
        
            line = skip_blank(line);
            cout << line << endl;
                
            if (line[0] == ';')
                  continue;                
                            
            if (line!="") {
                class MyControl con(line);
                
                if (last == -1) {
                  if (con.Level == 1) {
                      last = 1;
                      //... 创建顶层窗口
                      create_control(con);
                  } else {
                    cout << "You should start from level 1.\n";
                    return 1;
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
                          cout << "子控件的层数错误。\n";
                          return 1;
                      }
                      if (con.Level == 1) {
                          cout << "多余的顶层控件。\n";
                          return 1;
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
