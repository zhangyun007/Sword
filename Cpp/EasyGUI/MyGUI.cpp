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

//���ں���SetConsoleOutputCP(65001);����cmd����Ϊutf8

using namespace Gdiplus;
using namespace std;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "gdi32.lib")

#define IDT_TIMER1 12
    
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
        
//�õ�һ���ı���ͷһ�����ʡ�
string ȡ�׵���(string line) {
  string s = "";
  for (int i=0; i<line.length(); i++) {
    if (line[i] != ' ' && line[i] != '\t')
      s += line[i];
    else
      break;
  }
  return s;
}

//ȥ��line��ͷ�Ŀհ��ַ���
string ȥ�ո�(string line) {
  for (int i=0; i<line.length(); i++) {
    if (line[i]!=' ' && line[i]!='\t')
      return line.substr(i, line.length()-i);
  }
  return line;
}

class ͼ��Ԫ�� {
public:  
  unsigned short ��;   //�ؼ��ڵڼ��㣿
  string Ԫ������;  //�ؼ����� �����ܵ�ֵΪ"<window>" "<text>" "<div>" ...
  map<string, string> Ԫ������; //�ؼ�����  titile=1, 1Ϊval��index.
  vector<string> ֵ;           // �洢 "...."
  
  /*�����ո���ַ����洢��vector<string> val�У����ö�Ӧ��vector�±����滻�ַ�����
  ��ô����Ŀ����Ϊ�˷������ʷ��������Կո�Ϊ�����*/
  string �ַ���������(string line);
  ͼ��Ԫ��(string line);
  void ����ͼ��Ԫ��();
};

//line���ļ��е�һ�У�1 window title="��һ������"
ͼ��Ԫ��::ͼ��Ԫ��(string line) {
  string l = �ַ���������(line);
  
  string s = ȡ�׵���(line);
                            
  for (int i=0; i<s.length(); i++){
    if (!isdigit(s[i])) {
      cout << "You should start with �� number.\n";
      return;
    }
  }
  
  �� = atoi(s.c_str());
  
  Ԫ������ = ȡ�׵���(ȥ�ո�(line.substr(s.length())));
  
  cout << �� << ", "<< Ԫ������ << "\n";
}

//�ַ����浽vector����±꣬������������line�еĿո�
string ͼ��Ԫ��::�ַ���������(string line){
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
        cout << " �����ɶԡ�\n";
        exit(0);
      }
      i++;
    }
    
    ֵ.push_back(s);
    itoa(n, m, 4);
    str+=m;
    n++;
    
    if (i == (line.length()-1))
      break;
    i++;
  }
  return str;
}

void ͼ��Ԫ��::����ͼ��Ԫ��() {
  
  if (Ԫ������ == "<WINDOW>") {
    cout << "will create a window\n";
    HWND 		hwnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    
    wndClass.style          = CS_HREDRAW | CS_VREDRAW;
    //ͬһ�����๫��һ�����ڴ�����̣����ڴ������Ҫ����gs�ļ������ݲ���֪����
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
    
    //��Ϣѭ��
    while(GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  
  if (Ԫ������ == "<TEXT>") {
  }
}

//��ȡGUI�����ļ���GS�ű��ļ�������ͼ�γ���
void read_gui_gs(string gui, string gs){
  ifstream in(gui);
  string line;
      
  MyAssert(ȡ�׵���("hedllo world"), "hedllo");
  
  if (in) {
      
    int last = -1;
    // line�в�����ÿ�еĻ��з�
    while (getline (in, line)) { 
    
      line = ȥ�ո�(line);
      cout << line << endl;
          
      if (line[0] == ';')
        continue;                
                      
      if (line!="") {
        class ͼ��Ԫ�� con(line);
        
        if (last == -1) {
          if (con.�� == 1) {
              last = 1;
              //... �������㴰��
              con.����ͼ��Ԫ��();
          } else {
            cout << "You should start from �� 1.\n";
            return;
          }
        } else {
          if (con.�� - last == 1) {
              //�����ӿؼ���
              last = con.��;
          } else {
            //
            if (con.�� < last && con.�� != 1) {
            
            }
            if (con.�� - last > 1) {
                cout << "�ӿؼ��Ĳ�������\n";
                return;
            }
            if (con.�� == 1) {
                cout << "����Ķ���ؼ���\n";
                return;
            }
          }
        }
        cout << con.�� << "\n";
      }
    }        
  } else {
      cout <<"no such file" << endl;
  }  
}

int main() {
  SetConsoleOutputCP(65001);
  read_gui_gs("first.gui", "first.gs");
  return 0;
}

int i = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{  
  switch(message) {
    //����Edit�ؼ����ı�
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
    //�Ӵ��ڵĻ���Ӧ�÷���WM_PAINT��Ϣ��
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