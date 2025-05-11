#define WINVER 0x0501
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

HWND h = NULL;
BOOL CALLBACK pro(DWORD d);

int main()
{
    char name[1024] = {0};
    bool sh = true;
    printf("按A键开始获取窗口...\n");
    
    while(!h)
    {
        POINT pos = {0};
        if(GetKeyState('A') & 0x8000)
        {
            BOOL re = GetCursorPos(&pos);
            if(re)
            {
                h = WindowFromPoint(pos);
                if(h)
                {
                    char *t = NULL;
                    int len = GetWindowTextLength(h) + 1;
                    t = (char *)malloc(sizeof(char) * len);
                    ZeroMemory(t, sizeof(char) * len);
                    GetWindowText(h, t, len);
                    printf("匹配到的窗口句柄:0x%X, 窗口标题:%s\n", (int*)h, t);
                    free(t);
                    
                    len = MessageBox(GetConsoleWindow(), "是否继续获取?", "Ask", MB_TOPMOST | MB_YESNO | MB_ICONQUESTION);
                    if(len == IDYES)
                    {
                        h = NULL;
                        printf("按A键开始获取窗口...\n");
                    }
                }
                else
                {
                    printf("无法获取窗口信息!\n");
                }
            }
        }
        Sleep(50);
    }
    
    printf("按Q键退出...\n");
    printf("Enter Title:");
    scanf("%s", name);
    SetWindowText(GetConsoleWindow(), name);
    SetConsoleCtrlHandler(pro, TRUE);
    system("cls");
    
    while(true)
    {
        sh = !sh;
        ShowWindow(h, (sh ? SW_SHOW : SW_HIDE));
        printf("%sPress anything to toggle(Q to quit).\n",(sh ? "Show\n" : "Hide\n"));
        char ch = _getch();
	if(ch == 'Q' || ch == 'q')break;
    }
    
    ShowWindow(h, SW_SHOW);
    return 0;
}

BOOL CALLBACK pro(DWORD d)
{
    switch(d)
    {
        case CTRL_C_EVENT:
        case CTRL_CLOSE_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            ShowWindow(h, SW_SHOW);
            return TRUE;
    }
    return TRUE;
}
