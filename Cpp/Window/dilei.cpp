//扫雷
#include <windows.h>
#include <windowsx.h>
#include <strsafe.h>
#include <time.h>


#pragma comment(lib,"User32.lib")
#pragma comment(lib,"gdi32.lib")


//格子区域大小（DIVISIONS * DIVISIONS）
#define DIVISIONS 20
//地雷数
#define MINECOUNT 40

//消息处理
LRESULT CALLBACK DealMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//写入地雷
void SetMine(int(*pChess)[DIVISIONS]);
//获取随机数
unsigned int GetRand();
//判断胜利
bool Win(int(*pChess)[DIVISIONS], int *pNotClickCount, int *pClickCount);
//重置
void Reset(HWND hWnd,int(*pChess)[DIVISIONS], int(*pClick)[DIVISIONS]);

int WINAPI WinMain(
    HINSTANCE hInstance,    // 当前实例句柄
    HINSTANCE hPrevInstance,// 前一实例句柄
    LPSTR lpCmdLine,        // 指向命令行参数的指针
    int nCmdShow            // 窗口的显示方式
    )
{
    HWND hWnd;
    MSG msg;
    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//画刷背景BLACK_PEN
    wndClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
    wndClass.hIcon = LoadIcon(NULL, IDC_ARROW);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = DealMessage;
    wndClass.lpszClassName = TEXT("MineSweeping");
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wndClass))
    {
        MessageBox(NULL, TEXT("注册类失败，请检查参数是否成功设置"), TEXT("提示"), MB_OK);
    }

    hWnd = CreateWindow(TEXT("MineSweeping"),    // 窗口类名称
        TEXT("扫雷"),            // 窗口标题栏名称
        WS_OVERLAPPEDWINDOW,            // 窗口样式
        CW_USEDEFAULT,                    // 窗口水平位置
        CW_USEDEFAULT,                    // 窗口垂直位置
        CW_USEDEFAULT,                    // 窗口宽度
        CW_USEDEFAULT,                    // 窗口高度
        NULL,                            // 父窗口句柄
        NULL,                            // 窗口菜单句柄
        hInstance,                        // 窗口实例句柄
        NULL);                            // 窗口创建参数
    if (!hWnd)  // 新窗口创建失败
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


LRESULT CALLBACK DealMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //初始化要用到的变量
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    HBRUSH hBrush, hOldBrush;
    TEXTMETRIC tm;
    static int cxChar,cxCaps,cyChar;

    //输出整形用的缓冲区
    TCHAR szBuffer[128];
    size_t iTarget;

    //地雷以及点击后雷个数存储区
    static int iChess[DIVISIONS][DIVISIONS];
    int(*pChess)[DIVISIONS] = iChess;
    //点击后记录点击事件存储区
    static int iClick[DIVISIONS][DIVISIONS];
    int(*pClick)[DIVISIONS] = iClick;

    //pSize：当前一个格子宽高
    //p：通用
    static POINT pSize = { 0,0 }, p;

    //未点击的格子
    int iNotClickCount;
    //已经点击的格子
    int iClickCount;

    switch (uMsg)
    {
    case WM_CREATE:
        hdc = GetDC(hWnd);
        //初始化
        Reset(hWnd, pChess, pClick);
        //获取字体高度
        GetTextMetrics(hdc, &tm);
        cyChar = tm.tmHeight + tm.tmExternalLeading;
        //平均宽度
        cxChar = tm.tmAveCharWidth;
        //判断是否等宽字体
        cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;

        ReleaseDC(hWnd, hdc);
        return 0;
    case WM_KEYDOWN:
        //在没有鼠标的情况下，键盘模拟鼠标操作
        ShowCursor(false);
        GetCursorPos(&p);
        ScreenToClient(hWnd, &p);
        p.x = max(0, min(DIVISIONS - 1, p.x / pSize.x));
        p.y = max(0, min(DIVISIONS - 1, p.y / pSize.y));

        switch (wParam)
        {
        case VK_UP:
            p.y = max(0, p.y - 1);
            break;
        case VK_DOWN:
            p.y = min(DIVISIONS - 1, p.y + 1);
            break;
        case VK_LEFT:
            p.x = max(0, p.x - 1);
            break;
        case VK_RIGHT:
            p.x = min(DIVISIONS - 1, p.x + 1);
            break;
        case VK_HOME:
            p.x = p.y = 0;
            break;
        case VK_END:
            p.x = p.y = DIVISIONS - 1;
            break;
        case VK_RETURN:
        case VK_SPACE:
            SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(p.x * pSize.x, p.y * pSize.y));
            break;
        }
        p.x = (p.x * pSize.x) + (pSize.x / 2);
        p.y = (p.y * pSize.y) + (pSize.y / 2);

        ClientToScreen(hWnd, &p);
        SetCursorPos(p.x, p.y);
        ShowCursor(true);
        return 0;
    case WM_SIZE:
        //pSize每个格子大小，X宽，Y高
        pSize.x = LOWORD(lParam) / DIVISIONS;
        pSize.y = HIWORD(lParam) / DIVISIONS;
        return 0;
    case WM_LBUTTONDOWN:
        p.x = GET_X_LPARAM(lParam) / pSize.x;
        p.y = GET_Y_LPARAM(lParam) / pSize.y;
        if (p.x >= DIVISIONS || p.y >= DIVISIONS)
        {
            MessageBeep(0);
            return 0;
        }
        switch (iClick[p.x][p.y])
        {
        case 1:
            MessageBeep(0);
            return 0;
        case 2:
            MessageBeep(0);
            return 0;
        }
        //判断是否点击到了雷
        if (iChess[p.x][p.y] == -1)
        {
            if (MessageBox(hWnd, TEXT("你踩到地雷了！"), TEXT("boom"), MB_OK) == IDOK)
            {
                Reset(hWnd,pChess, pClick);
                InvalidateRect(hWnd, NULL, true);
            }
        }
        else
        {
            //当前位置修改为点击过
            iClick[p.x][p.y] = 1;
            //判断是否胜利
            if (Win(pClick, &iNotClickCount, &iClickCount))
            {
                if (MessageBox(hWnd, TEXT("you win！"), TEXT("wow"), MB_OK) == IDOK)
                {
                    Reset(hWnd,pChess, pClick);
                }
            }
            //标题显示信息
            StringCchPrintf(szBuffer, sizeof(szBuffer), TEXT("当前已经翻出的区域数%d，剩余区域数%d"), iClickCount, iNotClickCount);
            StringCchLength(szBuffer, sizeof(szBuffer), &iTarget);
            SetWindowText(hWnd, szBuffer);
            //计算当前点击位置附近雷数
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    //超出客户区的格子不计算
                    if (p.x + x >= 0 && p.x + x < DIVISIONS && p.y + y >= 0 && p.y + y < DIVISIONS)
                    {
                        //当前格子不计算
                        if (x != 0 || y != 0) {
                            if (iChess[p.x + x][p.y + y] == -1)
                            {
                                iChess[p.x][p.y]++;
                            }
                        }
                    }
                }
            }
        }
        //重绘格子
        rect.left = p.x * pSize.x;
        rect.top = p.y * pSize.y;
        rect.right = (p.x + 1) * pSize.x;
        rect.bottom = (p.y + 1) * pSize.y;
        InvalidateRect(hWnd, &rect, true);
        return 0;
    case WM_RBUTTONDOWN:
        p.x = GET_X_LPARAM(lParam) / pSize.x;
        p.y = GET_Y_LPARAM(lParam) / pSize.y;
        if (p.x >= DIVISIONS || p.y >= DIVISIONS)
        {
            MessageBeep(0);
            return 0;
        }
        //当前格子标记地雷状态切换
        switch (iClick[p.x][p.y])
        {
        case 0:
            iClick[p.x][p.y] = 2;
            break;
        case 2:
            iClick[p.x][p.y] = 0;
            break;
        default:
            MessageBeep(0);
            return 0;
        }
        //重绘格子
        rect.left = p.x * pSize.x;
        rect.top = p.y * pSize.y;
        rect.right = (p.x + 1) * pSize.x;
        rect.bottom = (p.y + 1) * pSize.y;
        InvalidateRect(hWnd, NULL, true);
        return 0;
    case WM_MOUSEMOVE:
        //鼠标超出扫雷区域鼠标禁止点击
        p.x = GET_X_LPARAM(lParam) / pSize.x;
        p.y = GET_Y_LPARAM(lParam) / pSize.y;
        if (p.x >= DIVISIONS || p.y >= DIVISIONS)
        {
            SetCursor(LoadCursor(NULL, IDC_NO));
        }
        else
        {
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        //扫雷棋盘绘画
        for (int i = 1; i < DIVISIONS; i++)
        {
            MoveToEx(hdc, pSize.x * i, 0, NULL);
            LineTo(hdc, pSize.x * i, pSize.y * DIVISIONS);

            MoveToEx(hdc, 0, pSize.y * i, NULL);
            LineTo(hdc, pSize.x * DIVISIONS, pSize.y * i);
        }
        //扫雷点击绘画
        for (int x = 0; x < DIVISIONS; x++)
        {
            for (int y = 0; y < DIVISIONS; y++)
            {
                //0：未开过的格子，1：开过的格子，2：标记过的格子
                switch (iClick[x][y])
                {
                case 1:
                    //每个格子背景变成灰色
                    hBrush = CreateSolidBrush(RGB(220, 220, 220));hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                    Rectangle(hdc, x * pSize.x, y * pSize.y, (x + 1) * pSize.x, (y + 1) * pSize.y);
                    SelectObject(hdc, hOldBrush);DeleteObject(hBrush);DeleteObject(hOldBrush);

                    //当前格子写入地雷数
                    //地雷数颜色随地雷数改变
                    switch (iChess[x][y])
                    {
                    case 0:
                        SetTextColor(hdc, RGB(0, 0, 0)); break;
                    case 1:
                        SetTextColor(hdc, RGB(0, 0, 255)); break;
                    case 2:
                        SetTextColor(hdc, RGB(144, 238, 144)); break;
                    case 3:
                        SetTextColor(hdc, RGB(255, 0, 0)); break;
                    case 4:
                        SetTextColor(hdc, RGB(255, 0, 255)); break;
                    case 5:
                        SetTextColor(hdc, RGB(139, 0, 0)); break;
                    case 6:
                        SetTextColor(hdc, RGB(0, 100, 0)); break;
                    }
                    SetBkMode(hdc, TRANSPARENT);
                    StringCchPrintf(szBuffer, sizeof(szBuffer), TEXT("%d"), iChess[x][y]);
                    StringCchLength(szBuffer, sizeof(szBuffer), &iTarget);
                    TextOut(hdc, (x * pSize.x) + (pSize.x / 2) - (cxChar / 2), (y * pSize.y) + (pSize.y / 2) - (cyChar / 2), szBuffer, iTarget);
                    break;
                case 2:
                    hBrush = CreateSolidBrush(RGB(255, 0, 0));hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                    //画一个标记的旗子
                    MoveToEx(hdc, (x * pSize.x) + (pSize.x / 2), (y * pSize.y) + (pSize.y / 2) - 5, NULL);
                    LineTo(hdc, (x * pSize.x) + (pSize.x / 2), (y * pSize.y) + (pSize.y / 2) + 5);

                    Rectangle(hdc, (x * pSize.x) + (pSize.x / 2), (y * pSize.y) + (pSize.y / 2) - 5, (x * pSize.x) + (pSize.x / 2) + 10, (y * pSize.y) + (pSize.y / 2));

                    MoveToEx(hdc, (x * pSize.x) + (pSize.x / 2) - 3, (y * pSize.y) + (pSize.y / 2) + 5, NULL);
                    LineTo(hdc, (x * pSize.x) + (pSize.x / 2) + 3, (y * pSize.y) + (pSize.y / 2) + 5);

                    SelectObject(hdc, hOldBrush);DeleteObject(hBrush);DeleteObject(hOldBrush);
                    break;
                }

            }
        }

        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
//产生随机数
unsigned int GetRand()
{
    int r = rand();
    r = r % DIVISIONS;
    return r;
}

//写入地雷
void SetMine(int(*pChess)[DIVISIONS])
{
    POINT pPoint;
    for (int i = 0; i < MINECOUNT; i++)
    {
        while (true)
        {
            pPoint.x = GetRand();
            pPoint.y = GetRand();
            if (pChess[pPoint.x][pPoint.y] != -1)
            {
                pChess[pPoint.x][pPoint.y] = -1;
                break;
            }
        }
    }
    return;
}

//判断获胜
bool Win(int(*pChess)[DIVISIONS],int *pNotClickCount,int *pClickCount)
{
    int i = 0;
    for (int x = 0; x < DIVISIONS; x++)
    {
        for (int y = 0; y < DIVISIONS; y++)
        {
            if (pChess[x][y] == 0|| pChess[x][y] == 2)
            {
                i++;
            }
        }
    }
    *pNotClickCount = i;
    *pClickCount = (DIVISIONS * DIVISIONS) - i;
    if (i - MINECOUNT == 0)
    {
        return true;
    }
    return false;
}

//重置
void Reset(HWND hWnd,int(*pChess)[DIVISIONS], int(*pClick)[DIVISIONS])
{
    //防止随机数重复
    srand((unsigned(time(NULL))));
    SetCursor(LoadCursor(NULL, IDC_WAIT));
    for (int x = 0; x < DIVISIONS; x++)
    {
        for (int y = 0; y < DIVISIONS; y++)
        {
            pChess[x][y] = 0;
            pClick[x][y] = 0;
        }
    }
    //memset(pChess, 0, sizeof(pChess));
    //memset(pClick, 0, sizeof(pClick));
    SetMine(pChess);
    SetCursor(LoadCursor(NULL, IDC_ARROW));
    InvalidateRect(hWnd, NULL, true);
    return;
}