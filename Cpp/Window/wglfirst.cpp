#include <iostream>
#include <Windows.h>
#include<gl/gl.h>

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"gdi32.lib")
#pragma comment(lib, "OpenGL32.lib")


LRESULT CALLBACK WndProc(HWND hWnd,//定义窗口回调函数，没啥解释的

                        UINT uMsg, 

                        WPARAM wParam, 

                        LPARAM lParam) 

{ 

        return 1; //没有任何作用，只是为了能成功创建窗口

}   

int main(int argc,char **argv) 

{ 

	HWND        hWnd; 

    HGLRC       hRC; 

	HDC         hDC; 

	HINSTANCE   hInstance; 

	//第 1）步：获取HINSTANCE

    hInstance =GetModuleHandle(NULL); 

    WNDCLASS    windClass; 

	TCHAR szWindowName[50] = TEXT("OpenGL_Window");//随便设

	TCHAR szClassName[50] = TEXT("OpenGL_Class"); //随便设

	//初始化窗口结构体

    windClass.lpszClassName = szClassName; 

    windClass.lpfnWndProc   = (WNDPROC)WndProc; 

    windClass.hInstance     = hInstance; 

    windClass.hCursor       =LoadCursor(NULL,IDC_ARROW); 

    windClass.hIcon         =LoadIcon(NULL,IDI_WINLOGO); 

    windClass.hbrBackground =NULL;  

    windClass.lpszMenuName  =NULL;    

    windClass.style         =0;//随便设

    windClass.cbClsExtra    = 0;   

    windClass.cbWndExtra    = 0; 

	//注册窗口类

	if(!RegisterClass( &windClass )) return 1; 

	//第 2)步：创建窗口

    hWnd = CreateWindowEx(0,     // Extended style

        szClassName,   // class name

        szWindowName,  // window name

        0, 

        0,      //window position, x

        0,      //window position, y

        0,  //height

        0, //width

        NULL,          // Parent window

        NULL,          // menu

        hInstance,     // instance

        NULL);         // pass this toWM_CREATE

	//第 3）步：获取HDC，并随意设置一个空像素格式

    hDC = GetDC(hWnd); 

    PIXELFORMATDESCRIPTOR pfd; 

    SetPixelFormat( hDC, 1,&pfd); 

	//第 4）步：创建OpenGL环境

    hRC = wglCreateContext( hDC ); 

	//第 5）步：绑定HDC与HRC

    wglMakeCurrent( hDC, hRC ); 

    const GLubyte * pb = glGetString(GL_VERSION);//获取OpenGL版本字符串

	if(pb) 

        std::cout <<"OpenGL versionis "<< pb << std::endl; 

    pb = glGetString(GL_VENDOR); //获取OpenGL显卡厂家信息字符串

	if(pb) 

        std::cout <<"OpenGL vendoris "<< pb << std::endl; 

    pb = (glGetString(GL_RENDERER)); //获取OpenGL显卡型号信息字符串

	if(pb) 

        std::cout <<"OpenGLrenderer is "<< pb << std::endl; 

    pb = glGetString(GL_EXTENSIONS); //获取OpenGL扩展函数名称字符串

	if(pb) 

        std::cout <<"OpenGLextensions is "<< pb << std::endl; 

	//一旦释放环境,glGetString函数将总是返回空值

    wglMakeCurrent(NULL,NULL); 

    wglDeleteContext(hRC); 

    ReleaseDC(hWnd, hDC); 

    DestroyWindow(hWnd); 

	//释放后再执行，则pb每次均返回空值，表明OpenGL环境已经被释放

    pb = glGetString(GL_VERSION); 

	if(pb) 

        std::cout <<"OpenGL versionis "<< pb << std::endl; 

    pb = glGetString(GL_VENDOR); 

	if(pb) 

        std::cout <<"OpenGL vendoris "<< pb << std::endl; 

    pb = (glGetString(GL_RENDERER)); 

	if(pb) 

        std::cout <<"OpenGLrenderer is "<< pb << std::endl; 

    pb = glGetString(GL_EXTENSIONS); 

	if(pb) 

        std::cout <<"OpenGLextensions is "<< pb << std::endl; 

	return 0; 

} 
