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
    printf("��A����ʼ��ȡ����...\n");
    
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
                    printf("ƥ�䵽�Ĵ��ھ��:0x%X, ���ڱ���:%s\n", (int*)h, t);
                    free(t);
                    
                    len = MessageBox(GetConsoleWindow(), "�Ƿ������ȡ?", "Ask", MB_TOPMOST | MB_YESNO | MB_ICONQUESTION);
                    if(len == IDYES)
                    {
                        h = NULL;
                        printf("��A����ʼ��ȡ����...\n");
                    }
                }
                else
                {
                    printf("�޷���ȡ������Ϣ!\n");
                }
            }
        }
        Sleep(50);
    }
    
    printf("��Q���˳�...\n");
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
