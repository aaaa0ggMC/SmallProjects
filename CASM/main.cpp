#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

//Windows at least XP
#define WINVER 0X500
#include "wst.h"
#include "res.h"
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <shlobj.h>
#include <sys/stat.h>
#include <malloc.h>

using namespace std;

typedef TCHAR WChar;
typedef TCHAR AChar[];
typedef TCHAR * PWChar;
typedef TCHAR tchar;

#define ID_TEXTBOX 114514

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

///CreateNewFileProc///
INT_PTR CALLBACK DlgNewproc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK FileInfoDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK VerProc(HWND, UINT, WPARAM, LPARAM);

void GetFilePathDirectory(const TCHAR path[MAX_PATH], TCHAR in[MAX_PATH]);

///Define Class Name///
AChar szClassName = _T("CASM");

AChar saying = "如果您想康康该应用参考了什么，那么以下为内容:\n";

TCHAR bufferPath[MAX_PATH];

const ULONG_PTR mSave = 1, mRun = 2, mVer = 3, mSee = 4, mNew = 5, mOpen = 6, mSelAll = 7, mInfo = 8, mBuf = 9;

HWND hwnd, textBox;

bool fileSaved = false;
HINSTANCE mins = NULL;

int SaveFile();
int NewFile();
int OpenFileS();
int ShowInfo();
void LoadEnvs();
int file_size(char* filename);
void GetMeaning(int err, char* s, int size);
int FlushToBuffer();

int szTc = sizeof(TCHAR);
int pthSz = MAX_PATH * sizeof(TCHAR);

WChar filePath[MAX_PATH] = { 0 };
WChar fileDirectory[MAX_PATH] = { 0 };

FILE* fBufferI = NULL;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    ///Define Class///
    WNDCLASSEX wincl;
    ///Register class///
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));

    ///Check whether class register works or not///
    if (!RegisterClassEx(&wincl))
        return 0;

    mins = hThisInstance;
    LoadEnvs();

    ///Allocate Variables///
    MSG messages;

    ///Creating Menu///
    HMENU menu = CreateMenu();
    HMENU menuFile = CreatePopupMenu();
    HMENU menuVer = CreatePopupMenu();
    HMENU menuEdit = CreatePopupMenu();

    ///Append Menu Item///
    AppendMenu(menu, MF_POPUP, (UINT_PTR)menuFile, "文件");
    AppendMenu(menu, MF_POPUP, (UINT_PTR)menuEdit, "编辑");
    AppendMenu(menu, MF_POPUP, (UINT_PTR)menuVer, "其他");
    //Add File content
    AppendMenu(menuFile, MF_STRING, mNew, "新建(Ctrl+N)");
    AppendMenu(menuFile, MF_STRING, mOpen, "打开(Ctrl+O)");
    AppendMenu(menuFile, MF_STRING, mInfo, "信息(Ctrl+I)");
    AppendMenu(menuFile, MF_STRING, mSave, "保存(Ctrl+S)");
    AppendMenu(menuFile, MF_STRING, mRun, "运行(Ctrl+R)");
    AppendMenu(menuFile, MF_STRING, mBuf, "将文件输入缓存(Ctrl+Shift+B)");
    //Edit Menu
    AppendMenu(menuEdit, MF_STRING, mSelAll, "全选(Ctrl+A)");
    //Add Other Content
    AppendMenu(menuVer, MF_STRING, mVer, "版本");
    AppendMenu(menuVer, MF_STRING, mSee, "参考资料");

    ///Creating Window///
    hwnd = CreateWindowEx(0, szClassName, _T("CASM *(未保存)"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, HWND_DESKTOP, menu, hThisInstance, NULL);
    textBox = CreateWindowEx(0, "EDIT", _T(""), WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN,
        0, 0, 782, 440, hwnd, (HMENU)ID_TEXTBOX, hThisInstance, NULL);
    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    ShowWindow(hwnd, nCmdShow);
    ShowWindow(textBox, SW_SHOW);
    //一个临时代码块
    {
        FILE* tmpFile = fopen(bufferPath, "r");
        if (tmpFile) {
            fread(filePath, sizeof(TCHAR), MAX_PATH, tmpFile);
            GetFilePathDirectory(filePath, fileDirectory);
            fBufferI = fopen(filePath, "r");
            if (!fBufferI) {
                fclose(tmpFile);
                TCHAR tc[MAX_PATH + 64] = { 0 };
                sprintf(tc, "del \"%s\"", bufferPath);
                system(tc);
                ZeroMemory(filePath, pthSz);
                ZeroMemory(fileDirectory, pthSz);
            }
            else {
                int fsz = file_size(filePath);
                if (fsz == -1) {
                    fclose(tmpFile);
                    TCHAR tc[MAX_PATH + 64] = { 0 };
                    sprintf(tc, "del \"%s\"", bufferPath);
                    system(tc);
                    ZeroMemory(filePath, pthSz);
                    ZeroMemory(fileDirectory, pthSz);
                }
                else {
                    int lns = 0;
                    int addr = 0;
                    TCHAR* strsz = (TCHAR*)malloc(sizeof(TCHAR) * (fsz + 1));
                    ZeroMemory(strsz, sizeof(TCHAR) * (fsz + 1));
                    fread(strsz, sizeof(TCHAR), fsz, fBufferI);
                    TCHAR* strsz2 = (TCHAR*)malloc(sizeof(TCHAR) * (fsz + 1 + lns));
                    for (int i = 0; i < fsz; i++) {
                        char s = strsz[i];
                        if (s != '\n') {
                            strsz2[i + addr] = strsz[i];
                        }
                        else {
                            strsz2[i + addr] = '\r';
                            addr++;
                            strsz2[i + addr] = '\n';
                        }
                    }
                    SetWindowText(textBox, strsz2);
                    free(strsz);
                    free(strsz2);
                    fileSaved = true;
                    SetWindowText(hwnd, "CASM");
                }
                fclose(fBufferI);
            }
            fclose(tmpFile);
        }
    }

    while (GetMessage(&messages, NULL, 0, 0))
    {
        if (GetKeyState(VK_CONTROL) & 0x8000) {
            if (GetKeyState('A') & 0x8000) {
                SendDlgItemMessage(hwnd, ID_TEXTBOX, EM_SETSEL, 0, -1);
            }
            else if (GetKeyState('S') & 0x8000) {
                int rt = SaveFile();
                if (rt == -1) {
                    MessageBox(hwnd, "无法保存文件！", "错误", MB_ICONERROR);
                }
                else if (!rt) {
                    SetWindowText(hwnd, "CASM");
                    fileSaved = true;
                }
            }
            else if (GetKeyState('O') & 0x8000) {
                OpenFileS();
                SetWindowText(hwnd, "CASM");
            }
            else if (GetKeyState('R') & 0x8000) {
                MessageBox(hwnd, "开发中(^-^)!", "提示", MB_ICONINFORMATION);
            }
            else if (GetKeyState('I') & 0x8000) {
                ShowInfo();
            }
            else if (GetKeyState('N') & 0x8000) {
                //不可用PostMessage ta讲究时效性，要求窗口立马执行，在这里会堵塞！
                SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(mNew, 0), 0);
            }
            else if (GetKeyState(VK_SHIFT) & 0x8000) {
                if (GetKeyState('B') & 0x8000) {
                    FlushToBuffer();
                }
            }
        }
        else {
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }
    }

    return messages.wParam;
}

INT_PTR CALLBACK FileInfoDlg(HWND h, UINT u, WPARAM w, LPARAM p) {
    int allocSz = 0;
    TCHAR* com;
    switch (u) {
        case WM_CLOSE:
        case WM_DESTROY:
            EndDialog(h, 0);
            break;
        case WM_INITDIALOG:
            SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
            allocSz = sizeof(TCHAR) * (MAX_PATH + 64);
            com = (TCHAR*)malloc(allocSz);
            ZeroMemory(com, allocSz);
            sprintf(com, "&文件路径(点击可打开):%s", filePath);
            SetDlgItemText(h, DLG_FILE_NAME, com);
            ZeroMemory(com, allocSz);
            sprintf(com, "文件大小:%d", file_size(filePath));
            SetDlgItemText(h, DLG_FILE_SIZE, com);
            free(com);
            break;
        case WM_COMMAND:
            switch (LOWORD(w)) {
                case DLG_OPEN_PATH:
                    com = (TCHAR*)malloc(sizeof(TCHAR) * (MAX_PATH + 64));
                    ZeroMemory(com, sizeof(TCHAR) * (MAX_PATH + 64));
                    sprintf(com, "start explorer \"%s\"", fileDirectory);
                    system(com);
                    free(com);
                    break;
            }
            break;
        default:
            return DefWindowProc(h, u, w, p);
    }
    return 0;
}

INT_PTR CALLBACK VerProc(HWND h, UINT u, WPARAM w, LPARAM p) {
    switch (u) {
        case WM_CLOSE:
        case WM_DESTROY:
            SetFocus(hwnd);
            EndDialog(h, 0);
            break;
        case WM_INITDIALOG:
            SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
            break;
        default:
            return DefWindowProc(h, u, w, p);
    }
    return 0;
}

int ShowInfo() {
    if (!strcmp(filePath, "")) {
        MessageBox(hwnd, "未打开文件，请打开文件后在试试!", "错误", MB_ICONERROR);
        return -1;
    }
    return DialogBox(mins, MAKEINTRESOURCE(IDI_DLG_INFO), hwnd, FileInfoDlg);
}

void GetFilePathDirectory(const TCHAR path[MAX_PATH], TCHAR in[MAX_PATH]) {
    int loc = 0;
    for (int i = MAX_PATH - 1; i > -1; i--) {
        if (path[i] == '\\' || path[i] == '/') {
            loc = i;
            break;
        }
    }
    strncpy(in, path, loc);
    in[loc] = '\0';
}

int FlushToBuffer() {
    if (!strcmp(filePath, "")) {
        MessageBox(hwnd, "未打开文件!", "错误", MB_ICONERROR);
        return -1;
    }
    fBufferI = fopen(bufferPath, "w");
    if (!fBufferI) {
        TCHAR txt[1024] = { 0 };
        TCHAR cst[1024] = { 0 };
        GetMeaning(errno, cst, 1024 * sizeof(TCHAR));
        sprintf(txt, "文件打开失败!错误码:%d(%s)", errno, cst);
        MessageBox(hwnd, txt, "错误", MB_ICONERROR);
        return -1;
    }
    fwrite((const void*)filePath, sizeof(TCHAR), MAX_PATH, fBufferI);
    fclose(fBufferI);
    return 0;
}

void LoadEnvs() {
    system("if not exist \"%APPDATA%\\CASM\" mkdir \"%APPDATA%\\CASM\"");
    TCHAR* appdata = getenv("APPDATA");
    if (!appdata) {
        MessageBox(hwnd, "电脑失去环境变量AppData，无法定位合法存储区!!", "严重错误", MB_ICONERROR);
        ExitProcess(-1);
    }
    TCHAR loc[MAX_PATH] = { 0 };
    sprintf(loc, "%s\\CASM\\buffer.buf", appdata);
    strcpy(bufferPath, loc);
}

int file_size(char* filename){
    struct stat statbuf;
    int ret;
    ret = stat(filename,&statbuf);//调用stat函数
    if(ret != 0) return -1;//获取失败。
    return statbuf.st_size;//返回文件大小。
}

void GetMeaning(int err,char * s,int size){
    if(err == 13){
        strncpy(s,"拒绝访问(文件别占用或者只读)",size);
    }else if(err == 22){
        strncpy(s,"不合适的路径或者文件",size);
    }else{
        strncpy(s,"Unknown",size);
    }
}

int SaveFile(){
    if(fileSaved){
        return -2;
    }
    if(!strcmp(filePath,"")){
        int rt = NewFile();
        if(rt)return -2;
    }
    //printf("fp:%s",filePath);
    fBufferI = fopen(filePath,"w");
    if(!fBufferI){
        TCHAR txt[1024] = {0};
        TCHAR cst[1024] = {0};
        GetMeaning(errno,cst,1024 * sizeof(TCHAR));
        sprintf(txt,"文件写入失败!错误码:%d(%s)",errno,cst);
        AssertE(txt,hwnd);
        return -1;
    }
    int len = GetWindowTextLength(textBox);
    TCHAR * c = (TCHAR *)malloc(sizeof(TCHAR) * (len+1));
    ZeroMemory(c,sizeof(TCHAR) * (len+1));
    GetWindowText(textBox,c,len);
    fwrite((const void *)c,sizeof(TCHAR),len+1,fBufferI);
    fclose(fBufferI);
    return 0;
}

int OpenFileS(){
    BOOL bSel;
    OPENFILENAME file = {0};
    ZeroMemory(filePath,sizeof(TCHAR) * MAX_PATH);
    file.hwndOwner = hwnd;
    file.lStructSize = sizeof(file);
    file.lpstrFilter = _T("cAsm文件(*.casm,*.asmx)\0*.casm;*.asmx\0*.*(*.*)\0*.*\0");//要选择的文件后缀
    file.lpstrInitialDir = _T("C:\\");//默认的文件路径
    file.lpstrFile = filePath;//存放文件的缓冲区
    file.nMaxFile = MAX_PATH;
    file.nFilterIndex = 0;
    file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//标志如果是多选要加上OFN_ALLOWMULTISELECT

    bSel = GetOpenFileName(&file);
    if(bSel){
        GetFilePathDirectory(filePath,fileDirectory);
        //printf(fileDirectory);
        fBufferI = fopen(filePath,"r");
        if(!fBufferI){
            TCHAR txt[1024] = {0};
            TCHAR cst[1024] = {0};
            GetMeaning(errno,cst,1024 * sizeof(TCHAR));
            sprintf(txt,"文件打开失败!错误码:%d(%s)",errno,cst);
            AssertE(txt,hwnd);
            return -1;
        }
        int fsz = file_size(filePath);
        if(fsz == -1){
            AssertE("无法获取文件信息，请确保文件可以访问！",hwnd);
            return -1;
        }
        //printf("%d",fsz);
        int lns = 0;
        int addr = 0;
        TCHAR * strsz = (TCHAR *)malloc(sizeof(TCHAR) * (fsz+1));
        ZeroMemory(strsz,sizeof(TCHAR) * fsz);
        fread(strsz,sizeof(TCHAR),fsz,fBufferI);
        TCHAR * strsz2 = (TCHAR *)malloc(sizeof(TCHAR) * (fsz+1+lns));
        for(int i = 0;i < fsz;i++){
            char s = strsz[i];
            if(s != '\n'){
                strsz2[i+addr] = strsz[i];
            }else{
                strsz2[i+addr] = '\r';
                addr++;
                strsz2[i+addr] = '\n';
            }
        }
        SetWindowText(textBox,strsz2);
        free(strsz);
        free(strsz2);
        fclose(fBufferI);
    }
    fileSaved = true;
    return 0;
}


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam)){
            case mNew:
                if(!fileSaved){
                    if(Q("文件未保存，是否保存文件?",hwnd) == IDYES){
                        int rt = SaveFile();
                        if(rt == -1){
                            AssertE("无法保存文件！",hwnd);
                        }else if(!rt){
                            SetWindowText(hwnd,"CASM");
                            fileSaved = true;
                        }
                        //printf("已保存");
                    }
                }
                NewFile();
                SetWindowText(textBox,"");
                break;
            case mOpen:
                OpenFileS();
                SetWindowText(hwnd,"CASM");
                break;
            case mBuf:
                FlushToBuffer();
                break;
            case mInfo:
                ShowInfo();
                break;
            case mSee:
                AssertE("有问题，再修了.@-@",hwnd);
                break;
                /*if(!fileSaved){
                    int id = MessageBox(hwnd,"文件未保存，是否保存","提示",MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
                    if(id == IDYES){
                        int rt = SaveFile();
                        if(rt == -1){
                            AssertE("无法保存文件！",hwnd);
                        }else if(!rt){
                            SetWindowText(hwnd,"CASM");
                            fileSaved = true;
                        }else if(rt == -2){
                            break;
                        }
                        //printf("已保存");
                    }
                }
                SetWindowText(textBox,saying);
                break:*/
            case mVer:
                DialogBox(mins,MAKEINTRESOURCE(IDI_DLG_VER),hwnd,VerProc);
                SetFocus(hwnd);
                break;
            case mSelAll:
                SendDlgItemMessage(hwnd,ID_TEXTBOX,EM_SETSEL,0,-1);
                break;
            case mSave:
                int rt = SaveFile();
                if(rt == -1){
                    AssertE("无法保存文件！",hwnd);
                }else if(!rt){
                    SetWindowText(hwnd,"CASM");
                    fileSaved = true;
                }
                //printf("已保存");
                break;
            }
            if(fileSaved){
                switch(HIWORD(wParam)){
                case EN_CHANGE:
                    fileSaved = false;
                    SetWindowText(hwnd,"CASM *(未保存)");
                    break;
                }
            }
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

int NewFile(){
    BROWSEINFO bi;
    LPITEMIDLIST idl;
    int rt = -1;
    TCHAR tmp[MAX_PATH] = {0},tmp2[MAX_PATH] = {0};
    ZeroMemory(filePath,sizeof(TCHAR) * MAX_PATH);
    ZeroMemory(fileDirectory,sizeof(TCHAR) * MAX_PATH);
    ZeroMemory(&bi,sizeof(BROWSEINFO));
    bi.hwndOwner = hwnd;
    bi.pszDisplayName = tmp;
    bi.lpszTitle = _T("从下面选文件夹目录:");
    bi.ulFlags = BIF_RETURNFSANCESTORS;
    idl = SHBrowseForFolder(&bi);
    if (!idl){
        //printf("未选择文件!");
        return rt;
    }
    SHGetPathFromIDList(idl,tmp);
    if(DialogBox(mins,MAKEINTRESOURCE(IDI_DLG_CHOSEN),hwnd,DlgNewproc) == DLG_OK){
        rt = 0;
        strcpy(fileDirectory,tmp);
        sprintf(tmp2,"%s\\%s",tmp,filePath);
        strcpy(filePath,tmp2);
        fBufferI = NULL;
        fBufferI = fopen(filePath,"r");
        if(fBufferI){
            int r = Q("文件已存在，是否覆盖?",hwnd);
            if(r == IDNO){
                fclose(fBufferI);
                fBufferI = NULL;
                SetFocus(hwnd);
                return -1;
            }
            fclose(fBufferI);
        }
        fBufferI = NULL;
        fBufferI = fopen(filePath,"w");
        if(!fBufferI){
            TCHAR txt[1024] = {0};
            TCHAR cst[1024] = {0};
            GetMeaning(errno,cst,1024 * sizeof(TCHAR));
            sprintf(txt,"文件写入失败!错误码:%d(%s)",errno,cst);
            AssertE(txt,hwnd);
            return -1;
        }
        fclose(fBufferI);
    }
    fclose(fBufferI);
    SetFocus(hwnd);
    return rt;
}


INT_PTR CALLBACK DlgNewproc(HWND h,UINT u,WPARAM w,LPARAM p){
    WChar pth[MAX_PATH] = {0};
    switch (u)
    {
        case WM_CLOSE:
        case WM_DESTROY:
            EndDialog(h,w);
            break;
        case WM_INITDIALOG:
            SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE) & ~WS_MAXIMIZEBOX &~WS_SIZEBOX);
            break;
        case WM_COMMAND:
            switch(LOWORD(w)){
            case DLG_OK:
                GetDlgItemText(h,DLG_CS_TXT,pth,MAX_PATH);
                strcpy(filePath,pth);
                EndDialog(h,w);
            }
            break;
        default:
            return DefWindowProc (h, u, w, p);
    }
    return 0;
}

