#include <windows.h>

#pragma comment(lib,"User32.lib")

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	MessageBox(NULL, TEXT("abcdef"), TEXT("消息对话框"), MB_OK | MB_ICONINFORMATION);  
	return 0;
}
