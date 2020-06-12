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

//ȥ��line��ͷ�Ŀհ��ַ���
string skip_blank(string line) {
  for (int i=0; i<line.length(); i++) {
    if (line[i]!=' ' && line[i]!='\t')
      return line.substr(i, line.length()-i);
  }
  return line;
}

class GUI_Element {
public:  
  unsigned short Level;   //�ؼ��ڵڼ�Level��
  string Name;  //�ؼ����� �����ܵ�ValΪ"<window>" "<text>" "<div>" ...
  map<string, string> Property; //�ؼ�����  titile=1, 1ΪVal��index.
  vector<string> Val;           // GUI�����е��ַ���
  
  HWND 		hwnd;                   //��ǰ�ؼ��ľ��
  
  class GUI_Element *parent;      //���ڵ�
  class GUI_Element *child;      //��һ���ӽڵ�
  class GUI_Element *brother;    //��һ���ֵܽڵ�

  GUI_Element(string line);  
  
  /*�����ո���ַ����洢��vector<string> val�У����ö�Ӧ��vector�±����滻�ַ�����
  ��ô����Ŀ����Ϊ�˷������ʷ��������Կո�Ϊ�����*/
  string String_2_Int(string line);
  
  //���������ƿؼ�
  void Create_Element();
};

//line���ļ��е�һ�У�1 window title="��һ������"
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

//�ַ����浽vector����±꣬������������line�еĿո�
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
        cout << " �����ɶԡ�\n";
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

//���������ƿؼ����ȸ����ӣ����ֺ�ܡ�
void GUI_Element::Create_Element() {
  
  if (Name == "<WINDOW>") {
    cout << "will create a window\n";
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
  
  if (Name == "<TEXT>") {
    str = "";
    //�ҵ���Level���ھ��
    InvalidateRect(parent->hwnd, NULL, TRUE);
  }
}

//��ȡGUI�����ļ���GS�ű��ļ�������ͼ�γ���
void read_gui(string gui){
  ifstream in(gui);
  string line;
      
  MyAssert(Get_First("hedllo world"), "hedllo");
  
  if (in) {
      
    int last = -1;
    // line�в�����ÿ�еĻ��з�
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
              //... ������Level����
              con.Create_Element();
          } else {
            cout << "You should start from Level 1.\n";
            return;
          }
        } else {
          if (con.Level - last == 1) {
              //�����ӿؼ���
              last = con.Level;
          } else {
            //
            if (con.Level < last && con.Level != 1) {
            
            }
            if (con.Level - last > 1) {
                cout << "�ӿؼ���Level������\n";
                return;
            }
            if (con.Level == 1) {
                cout << "����Ķ�Level�ؼ���\n";
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