#include <windows.h>

//使用CString
//#include <atlstr.h>

#pragma comment(lib,"User32.lib")

//按钮ID
#define IDB_ONE     3301  
#define IDB_TWO     3302  
#define IDB_THREE   3303  
 
//函数声明
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);  
  
LPCSTR WINDOWS_CLASS = "MyWindowClass";    //类名  
LPCSTR WINDOWS_TITLE = "测试按钮";   //窗口标题  

//CString str("abcd");

WNDCLASSEX wc = { };  

 
int WINAPI wWinMain(HINSTANCE hThisApp,  
    HINSTANCE hPrevApp,  
    LPWSTR lpCmd,  
    int nShow)  
{  
    wc.cbSize = sizeof(WNDCLASSEX);  
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;  
    wc.hInstance = hThisApp;  
    wc.lpfnWndProc = (WNDPROC)WindowProc;  
    wc.lpszClassName = WINDOWS_CLASS;  
    wc.style = CS_HREDRAW | CS_VREDRAW;  
	//wc.style = WS_POPUP | WS_BORDER | WS_THICKFRAME;
    RegisterClassEx(&wc);  
    
    
    HWND hwnd = CreateWindowEx(WS_EX_WINDOWEDGE | WS_HSCROLL,  
                    WINDOWS_CLASS,  
                    WINDOWS_TITLE,  
                    WS_OVERLAPPEDWINDOW,  
                    20,  
                    25,  
                    400,  
                    300,  
                    NULL,  
                    NULL,  
                    hThisApp,  
                    NULL);  
    if (hwnd == NULL)  
    {
        return -1;
    }
          
	ShowWindow(hwnd, nShow);  
    UpdateWindow(hwnd);  
 
    MSG msg;  
    while(GetMessage(&msg,NULL,0,0))  
    {  
        TranslateMessage(&msg);  
        DispatchMessage(&msg);  
    }  
    
    return 0;  
}  
  
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)  
{  
    switch(msg) {  
	
    case WM_DESTROY:  
        PostQuitMessage(0);  
        return 0;  
 
    case WM_CREATE: 
		{  
			//MessageBox(hwnd, "ФЫВФЫ", "提示", MB_OK | MB_ICONINFORMATION);  
			
            //创建三个按钮  
            HWND mymdiwnd = CreateWindow("MDICLIENT", "MDICLIENT", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
                35, 10, 200, 100, hwnd, (HMENU)IDB_ONE, NULL, NULL);  
                
            CreateWindow("LISTBOX", "LISTBOX", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
                35, 150, 160, 60, hwnd, (HMENU)IDB_TWO, NULL, NULL); 
                 
            CreateWindow("Button", "Button", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  
                35, 250, 160, 60, hwnd, (HMENU)IDB_THREE, NULL, NULL);  
		}  
		return 0; 
         
    case WM_COMMAND:  
        {  
            switch(LOWORD(wParam))  
            {  
            case IDB_ONE:  
                //MessageBox(hwnd, L"您点击了第一个按钮。", L"提示", MB_OK | MB_ICONINFORMATION);  
                SendMessage((HWND)lParam, WM_SETTEXT, (WPARAM)NULL, (LPARAM)"First");  
                break;  
                
            case IDB_TWO:  
                //MessageBox(hwnd, L"您点击了第二个按钮。", L"提示", MB_OK | MB_ICONINFORMATION);  
                SendMessage((HWND)lParam, WM_SETTEXT, (WPARAM)NULL, (LPARAM)"Second");  
                break;  
                
            case IDB_THREE:  
                //MessageBox(hwnd, L"您点击了第三个按钮。", L"提示", MB_OK | MB_ICONINFORMATION);  
                SendMessage((HWND)lParam, WM_SETTEXT, (WPARAM)NULL, (LPARAM)"第三个按鈕已点击");  
                break;  
                
            default:  
                break;  
            }  
        }  
        return 0;  
        
    default:  
        return DefWindowProc(hwnd,msg,wParam,lParam);  
    }  
    
    return 0;  
}  
