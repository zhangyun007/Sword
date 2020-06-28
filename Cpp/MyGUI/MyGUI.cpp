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

//存储@var部分的变量名和值Val的下标。
map<string, string> var;

int cxScreen,cyScreen;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class Proc {
public:
  string name;    //过程名，可能是"@init" "@first.click" ...
  vector<string> s; //把过程的内容以空格区分，存进vector<string> s
};

vector<class Proc *> vp;

/*将字符串存储到vector<string> val中，并用对应的vector下标来替换字符串。
  这么做的目的是为了方便做词法分析：以空格为间隔。*/
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
    
    //此处，检测到第一个“
    i++;
    
    while (line[i] != '\"') {
      s+=line[i];
      if (i == (line.length()-1)) {
        cout << " “不成对。\n";
        exit(0);
      }
      i++;
    }
    
    //此处，第二个"被检测到
    Val.push_back(s);
    n = Val.size();
    
    //存数字索引   
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
  
  unsigned short Level;         //控件在第几Level？
  string Name;                  //控件名称 ，可能的Val为"<window>" "<text>" "<div>" ...
  map<string, string> Property; //控件属性  titile=1, 1为Val的index.
  
  class GUI_Element *parent;    //父节点
  class GUI_Element *child;     //第一个子节点
  class GUI_Element *brother;   //第一个兄弟节点

  GUI_Element(string line);  
  
};

//line是文件中的一行：1 window title="第一个 窗口"
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

struct Window_Element {
  HWND  hwnd;
  class GUI_Element *head;
};

vector<struct Window_Element *> v;

//绘制Window
void Draw_Window(struct Window_Element *w_e) {
  
  class GUI_Element *tmp = w_e->head;
  
  //绘制顶层窗口
  if (tmp->Name == "WINDOW") {
    MSG         msg;
    string      title = "Test Window";
    
    int x = atof(tmp->Property["left"].c_str()) * cxScreen;
    int y = atof(tmp->Property["top"].c_str()) * cyScreen;
    int w = (atof(tmp->Property["right"].c_str()) - atof(tmp->Property["left"].c_str())) * cxScreen;
    int h = (atof(tmp->Property["bottom"].c_str()) - atof(tmp->Property["top"].c_str())) * cyScreen;
    
    char buffer[10];

    //存储top和left right bottom，单位为像素。
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
  
    //发送一个WM_PAINTER消息，绘制子控件。
    InvalidateRect(w_e->hwnd, NULL, TRUE);
  
    ShowWindow(w_e->hwnd, 1);
    UpdateWindow(w_e->hwnd);

    //消息循环
    while(GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

//绘制Window以外的子控件。同一层，后绘制的可能会覆盖先绘制的;  先父后子，先兄后弟。
void Draw_Element(class GUI_Element *tmp, HDC hdc, HWND hwnd) { 
  
   //使用gdi函数绘制矩形
  if (tmp->Name == "RECT") {   
    //像素值
    int pt = atoi(tmp->parent->Property["t"].c_str());
    int pl = atoi(tmp->parent->Property["l"].c_str());
    int pr = atoi(tmp->parent->Property["r"].c_str());
    int pb = atoi(tmp->parent->Property["b"].c_str());
    
    int l = atof(tmp->Property["left"].c_str()) * (pr - pl) + pl;
    int t = atof(tmp->Property["top"].c_str()) * (pb - pt) + pt;
    int r = atof(tmp->Property["right"].c_str()) * (pr - pl) + pl;
    int b = atof(tmp->Property["bottom"].c_str()) * (pb - pt) + pt;
    
    char buffer[10];
    
    //存储top和left right bottom，单位为像素。
    itoa(l,buffer,10);
    tmp->Property["l"] = buffer;
    itoa(t,buffer,10);
    tmp->Property["t"] = buffer;
    itoa(r,buffer,10);
    tmp->Property["r"] = buffer;
    itoa(b,buffer,10);
    tmp->Property["b"] = buffer;    
  }
  
  //RECT和RECTANGEL的区别是前者只做定位使用，并不绘制；后者会绘制矩形。
 
  if (tmp->Name == "RECTANGLE") {    
    //像素值
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
    
    //存储top和left right bottom，单位为像素。
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
  
  //链接
  if (tmp->Name == "A") {
    cout<< "A...\n";
  }
  
  if (tmp->child)
    Draw_Element(tmp->child, hdc, hwnd);
  if (tmp->brother)
    Draw_Element(tmp->brother, hdc, hwnd);
}

//找到hwnd对应的Window_Element的数组下标，如果返回-1表示没有找到。
int Find_Window(HWND hwnd) {
  for (int i=0; i< v.size(); i++){
    if (v[i]->hwnd == hwnd) {
      return i;
    }
  }
  return -1;
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
          
      if (line == "")
        continue;
      // ；开头表示注释
      if (line[0] == ';')
        continue;                
        
      //变量定义
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
          //不是最后一个单词
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

      //图形描述
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
      
      //初始化函数
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

      //以@开头，可能为@init--初始化函数或者键盘鼠标处理函数。
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
          //不是最后一个单词
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

  //释放内存
  
  return 0;
}

//返回p所处的控件
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

//同一个窗口类公用一个窗口处理过程
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
   WPARAM wParam, LPARAM lParam)
{
  int i;
  string s;
  RECT r;  
  
  switch(message) {
    //移动标题栏等
    case WM_SYSCOMMAND:
      i = Find_Window(hWnd);
      
      //取得窗口客户区坐标
      GetClientRect(hWnd, &r);
      
      //取得移动后，窗体的客户区坐标。
      v[i]->head->Property["l"] = r.left;
      v[i]->head->Property["t"] = r.top;
      v[i]->head->Property["r"] = r.right;
      v[i]->head->Property["b"] = r.bottom;
      
      return DefWindowProc(hWnd, message, wParam, lParam);
      
    case WM_LBUTTONDOWN:
      
      POINT point;
      
      GetCursorPos(&point);            // 获取鼠标指针位置（屏幕坐标）
      ScreenToClient(hWnd, &point);    // 将鼠标指针位置转换为窗口坐标
      cout << point.x << " "<< point.y << "\n";
      
      i = Find_Window(hWnd);
      //遍历Window_Element，得到鼠标点击点所在的控件，并调用其处理函数。
      //遍历方式：先父后子，先兄后弟。
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
      
      hdc=BeginPaint(hWnd,&pt);
      SetTextColor(hdc,RGB(255,0,0));
      SetBkColor(hdc,RGB(0,255,0));
      SetBkMode(hdc,TRANSPARENT);
      
      i = Find_Window(hWnd);
            
      //取得窗口客户区坐标
      GetClientRect(hWnd, &r);
      
      char buffer[10];
      
      //存储当前窗口客户区的top left right bottom
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