#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

//���ں���SetConsoleOutputCP(65001);����cmd����Ϊutf8

using namespace Gdiplus;
using namespace std;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//�õ�һ���ı���ͷһ�����ʡ�
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
  unsigned short Level;   //�ؼ��ڵڼ��㣿
  string GraphicControl;  //�ؼ����� �����ܵ�ֵΪ"<window>" "<text>" "<div>" ...
  map<string, string> property; //�ؼ�����  titile=1, 1Ϊval��index.
  vector<string> val;           // �洢 "...."
  
  /*�����ո���ַ����洢��vector<string> val�У����ö�Ӧ��vector�±����滻�ַ�����
  ��ô����Ŀ����Ϊ�˷������ʷ��������Կո�Ϊ�����*/
  string replace_string_2_int(string line);
  MyControl(string line);
};

//line���ļ��е�һ�У�1 window title="��һ������"
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

//�ַ����浽vector����±꣬������������line�еĿո�
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
        cout << " �����ɶԡ�\n";
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
    //һ������ͬһ��������Ĵ��ڹ���һ�����ڴ�����̡�
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

//ȥ��line��ͷ�Ŀհ��ַ���
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
        
        // line�в�����ÿ�еĻ��з�
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
                      //... �������㴰��
                      create_control(con);
                  } else {
                    cout << "You should start from level 1.\n";
                    return 1;
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
                          cout << "�ӿؼ��Ĳ�������\n";
                          return 1;
                      }
                      if (con.Level == 1) {
                          cout << "����Ķ���ؼ���\n";
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
		//����Edit�ؼ����ı�
		case WM_SETTEXT:
		//�Ӵ��ڵĻ���Ӧ�÷���WM_PAINT��Ϣ��
		case WM_PAINT:
      {
        PAINTSTRUCT pt;
        HDC hdc;
        hdc=BeginPaint(hWnd,&pt);
        
        SetTextColor(hdc,RGB(255,0,0));
        SetBkColor(hdc,RGB(0,255,0));
        SetBkMode(hdc,TRANSPARENT);
        //Ϊʲô���λ��Ƴɹ�����������û�л����أ�
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
