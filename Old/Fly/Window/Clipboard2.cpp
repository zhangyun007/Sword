// 接收数据.cpp : Defines the entry point for the console application.
// 接收数据：即从剪贴板中读取数据， 黏贴(Ctrl + V)动作

#include <Windows.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"User32.lib")

int main()
{
    //1. 打开剪贴板: 参数指定为 NULL，表明为当前进程打开剪贴板
    if (OpenClipboard(NULL))
    {
        //2. 判断剪贴板中的数据格式是否为 CF_TEXT
        if (IsClipboardFormatAvailable(CF_TEXT))
        {
            //3. 从剪贴板中获取数据
            //3.1 从剪贴板中获取格式为 CF_TEXT 的数据
            HGLOBAL hGlobalClip = GetClipboardData(CF_TEXT);

            //3.2 用GlobalLock获得地址并锁定内存
            char *pDataBuf = NULL;
            pDataBuf = (char *)GlobalLock(hGlobalClip);

            //3.3 用GlobalUnlock解除锁定内存
            GlobalUnlock(hGlobalClip);

            cout << "从剪贴板中获取到数据是：  " << pDataBuf << endl;
        }

        //4. 关闭剪贴板
        CloseClipboard();
    }

    return 0;
}