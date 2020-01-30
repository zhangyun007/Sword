#include <windows.h>
#include <commctrl.h>
#include <wchar.h>

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"ComCtl32.lib") 
#pragma comment(lib, "gdiplus.lib") 
#pragma comment(lib, "gdi32.lib")

#define ID_TABCTRL 1
#define ID_EDIT 2
#define BTN_ADD 3
#define BTN_DEL 4
#define BTN_CLR 5
#define MAX_TAB_LEN 15

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
HWND hTab, hEdit;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
    PWSTR pCmdLine, int nCmdShow) {
		
	HWND                hWnd;
    MSG  msg ;    
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Tab control";
    wc.hInstance     = hInstance;
    //wc.hbrBackground = GetSysColorBrush(RGB(255, 0, 0));
	//wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	wc.hbrBackground = CreateSolidBrush(RGB(0xff,0x0,0x0));
    wc.lpfnWndProc   = WindowProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
  
    RegisterClassW(&wc);
	
	// WS_DLGFRAME表示窗口不带标题栏
   hWnd = CreateWindowW(wc.lpszClassName, L"Tab control",
				  WS_POPUP | WS_DLGFRAME | WS_VISIBLE,
                  CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, 0, 0, hInstance, 0);  


	//SW_MAXIMIZE，全屏幕显示（看不见底层的任务栏），不等于窗口最大化。
   ShowWindow(hWnd, SW_MAXIMIZE);
   UpdateWindow(hWnd);
   
   while(GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   return (int) msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {

    TCITEMW tie;
    wchar_t text[4];
    LRESULT count, id;
    INITCOMMONCONTROLSEX icex;

    switch(msg) {

        case WM_CREATE:
       
            icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
            icex.dwICC = ICC_TAB_CLASSES;
            InitCommonControlsEx(&icex);

            hTab = CreateWindowW(WC_TABCONTROLW, NULL, WS_CHILD | WS_VISIBLE,
                0, 0, 1024, 768, hwnd,(HMENU) ID_TABCTRL, NULL, NULL);

            hEdit = CreateWindowW(WC_EDITW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
                250, 20, 100, 25, hwnd, (HMENU) ID_EDIT, NULL, NULL);

            SendMessage(hEdit, EM_SETLIMITTEXT, MAX_TAB_LEN, 0);
  
            CreateWindowW(WC_BUTTONW, L"Add", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                250, 50, 100, 25, hwnd, (HMENU) BTN_ADD, NULL, NULL);

            CreateWindowW(WC_BUTTONW, L"Delete", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                250, 80, 100, 25, hwnd, (HMENU) BTN_DEL, NULL, NULL);

            CreateWindowW(WC_BUTTONW, L"Clear", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                250, 110, 100, 25, hwnd, (HMENU) BTN_CLR, NULL, NULL);
				
			
				
            break;

        case WM_COMMAND:

            switch(LOWORD(wParam)) {

                case BTN_ADD:

                    GetWindowTextW(hEdit, text, 250);

                    if (lstrlenW(text) != 0 ) {

                        tie.mask = TCIF_TEXT;
                        tie.pszText = text;
                        count = SendMessageW(hTab, TCM_GETITEMCOUNT, 0, 0);
                        SendMessageW(hTab, TCM_INSERTITEMW, count, 
                            (LPARAM) (LPTCITEM) &tie);
                    }
                    break;

                case BTN_DEL:
                
                    id = SendMessageW(hTab, TCM_GETCURSEL, 0, 0);
                    
                    if (id != -1) {
                    
                       SendMessageW(hTab, TCM_DELETEITEM, 0, id);
                    }
                    break;

                case BTN_CLR:
               
                    SendMessageW(hTab, TCM_DELETEALLITEMS, 0, 0);
                    break;
            } 
            break;

        case WM_DESTROY:
        
            PostQuitMessage(0);
            break;
    }
   
    return(DefWindowProcW(hwnd, msg, wParam, lParam));
}