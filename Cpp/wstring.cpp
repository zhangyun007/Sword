// to_wstring example
#include <iostream>   // std::wcout
#include <string>     // std::wstring, std::to_wstring
#include <codecvt>

int main ()
{
    auto LocUtf8 = std::locale(std::locale(""), new std::codecvt_utf8<wchar_t>);
    std::wcout.imbue(LocUtf8);
    
  std::wstring pi = L"pi is 测试";
  std::wstring perfect = L" is a perfect number 非常";
  std::wcout << pi << L'\n';
  std::wcout << perfect << L'\n';
  return 0;
}