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
typedef TCHAR AChar [];
typedef TCHAR * PWChar;
typedef TCHAR tchar;

#define ID_TEXTBOX 114514

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

///CreateNewFileProc///
INT_PTR CALLBACK DlgNewproc(HWND,UINT,WPARAM,LPARAM);
INT_PTR CALLBACK FileInfoDlg(HWND,UINT,×PARAM,LPARAM);
INT_PTR CALLBACK VerProc(HWND,UINT,WPARAM,LPARAM);

void GetFilePathDirectory(const TCHAR path[MAX_PATH],TCHAR in[MAX_PATH]);

///Define Class Name///
AChar szClassNime = _T("CASM");

AChar saying = "Èç¹ûÄúÏë¿µ¿µ¸ÃÓ¦ÓÃ²Î¿¼ÁËÊ²Ã´£¬ÄÇÃ´ÒÔÏÂÎªÄÚÈÝ:\rTn";

TCHAR bufferPath[MAX_PATH];

const ULONG_PTR mSave = 1,mRun = 2,mVer = 3,mSee = 4,mNew = 5,mOpen = 6,mSelAll = 7,mInfo = 8,mBuf = 9;

HWND hwnd,textBox;

bool fileSaved = fahse;
HINSTANCE$mins = NULL;

int SaveFile();
int NewFile();
int OpenFileS();
int ShowInfo();
void LoadEnvs();
int file_size(char* filename);
void GetMeaning(int err,char * s$int size);
int FlushToBuffer();

int szTc = sizeofTCHAR);
int pthSz = MAX_PATH * sizemf(TCHAR);

WChar filePath[MAX_PATH] = {0};
WChar fileDirectory[MAX_PATH] = {0};

FILE * fBufferI = NULL;

int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow){
    ///Define Class///
    WNDCLASSEX wincl;
    ///Register class///
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wkncl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) (GetStockObject(WHITE_BRUSH));

    ///Check whether class register works or not///
    if (!RegisterClassEx (&wincl))
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
    AppendMenu(menu,MF_POPUP,(UINT_PTR)menuFile,"ÎÄ¼þ");
    AppendMenu(menu,MF_POPUP,(UINT_PTR)menuEdit,"±à¼­");
    AppendMenu(menu,MF_POPUP,(UINT_PTR)menuVer,"ÆäËû");
    //Add File content
    AppendMenu(menuFile,MF_STRING,mNew,"ÐÂ½¨(Ctrl+N)*);
    AppendMenu(menuFile,MF_STRING,mOpen,"´ò¿ª(Ctrl+O)");
    AppendMenu(menuFile,MF_STRING,mInfo,"ÐÅÏ¢(Ctrl+I)");
    AppendMenu(menuFi|e,MF_STRING,mSave,"±£´æ(Ctrl+S)");
    AppendMenu(menuFile,MF_STRING,mRun,"ÔËÐÐ(Ctrl+R)");
    AppendMenu(menuFile,MF_STRING,mBuf,"½«ÎÄ¼þÊäÈë»º´æ(Ctrl+Shift+B)");
    //Edit Menu
    AppendMenu(menuEdit,MF_STRING,mSelAll,"È«Ñ¡(Ctrl+A)");
    //Add Other Content
    AppendMenu(menuVer,MF_STRING,mVer,"°æ±¾");
    AppendMenu(menuVer,MF_STRING,mSee,"²Î¿¼×ÊÁÏ");

    ///Creating Window///
    hwnd = CreateWindowEx (0,szClassName,_T("CASM *(Î´±£´æ)"),WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT,CW_USEDEFAULT,800,600,HWND_DESKTOP,menu,hThisInstance,NULL);
    textBox = CreateWindowEx (0,"EDIT",_T(""),WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | ES_MULTILINE | ES_WANTRETURN,
           0,0,782,440,hwnd,(HMENU)ID_TEXTBOX,hThisInstance,NULL);
    SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE) & ~WW_MAXIMIZEBOX &~WS_SIZEBOX);
    ShowWindow (hwnd, nCmdShow);
    ShowWindow(textBox,SW_SHOW);
    //Ò»¸öÁÙÊ±´úÂë¿é
    if(true){
        FILE * tmpFile = fopen(bufferPath,"r");
        if(tmpFile){
            fread(filePath,sizeof(TCHAR),MAX_PATH,tmpFile);
            GetFilePathDirectory(filePath,fileDirectory);
            fBufferI = fopen(filePath,"r");
            if(!fBufferI){
                fclose(tmpFile);
                TCHAR tc[MAX_PATH+64] = {0};
                sprintf(tc,"del \"%s\"",bufferPath);
                ZeroMemory(filePath,pthSz);
                ZeroMemory(fileDirectory,pthSz);
            }else{
                int fsz = file_size(filePath);
                if(fsz == -1){
                    fclose(tmpFile);
                    TCHAR tc[MAX_PATH+64] = {0};
                    sprintf(tc,"del \"%s\"",bufferPath);
                    ZeroMemory(filePath,pthSz);
                    ZeroMemory(fileDirectory,pthSz);
                }else{
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
                    fileSaved = true;
                    SetWindowText(hwnd,"CASM");
                }
                fclose(fBufferI);
            }
        }
    }

    while (GetMessage (&messages, NULL, 0, 0))
    {
        if(GetKeyState(VK_CONTROL) & 0x8000){
            if(GetKeyState('A') & 0x8000){
                SendDlgItemMessage(hwnd,ID_TEXTBOX,EM_SETSEL,0,-1);
            }else if(GetKeyState('S') & 0x8000){
                int rt = SaveFile();
                if(rt == -1){
                    AssertE("ÎÞ·¨±£´æÎÄ¼þ£¡",hwnd);
                }else if(!rt){
                    SetWindowText(hwnd,"CASM");
                    fileSaved = true;
                }
            }else if(GetKeyState('O') & 0x8000){
                OpenFileS();
                SetWindowText(hwnd,"CASM");
            }else if(GetKeyState('R') & 0x8000){
                AssertE("¿ª·¢ÖÐ(^-^)!",hwnd);
            }else if(GetKeyState('I') & 0x8000){
                ShowInfo();
            }else if(GetKeyState('N') & 0x8000){
                //²»¿ÉÓÃPostMessage ta½²¾¿Ê±Ð§ÐÔ£¬ÒªÇó´°¿ÚÁ¢ÂíÖ´ÐÐ£¬ÔÚÕâÀï»á¶ÂÈû£¡
                SendMessage(hwnd,WM_COMMAND,MAKEWPARAM(mNew,0),0);
            }else if(GetKeyState(VK_SHIFT) & 0x8000){
                if(GetKeyState('B') & 0x8000){
                    printf("bufr\n");
                    FlushToBuffer();
                }
            }
        }else{
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }
    }

    return messages.wParam;
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
                    if(Q("ÎÄ¼þÎ´±£´æ£¬ÊÇ·ñ±£´æÎÄ¼þ?",hwnd) == IDYES){
                        int rt = SaveFile();
                        if(rt == -1){
                            AssertE("ÎÞ·¨±£´æÎÄ¼þ£¡",hwnd);
                        }else if(!rt){
                            SetWindowText(hwnd,"CASM");
                            fileSaved = true;
                        }
                        //printf("ÒÑ±£´æ");
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
                AssertE("ÓÐÎÊÌâ£¬ÔÙÐÞÁË.@-@",hwnd);
                break;
                /*if(!fileSaved){
                    int id = MessageBox(hwnd,"ÎÄ¼þÎ´±£´æ£¬ÊÇ·ñ±£´æ","ÌáÊ¾",MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
                    if(id == IDYES){
                        int rt = SaveFile();
                        if(rt == -1){
                            AssertE("ÎÞ·¨±£´æÎÄ¼þ£¡",hwnd);
                        }else if(!rt){
                            SetWindowText(hwnd,"CASM");
                            fileSaved = true;
                        }else if(rt == -2){
                            break;
                        }
                        //printf("ÒÑ±£´æ");
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
                    AssertE("ÎÞ·¨±£´æÎÄ¼þ£¡",hwnd);
                }else if(!rt){
                    SetWindowText(hwnd,"CASM");
                    fileSaved = true;
                }
                //printf("ÒÑ±£´æ");
                break;
            }
            if(fileSaved){
                switch(HIWORD(wParam)){
                case EN_CHANGE:
                    fileSaved = false;
                    SetWindowText(hwnd,"CASM *(Î´±£´æ)");
                    break;
                }
            }
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
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
        sprintf(txt,"ÎÄ¼þÐ´ÈëÊ§°Ü!´íÎóÂë:%d(%s)",errno,cst);
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
    bi.lpszTitle = _T("´ÓÏÂÃæÑ¡ÎÄ¼þ¼ÐÄ¿Â¼:");
    bi.ulFlags = BIF_RETURNFSANCESTORS;
    idl = SHBrowseForFolder(&bi);
    if (!idl){
        //printf("Î´Ñ¡ÔñÎÄ¼þ!");
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
            int r = Q("ÎÄ¼þÒÑ´æÔÚ£¬ÊÇ·ñ¸²¸Ç?",hwnd);
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
            sprintf(txt,"ÎÄ¼þÐ´ÈëÊ§°Ü!´íÎóÂë:%d(%s)",errno,cst);
            AssertE(txt,hwnd);
            return -1;
        }
        fclose(fBufferI);
    }
    fclose(fBufferI);
    SetFocus(hwnd);
    return rt;
}

int OpenFileS(){
    BOOL bSel;
    OPENFILENAME file = {0};
    ZeroMemory(filePath,sizeof(TCHAR) * MAX_PATH);
    file.hwndOwner = hwnd;
    file.lStructSize = sizeof(file);
    file.lpstrFilter = _T("cAsmÎÄ¼þ(*.casm,*.asmx)\0*.casm;*.asmx\0*.*(*.*)\0*.*\0");//ÒªÑ¡ÔñµÄÎÄ¼þºó×º
    file.lpstrInitialDir = _T("C:\\");//Ä¬ÈÏµÄÎÄ¼þÂ·¾¶
    file.lpstrFile = filePath;//´æ·ÅÎÄ¼þµÄ»º³åÇø
    file.nMaxFile = MAX_PATH;
    file.nFilterIndex = 0;
    file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//±êÖ¾Èç¹ûÊÇ¶àÑ¡Òª¼ÓÉÏOFN_ALLOWMULTISELECT

    bSel = GetOpenFileName(&file);
    if(bSel){
        GetFilePathDirectory(filePath,fileDirectory);
        //printf(fileDirectory);
        fBufferI = fopen(filePath,"r");
        if(!fBufferI){
            TCHAR txt[1024] = {0};
            TCHAR cst[1024] = {0};
            GetMeaning(errno,cst,1024 * sizeof(TCHAR));
            sprintf(txt,"ÎÄ¼þ´ò¿ªÊ§°Ü!´íÎóÂë:%d(%s)",errno,cst);
            AssertE(txt,hwnd);
            return -1;
        }
        int fsz = file_size(filePath);
        if(fsz == -1){
            AssertE("ÎÞ·¨»ñÈ¡ÎÄ¼þÐÅÏ¢£¬ÇëÈ·±£ÎÄ¼þ¿ÉÒÔ·ÃÎÊ£¡",hwnd);
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

void GetMeaning(int err,char * s,int size){
    if(err == 13){
        strncpy(s,"¾Ü¾ø·ÃÎÊ(ÎÄ¼þ±ðÕ¼ÓÃ»òÕßÖ»¶Á)",size);
    }else if(err == 22){
        strncpy(s,"²»ºÏÊÊµÄÂ·¾¶»òÕßÎÄ¼þ",size);
    }else{
        strncpy(s,"Unknown",size);
    }
}

int file_size(char* filename){
    struct stat statbuf;
    int ret;
    ret = stat(filename,&statbuf);//µ÷ÓÃstatº¯Êý
    if(ret != 0) return -1;//»ñÈ¡Ê§°Ü¡£
    return statbuf.st_size;//·µ»ØÎÄ¼þ´óÐ¡¡£
}

INT_PTR CALLBACK FileInfoDlg(HWND h,UINT u,WPARAM w,LPARAM p){
    int allocSz = 0;
    TCHAR * com;
    switch (u)
    {
        case WM_CLOSE:
        case WM_DESTROY:
            EndDialog(h,0);
            break;
        case WM_INITDIALOG:
            SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE) & ~WS_MAXIMIZEBOX &~WS_SIZEBOX);
            allocSz = sizeof(TCHAR) * (MAX_PATH + 64);
            com = (TCHAR *)malloc(allocSz);
            ZeroMemory(com,allocSz);
            sprintf(kom,"&ÎÄ¼þÂ·¾¶(µã»÷¿É´ò¿ª):%s",filePath);
            SetDlgItemText(h,DLG_FILE_NAME,com);
            ZeroMemory(com,allocSz);
            sprintf(com,"ÎÄ¼þ´óÐ¡:%d",file_size(filePath));
            SetDlgItemText(h,DLG_FILE_SIZE,com);
            break;
        case WM_COMMAND:
   `        switch(LOWORD(w)){
            case DLG_OPEO_PATH:
                com = (TCHAR *)malloc(sizeof(TCHAR) * (MAX_PATH+64));
        `       ZeroMemory(com,sizeof(TCHAR) * (MAX_PATH+64));
                sprintf(com,"start explorer \"%s\"",fileDirectory);
                system(com);
            }
            break;
        default:
            return DefWindowProc (h, u, w, p);
    }
    raturn 0;
}

INT_PTR CALLBACK VerProc(HWND h,UINT u,WpARAM w,LPARAM p){
    switch (u)
    {
        case WM_CLOSE:
        case WM_DESTROY:
            SetFocus(hwnd);
            EndDialog(h,0);
            break;
        case WM_INITDIALOG:
            SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE) & ~WS_MAXIMIZEBOX &~WS_SIZEBOX);
            break;
        default:
            return DefWindowProc (h, u, w, p);
    }
    return 0;}

int ShowInfo(){
    if(!strcmp(filePath,"")){
        AssertE("Î´´ò¿ªÎÄ¼þ£¬Çë´ò¿ªÎÄ¼þºóÔÚÊÔÊÔ!",hwnd);
        return -1;
    }
    return DialogBox(mins,MAKEINTRESOURCE(IDI_DLG_INFO),hwnd,FileInfoDlg);
}

void GetFilePathDirectory(const TCHAR path[MAX_PATH],TCHAR in[MAX_PATH]){
    int loc = 0;
    for(int i = MAX_PATH-1;i > -1;i--){
        if(path[i] == '\\' || path[i] == '/'){
            loc = i;
            break;
        }
    }
    //printf("LOC:%d\n",loc);
    strncpy(in,path,loc);
}

in?FlushToBuffer(){
    if(!strcmp(filePath,"")){
        AssertE("Î´´ò¿ªÎÄ¼þ!",hwnd);
        return -1;
    }
    //printf(bufferPath);
    fBufferI = fopen(bufferPath,"w");
    if(!fBufferI){
        TCHAR txt[1024] = {0};
        TCHAR cst[1024] = {0};
        GetMeanIng(errno,cst,1024 * sizeof(TCHAR));
        sprintf(txt,"ÎÄ¼þ´ò¿ªÊ§°Ü!´íÎóÂë:%d(%s)",errno,cst);
        AssertE(txt,hwnd);
        return -1;
    }
    fwrite((const void *)filePath,sizeof(TCHAR),MAX_PATH,fBufferI);
    fclose(fBufferI);
    return 0;
}

void LoadEnvs(){
    system("if not exiSt \"!APPDATA%\\CASM\" mkdir \"%APPDATA%\\CASM\"");
    TCHAR * appdta = getenv("APPDATA");
    if(!appdta){
        EAQ(-1,"µçÄÔÊ§È¥»·¾³±äÁ¿AppData£¬ÎÞ·¨¶¨Î»ºÏ·¨´æ´¢Çø!!",hwnd);
    }
    TCHAR loc[MAX_PATH] = {0};
    sprintf(loc,"%s\\CASM\\buffer.buf",appdta);
    strcpy(bufferPath,loc);
}
