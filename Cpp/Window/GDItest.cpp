#include <windows.h>
#include <gdiplus.h>

//使用CString
//#include <atlstr.h>

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib, "GdiPlus.lib")

using namespace Gdiplus;

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

void DrawBitmap(char *filename, int x, int y, HDC device)
{
	HBITMAP image = (HBITMAP)LoadImage(0, filename, IMAGE_BITMAP, 0 ,0, LR_LOADFROMFILE);
	BITMAP bm;
	
	GetObject(image, sizeof(BITMAP), &bm);
	HDC hdcimage = CreateCompatibleDC(device);
	SelectObject(hdcimage, image);
	BitBlt(device, x, y, bm.bmWidth, bm.bmHeight, hdcimage, 0, 0, SRCCOPY);
	DeleteDC(hdcimage);
	DeleteObject((HBITMAP)image);
}
 
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
	HDC hdc = GetDC(hwnd);
	DrawBitmap("d1.bmp", 20, 40, hdc);
	
	// enter main event loop, but this time we use PeekMessage()
	// instead of GetMessage() to retrieve messages
	while(TRUE) {
		// test if there is a message in queue, if so get it
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) { 
			// test if this is a quit
			if (msg.message == WM_QUIT)
				break;
			
			// translate any accelerator keys
			TranslateMessage(&msg);
			
			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		
		// main game processing goes here
		
		// set the foreground color to random
		SetTextColor(hdc, RGB(rand()%256,rand()%256,rand()%256));
	
		// set the background color to black
		SetBkColor(hdc, RGB(0,0,0));
	
		// finally set the transparency mode to transparent
		SetBkMode(hdc, TRANSPARENT);
	
		// draw some text at a random location
		TextOut(hdc,rand()%800,rand()%800, "Green Light", strlen("Green Light"));
	
		Sleep(10);
		
	}
	
	ReleaseDC(hwnd,hdc);
	
    
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
            HWND mymdiwnd = CreateWindow("MDICLIENT", "MDICLIENT", WS_VISIBLE | WS_CHILD,  
                35, 10, 200, 100, hwnd, (HMENU)IDB_ONE, NULL, NULL);  

			HDC hdc = GetDC(mymdiwnd);
			
			// 创建红色1像素宽度的实线画笔
			HPEN hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HPEN hpen_old = (HPEN)SelectObject(hdc, hpen1);
			
			Rectangle(hdc, 40, 40, 50, 50);
				
                
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
