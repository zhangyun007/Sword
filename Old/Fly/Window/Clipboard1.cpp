// 发送数据.cpp : Defines the entry point for the console application.
// 发送数据：即向剪贴板中写入数据， 复制(Ctrl + C)动作

#include <Windows.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"User32.lib")

int main()
{
    const char *pStrData = "This is a test string for Clipboard!";

    //1. 打开剪贴板: 参数指定为 NULL，表明为当前进程打开剪贴板
    if (OpenClipboard(NULL))
    {
        char *pDataBuf = NULL;

        //2. 清空剪贴板
        EmptyClipboard();

        //3. 向剪贴板中放入数据
        //3.1 获得一块堆内存
        HGLOBAL hGlobalClip = GlobalAlloc(GHND, strlen(pStrData) + 1);

        //3.2 锁定堆内存并获得堆内存首地址
        pDataBuf = (char*)GlobalLock(hGlobalClip);
        strcpy_s(pDataBuf, strlen(pStrData) + 1, pStrData);

        //3.3 释放内存
        GlobalUnlock(hGlobalClip);

        //3.4 向剪贴板放入数据
        SetClipboardData(CF_TEXT, hGlobalClip);

        //4. 关闭剪贴板
        CloseClipboard();
    }

    return 0;
}