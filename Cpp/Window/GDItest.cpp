#include <windows.h>
#include <gdiplus.h>
#include <gl/gl.h>
#include <cmath>

//使用CString
//#include <atlstr.h>

#pragma comment(lib, "gdiplus.lib") 
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib, "OpenGL32.lib")

using namespace Gdiplus;

#define NUM 200 //绘制圆时用的顶点数

GLfloat r=1.0f; //圆半径

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

void DrawSceneGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色及深度缓存
	glLoadIdentity();
	glColor3f(1.0f,0.0f,0.0f); //设置画笔颜色
	glBegin(GL_TRIANGLES); //画三角形
	glVertex3f(0.0f,1.0f,0.0f);
	glVertex3f(-1.0f,-1.0f,0.0f);
	glVertex3f(1.0f,-1.0f,0.0f);
	glEnd();
	glTranslatef(-1.5f,1.0f,-7.0f); //移动坐标
	glTranslatef(3.0f,0.0f,0.0f);
	glColor3f(0.0f,0.0f,1.0f); //设置画笔为蓝色
	glBegin(GL_QUADS); //画四边形
	glVertex3f(-1.0f,1.0f,0.0f);
	glVertex3f(-1.0f,-1.0f,0.0f);
	glVertex3f(1.0f,-1.0f,0.0f);
	glVertex3f(1.0f,1.0f,0.0f);
	glEnd();
	glColor3f(1.0f,1.0f,0.0f);
	glTranslatef(-1.5f,-2.5f,0.0f);
	glLineWidth(2.0f); //画黄色线
	glBegin(GL_LINES);
	glVertex2f(-1.0f,0.0f);
	glVertex2f(-1.0f,0.0f);
	glEnd();
	glBegin(GL_LINE_LOOP); //画圆
	for(int i=0;i<NUM;i++) {
		glVertex3f(r*float(sin(2*3.14*i/NUM)),r*float(cos(2*3.14*i/NUM)),0.0);
	}
	glEnd();
	glFlush();
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
                    800,  
                    600,  
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
	
	HGLRC   hglrc;
	// create a rendering context
	hglrc = wglCreateContext (hdc);
	
	// make it the calling thread's current rendering context
	wglMakeCurrent(hdc, hglrc);
	
	DrawSceneGL();
	
	// make the rendering context not current
	wglMakeCurrent (NULL, NULL) ;
	
	// delete the rendering context		
	wglDeleteContext (hglrc);
	
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
