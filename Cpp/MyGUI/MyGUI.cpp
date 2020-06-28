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

//�洢@var���ֵı�������ֵVal���±ꡣ
map<string, string> var;

int cxScreen,cyScreen;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class Proc {
public:
  string name;    //��������������"@init" "@first.click" ...
  vector<string> s; //�ѹ��̵������Կո����֣����vector<string> s
};

vector<class Proc *> vp;

/*���ַ����洢��vector<string> val�У����ö�Ӧ��vector�±����滻�ַ�����
  ��ô����Ŀ����Ϊ�˷������ʷ��������Կո�Ϊ�����*/
string String_2_Int(string line){
  int i = 0;
  string str = "";
  short n=0;
   
  while (1) {
    string s = "";
    
    while (line[i] != '\"') {
      str+=line[i];
      if (i == (line.length()-1))
        return str;
      i++;
    }
    
    //�˴�����⵽��һ����
    i++;
    
    while (line[i] != '\"') {
      s+=line[i];
      if (i == (line.length()-1)) {
        cout << " �����ɶԡ�\n";
        exit(0);
      }
      i++;
    }
    
    //�˴����ڶ���"����⵽
    Val.push_back(s);
    n = Val.size();
    
    //����������   
    char buf[10];
    sprintf(buf,"%d",n-1);
    str=str+"_VAL"+buf;
    
    if (i == (line.length()-1))
      break;
    i++;
  }
  return str;
}

class GUI_Element {
public:  
  
  unsigned short Level;         //�ؼ��ڵڼ�Level��
  string Name;                  //�ؼ����� �����ܵ�ValΪ"<window>" "<text>" "<div>" ...
  map<string, string> Property; //�ؼ�����  titile=1, 1ΪVal��index.
  
  class GUI_Element *parent;    //���ڵ�
  class GUI_Element *child;     //��һ���ӽڵ�
  class GUI_Element *brother;   //��һ���ֵܽڵ�

  GUI_Element(string line);  
  
};

//line���ļ��е�һ�У�1 window title="��һ�� ����"
GUI_Element::GUI_Element(string line) {  
  string s = Get_First(line);
                            
  for (int i=0; i<s.length(); i++){
    if (!isdigit(s[i])) {
      cout << "You should start with Level number.\n";
      return;
    }
  }
  
  Level = atoi(s.c_str());
  
  string tmp = Skip_Blank(line.substr(s.length()));
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

struct Window_Element {
  HWND  hwnd;
  class GUI_Element *head;
};

vector<struct Window_Element *> v;

//����Window
void Draw_Window(struct Window_Element *w_e) {
  
  class GUI_Element *tmp = w_e->head;
  
  //���ƶ��㴰��
  if (tmp->Name == "WINDOW") {
    MSG         msg;
    string      title = "Test Window";
    
    int x = atof(tmp->Property["left"].c_str()) * cxScreen;
    int y = atof(tmp->Property["top"].c_str()) * cyScreen;
    int w = (atof(tmp->Property["right"].c_str()) - atof(tmp->Property["left"].c_str())) * cxScreen;
    int h = (atof(tmp->Property["bottom"].c_str()) - atof(tmp->Property["top"].c_str())) * cyScreen;
    
    char buffer[10];

    //�洢top��left right bottom����λΪ���ء�
    itoa(x,buffer,10);
    cout << " Window L is " << buffer << "\n";
    tmp->Property["l"] = buffer;
    cout << " Window T is " << buffer << "\n";
    itoa(y,buffer,10);
    tmp->Property["t"] = buffer;
    
    itoa(x+w,buffer,10);
    cout << " Window R is " << buffer << "\n";
    tmp->Property["r"] = buffer;
    itoa(y+h,buffer,10);
    cout << " Window B is " << buffer << "\n";
    tmp->Property["b"] = buffer;
    
    w_e->hwnd = CreateWindow(
      TEXT("MyClass"),   			  // window class name
      TEXT(title.c_str()),  		        
      WS_OVERLAPPEDWINDOW,     	// window style
      x,           	// initial x position
      y,           	// initial y position
      w,           	// initial x size
      h,           	// initial y size
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
  
    //����һ��WM_PAINTER��Ϣ�������ӿؼ���
    InvalidateRect(w_e->hwnd, NULL, TRUE);
  
    ShowWindow(w_e->hwnd, 1);
    UpdateWindow(w_e->hwnd);

    //��Ϣѭ��
    while(GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

//����Window������ӿؼ���ͬһ�㣬����ƵĿ��ܻḲ���Ȼ��Ƶ�;  �ȸ����ӣ����ֺ�ܡ�
void Draw_Element(class GUI_Element *tmp, HDC hdc, HWND hwnd) { 
  
   //ʹ��gdi�������ƾ���
  if (tmp->Name == "RECT") {   
    //����ֵ
    int pt = atoi(tmp->parent->Property["t"].c_str());
    int pl = atoi(tmp->parent->Property["l"].c_str());
    int pr = atoi(tmp->parent->Property["r"].c_str());
    int pb = atoi(tmp->parent->Property["b"].c_str());
    
    int l = atof(tmp->Property["left"].c_str()) * (pr - pl) + pl;
    int t = atof(tmp->Property["top"].c_str()) * (pb - pt) + pt;
    int r = atof(tmp->Property["right"].c_str()) * (pr - pl) + pl;
    int b = atof(tmp->Property["bottom"].c_str()) * (pb - pt) + pt;
    
    char buffer[10];
    
    //�洢top��left right bottom����λΪ���ء�
    itoa(l,buffer,10);
    tmp->Property["l"] = buffer;
    itoa(t,buffer,10);
    tmp->Property["t"] = buffer;
    itoa(r,buffer,10);
    tmp->Property["r"] = buffer;
    itoa(b,buffer,10);
    tmp->Property["b"] = buffer;    
  }
  
  //RECT��RECTANGEL��������ǰ��ֻ����λʹ�ã��������ƣ����߻���ƾ��Ρ�
 
  if (tmp->Name == "RECTANGLE") {    
    //����ֵ
    int pt = atoi(tmp->parent->Property["t"].c_str());
    int pl = atoi(tmp->parent->Property["l"].c_str());
    int pr = atoi(tmp->parent->Property["r"].c_str());
    int pb = atoi(tmp->parent->Property["b"].c_str());
    
    int l = atof(tmp->Property["left"].c_str()) * (pr - pl) + pl;
    int t = atof(tmp->Property["top"].c_str()) * (pb - pt) + pt;
    int r = atof(tmp->Property["right"].c_str()) * (pr - pl) + pl;
    int b = atof(tmp->Property["bottom"].c_str()) * (pb - pt) + pt;

    //Why Wrong?
    cout << pl << " ---- "<< tmp->parent->Property["t"]  << " " << pr  << " " << pb <<"  parent... RECTANGLE\n";
    cout << l << " "<< t  << " " << r  << " " << b <<" local ... RECTANGLE\n";
    
    char buffer[10];
    
    //�洢top��left right bottom����λΪ���ء�
    itoa(l,buffer,10);
    tmp->Property["l"] = buffer;
    itoa(t,buffer,10);
    tmp->Property["t"] = buffer;
    itoa(r,buffer,10);
    tmp->Property["r"] = buffer;
    itoa(b,buffer,10);
    tmp->Property["b"] = buffer;
    
    Rectangle(hdc,l,t,r,b);
    //Draw_Rectangle();
  }
  
  if (tmp->Name == "TEXT") {
    string s;
    
    s = tmp->Property["caption"];

    for (auto it: var) {
      if (it.first == s) {
        s = it.second;
      }
    }
   
    int t = atoi(tmp->parent->Property["t"].c_str());
    int l = atoi(tmp->parent->Property["l"].c_str());
    int r = atoi(tmp->parent->Property["r"].c_str());
    int b = atoi(tmp->parent->Property["b"].c_str());
    
    RECT re;  
    re.left=l; re.top=t; re.right=r; re.bottom=b;
    
    int i;
    if (s.substr(0, 4) == "_VAL")
       i = atoi(s.substr(4).c_str());
    //TextOut(hdc, l, t, s.c_str(), s.length());
    DrawText(hdc, Val[i].c_str(), Val[i].length(), &re, DT_LEFT);
  }
  
  //����
  if (tmp->Name == "A") {
    cout<< "A...\n";
  }
  
  if (tmp->child)
    Draw_Element(tmp->child, hdc, hwnd);
  if (tmp->brother)
    Draw_Element(tmp->brother, hdc, hwnd);
}

//�ҵ�hwnd��Ӧ��Window_Element�������±꣬�������-1��ʾû���ҵ���
int Find_Window(HWND hwnd) {
  for (int i=0; i< v.size(); i++){
    if (v[i]->hwnd == hwnd) {
      return i;
    }
  }
  return -1;
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
          
      if (line == "")
        continue;
      // ����ͷ��ʾע��
      if (line[0] == ';')
        continue;                
        
      //��������
      if (line=="@var") {
        while (getline (in, line)) {
          line = Skip_Blank(line);
          cout << line << "\n";          
          
          if (line == "")
            continue;
          if (line[0] == ';')
            continue;
          if (line == "end")
            break;
          
          string l = String_2_Int(line);
          cout << l << " ..\n";
          
          string f = Get_First(l);
          //�������һ������
          while (f != l) {
            for (int i=0; i<f.length(); i++) {
              if (f[i]=='=') {
                cout << f.substr(i+1, f.length()) << "\n";
                var[f.substr(0, i)] = f.substr(i+1, f.length());
                break;
              }
            }
            l = Skip_Blank(l.substr(f.length()));
            f = Get_First(l);
          }
          for (int i=0; i<f.length(); i++) {
            if (f[i]=='=') {
              cout << f.substr(i+1, f.length()) << "\n";
              var[f.substr(0, i)] = f.substr(i+1, f.length());
            }
          }
        }
      }

      //ͼ������
      if (line=="@gui") {        
        while (getline (in, line)) {
          cout << line << "\n";
          line = Skip_Blank(line);

          if (line == "")
            continue;
          if (line[0] == ';')
            continue;   
          if (line=="end")
            break;          
          
          string l = String_2_Int(line);
          cout << l << "\n";

          class GUI_Element *con = new GUI_Element(l);
          
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
      
      //��ʼ������
      if (line=="@init") {
        while (getline (in, line)) {
          line = Skip_Blank(line);
          cout << line << "\n";
          if (line == "")
            continue;
          if (line[0] == ';')
            continue;
          if (line=="end")
            break;
          string l = String_2_Int(line);
          continue;
        }
      }

      //��@��ͷ������Ϊ@init--��ʼ���������߼�����괦������
      if (line[0] == '@') {
        class Proc *p = new(class Proc);
        p->name = line;
        
        while (getline (in, line)) {
          line = Skip_Blank(line);
          cout << line << "\n";
          if (line == "")
            continue;
          if (line[0] == ';')
            continue;
          if (line=="end")
            break;
          
          string l = String_2_Int(line);

          string f = Get_First(l);
          //�������һ������
          while (f != l) {
            p->s.push_back(f);
            l = Skip_Blank(l.substr(f.length()));
            f = Get_First(l);
          }
        }
        vp.push_back(p);
      }
    }
  } else {
      cout <<"no such file" << endl;
  }
}

int main(int argc, char **argv) {
  SetConsoleOutputCP(65001);
  cxScreen=GetSystemMetrics(SM_CXSCREEN);
  cyScreen=GetSystemMetrics(SM_CYSCREEN);
  if (argc == 1) {
    cout << "Need file name as args.\n";
    exit(1);
  }
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

  //�ͷ��ڴ�
  
  return 0;
}

//����p�����Ŀؼ�
GUI_Element * Find_Element(POINT p, GUI_Element *e) {
  GUI_Element *last = NULL;
  
  int t = atoi(e->Property["t"].c_str());
  int l = atoi(e->Property["l"].c_str());
  int r = atoi(e->Property["r"].c_str());
  int b = atoi(e->Property["b"].c_str());

  cout << "e->name = " << e->Name << "\n";
  cout << t << " " << l << " " << r << " " << b << " " << " in find element....\n";
  
  if ((p.x > t) && (p.y > l) && (p.x < r) && (p.y < b))
      last = e;
    
  if (e->child != NULL) {
    GUI_Element *tmp = Find_Element(p, e->child);
    if (tmp!=NULL)
      last = tmp;
  } 
  
  if (e->brother!= NULL) {
    GUI_Element *tmp = Find_Element(p, e->brother);
    if (tmp!=NULL)
      last = tmp;
  } 
  
  return last;
}

//ͬһ�������๫��һ�����ڴ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
  int i;
  string s;
  RECT r;  
  
  switch(message) {
    //�ƶ���������
    case WM_SYSCOMMAND:
      i = Find_Window(hWnd);
      
      //ȡ�ô��ڿͻ�������
      GetClientRect(hWnd, &r);
      
      //ȡ���ƶ��󣬴���Ŀͻ������ꡣ
      v[i]->head->Property["l"] = r.left;
      v[i]->head->Property["t"] = r.top;
      v[i]->head->Property["r"] = r.right;
      v[i]->head->Property["b"] = r.bottom;
      
      return DefWindowProc(hWnd, message, wParam, lParam);
      
    case WM_LBUTTONDOWN:
      
      POINT point;
      
      GetCursorPos(&point);            // ��ȡ���ָ��λ�ã���Ļ���꣩
      ScreenToClient(hWnd, &point);    // �����ָ��λ��ת��Ϊ��������
      cout << point.x << " "<< point.y << "\n";
      
      i = Find_Window(hWnd);
      //����Window_Element���õ�����������ڵĿؼ����������䴦������
      //������ʽ���ȸ����ӣ����ֺ�ܡ�
      class GUI_Element * tmp;
      tmp = Find_Element(point, v[i]->head);   
      s = tmp->Property["name"];
      int j;
      if (s.substr(0, 4) == "_VAL")
        j = atoi(s.substr(4).c_str());
      cout << Val[j] << "\n";
      return 0;
    case WM_LBUTTONDBLCLK:
      return 0;
    case WM_RBUTTONDOWN:
      return 0;
    case WM_RBUTTONDBLCLK:
      return 0;
    case WM_MBUTTONDOWN:
      return 0;
    case WM_MBUTTONDBLCLK:
      return 0;
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
      
      hdc=BeginPaint(hWnd,&pt);
      SetTextColor(hdc,RGB(255,0,0));
      SetBkColor(hdc,RGB(0,255,0));
      SetBkMode(hdc,TRANSPARENT);
      
      i = Find_Window(hWnd);
            
      //ȡ�ô��ڿͻ�������
      GetClientRect(hWnd, &r);
      
      char buffer[10];
      
      //�洢��ǰ���ڿͻ�����top left right bottom
      itoa(r.left, buffer, 10);
      v[i]->head->Property["l"] = buffer;
      itoa(r.top, buffer, 10);
      v[i]->head->Property["t"] = buffer;
      itoa(r.right, buffer, 10);
      v[i]->head->Property["r"] = buffer;
      itoa(r.bottom , buffer, 10);
      v[i]->head->Property["b"] = buffer;

      Draw_Element(v[i]->head->child, hdc, hWnd);
      
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