#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//���ں���SetConsoleOutputCP(65001);����cmd����Ϊutf8
#include <windows.h>

using namespace Gdiplus;
using namespace std;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib") 
#pragma comment(lib, "gdiplus.lib") 
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

struct MyControl {
  unsigned short level;   //�ؼ��ڵڼ��㣿
  string con;             //�ؼ����ƣ����ܵ�ֵΪ"<window>" "<text>" "<div>" ...
  string property;       //�ؼ�����
};

//ȥ��line��ͷ�Ŀհ��ַ���
string skip_blank(string line) {
  for (int i=0; i<line.length(); i++) {
    if (line[i]!=' ' && line[i]!='\t')
      return line.substr(i, line.length()-i);
  }
  return line;
}

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

int main() {
    SetConsoleOutputCP(65001);
    ifstream in("first.gui");
    string line;
 
    if (in) {
        // line�в�����ÿ�еĻ��з�
        while (getline (in, line)) { 
        
            line = skip_blank(line);
            cout << line << endl;
                    
            string s;
            
            if (line!="\n")
               s = get_first_token(line);
            
            cout << s << "\n";
            /*
            for (int i=0; i<s.length(); i++){
              if (!isdigit(s[i]))
                cout << "You should start with level number.\n";
            }
            
            int level = atoi(s.c_str());
            
            cout << level << "\n";*/
        }        
    } else {
        cout <<"no such file" << endl;
    }
}
