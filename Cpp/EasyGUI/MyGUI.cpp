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

//���ں���SetConsoleOutputCP(65001);����cmd����Ϊutf8

using namespace Gdiplus;
using namespace std;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "gdi32.lib")

#define IDT_TIMER1 12

// �ַ�������
vector<string> Val;

//�洢@var���ֵı�����ֵ
map<string, string> var;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class GUI_Element {
public:  
  
  unsigned short Level;         //�ؼ��ڵڼ�Level��
  string Name;                  //�ؼ����� �����ܵ�ValΪ"<window>" "<text>" "<div>" ...
  map<string, string> Property; //�ؼ�����  titile=1, 1ΪVal��index.
  vector<string> Val;           // GUI�����е��ַ���
  
  class GUI_Element *parent;    //���ڵ�
  class GUI_Element *child;     //��һ���ӽڵ�
  class GUI_Element *brother;   //��һ���ֵܽڵ�

  GUI_Element(string line);  
  
  /*�����ո���ַ����洢��vector<string> val�У����ö�Ӧ��vector�±����滻�ַ�����
  ��ô����Ŀ����Ϊ�˷������ʷ��������Կո�Ϊ�����*/
  string String_2_Int(string line);
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
  
  string tmp = Skip_Blank(l.substr(s.length()));
  Name = Get_First(tmp);
  
  tmp = Skip_Blank(tmp.substr(Name.length()));
  string f = Get_First(tmp);
  //�������һ������
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

struct Window_Element {
  HWND  hwnd;
  class GUI_Element *head;
};

vector<struct Window_Element *> v;

//����Window
void Draw_Window(struct Window_Element *w) {
  
  class GUI_Element *tmp = w->head;
  
  //���ƶ��㴰��
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
  
    //����һ��WM_PAINTER��Ϣ�������ӿؼ���
    InvalidateRect(w->hwnd, NULL, TRUE);

    ShowWindow(w->hwnd, 1);
    UpdateWindow(w->hwnd);

    //��Ϣѭ��
    while(GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    
  }
}

//��ȡGUI�����ļ�������ͼ�γ���
void read_gui(char *gui){
  ifstream in(gui);
  string line;
      
  MyAssert(Get_First("hedllo world"), "hedllo");
  
  if (in) {
      
    class GUI_Element *last = NULL;
    // line�в�����ÿ�еĻ��з�
    while (getline (in, line)) { 
    
      line = Skip_Blank(line);
      cout << line << endl;
          
      // ����ͷ��ʾע��
      if (line[0] == ';')
        continue;                
        
      //��������
      if (line=="@var") {
        while (getline (in, line)) {
          line = Skip_Blank(line);
          if (line[0] == ';')
            continue;   
          if (line=="end")
            break;
          string f = Get_First(line);
          //�������һ������
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

      //ͼ������
      if (line=="@gui") {        
        while (getline (in, line)) {
          line = Skip_Blank(line);
          
          if (line[0] == ';')
            continue;   
          
          if (line=="end")
            break;          

          if (line!="") {
            class GUI_Element *con = new GUI_Element(line);
            
            //����ؼ�
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
            
            //�Ƕ���ؼ�
            if (last != NULL) {
              //last���ӿؼ�
              if (con->Level - last->Level == 1) {
                con->parent=last;
                con->child=NULL;
                con->brother=NULL;
                last->child = con;
                last = con;
                continue;
              }

              //last���ֵܿؼ�
              if (con->Level == last->Level) {
                last->brother=con;
                
                con->parent=last->parent;
                con->child=NULL;
                con->brother=NULL;
                last = con;
                continue;
              }
              //last�ϲ�ؼ�
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
              //�ؼ���δ���
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
      
      //��ʼ������
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
  //ͬһ�����๫��һ�����ڴ������
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

//����Window������ӿؼ���ͬһ�㣬����ƵĿ��ܻḲ���Ȼ��Ƶ�;  �ȸ����ӣ����ֺ�ܡ�
void Draw_Element(struct Window_Element *w, HDC hdc) { 
  class GUI_Element *tmp = w->head;
  tmp = tmp->child;
  
  //�����ӿؼ�
  while (tmp != NULL) {
    
     //ʹ��gdi�������ƾ���
    if (tmp->Name == "REGTANGLE") {
      cout << "regtangel ...\n";
      Rectangle(hdc,0,0,100,100);
      Rectangle(hdc,50,50,200,200);          
    }
    
    //�����ı�
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

//�ҵ�hwnd��Ӧ��Window_Element�������±꣬�������-1��ʾû���ҵ���
int Find_Window(HWND hwnd) {
  for (int i=0; i< v.size(); i++){
    cout << v[i]->hwnd << " --- " << hwnd << " find .... \n";
    if (v[i]->hwnd == hwnd) {
      return i;
    }
  }
  return -1;
}

//ͬһ�������๫��һ�����ڴ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
  switch(message) {
    //����Edit�ؼ����ı�
		case WM_SETTEXT:
      return 0;
    case WM_TIMER: 
      //InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    // WINDOW����ͼ��Ԫ�صĻ���
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