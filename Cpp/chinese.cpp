#include <iostream>   // std::wcout
#include <string>     // std::wstring, std::to_wstring

using namespace std;

int main ()
{
  string a = string("人类");
  
  printf("\n%d\n",a.length()); // 6  
  cout << a.substr(3);
  cout << a.substr(0, 3);
  return 0;
}