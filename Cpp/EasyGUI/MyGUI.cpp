#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//用于函数SetConsoleOutputCP(65001);更改cmd编码为utf8
#include <windows.h>

using namespace Gdiplus;
using namespace std;

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib") 
#pragma comment(lib, "gdiplus.lib") 
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

struct MyControl {
  unsigned short level;   //控件在第几层？
  string con;             //控件名称，可能的值为"<window>" "<text>" "<div>" ...
  string property;       //控件属性
};

//去掉line开头的空白字符。
string skip_blank(string line) {
  for (int i=0; i<line.length(); i++) {
    if (line[i]!=' ' && line[i]!='\t')
      return line.substr(i, line.length()-i);
  }
  return line;
}

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

int main() {
    SetConsoleOutputCP(65001);
    ifstream in("first.gui");
    string line;
 
    if (in) {
        // line中不包括每行的换行符
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
