#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <thread>
#include <SFML/Audio.hpp>
#include <time.h>
#include "opencb.h"
#include "Generic.h"
#include "CClock.h"
#define CN "data/cn.txt"
#define EN "data/en.txt"
#define CON "data/config.cfg"
#define  IsKeyPressed(nVirtKey)     ((GetKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0)
#define  IsAKeyPressed(nVirtKey)     ((GetAsyncKeyState(nVirtKey) & (1<<(sizeof(SHORT)*8-1))) != 0)

using namespace std;
using namespace opencb::io;
using namespace opencb::base;
using namespace sf;

int sleept= 80;
HWND heart = NULL,gameWin = NULL;
sf::Music music;
#define GAME_WIN 2
#define GAME_OVER 1
#define GAME_CONT 0
int gameStatus = GAME_CONT;
struct Player{
    float x;
    float y;
    float w;
    float h;
    float hp;
    float maxHp;
    float shield;
    float maxShield;
    float speed;
};
struct Bullet{
    float x;
    float y;
    float w;
    float h;
    bool save {true};
    virtual void draw(){}
    virtual void flush(){}
    virtual ~Bullet(){}
};

struct Config{
    int lang;
    int deathTime;
};
Config config = {0,0};


unsigned int sysx,sysy;
string ts = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()~`_-+={}:\"<>?,./;\'\\|[]";
struct TextBullet : public Bullet{
    static HDC DC;
    string t;
    COLORREF co;
    void draw() override{
        COLORREF old = GetTextColor(DC);
        SetTextColor(DC,co);
        TextOut(DC,x,y,t.c_str(),t.size());
        SetTextColor(DC,old);
        y += sysy / 250;
        if(y > sysy+10)save = false;
    }
    void flush() override{
        t = "";
        t += ts[rand()%ts.size()];
        co = RGB(rand()%256,rand()%256,rand()%256);
    }
    TextBullet(){
        t = "";
        t += ts[rand()%ts.size()];
        x = rand()%(sysx-80)+80;
        y = 0;
        w = 8;
        h = 8;
    }
};
HDC TextBullet::DC = GetDC(NULL);

struct IconBullet : public Bullet{
    static HANDLE shell32;
    HICON thisIcon;
    float xcr,ycr;
    IconBullet(){
        if(rand()%100 >= 50){
            xcr = rand()%100 / 100.0 * 3;
            ycr = rand()%100 / 100.0 * 3;
            x = 60;
            y = 60;
        }else{
            xcr = -rand()%100 / 100.0 * 3;
            ycr = -rand()%100 / 100.0 * 3;
            x = sysx+20;
            y = sysy+20;
        }
        w = 32;
        h = 32;
    }
    void draw() override{
        DrawIconEx(TextBullet::DC,x,y,thisIcon,w,h,0,0,DI_NORMAL);
        x += xcr;
        y += ycr;
        if(x <= 40 || y <= 40 || x > sysx + 40 || y > sysy+40)save = false;
    }
    void flush() override{
        thisIcon = LoadIcon((HINSTANCE)shell32,MAKEINTRESOURCE(rand()%256));
    }
};
HANDLE IconBullet::shell32 = LoadLibrary("SHELL32.DLL");

vector<Bullet*> bullets;


Player pl = {0,0,20,20,100,100,100,100,1};
//extern bool solution2;

bool fnxx(int,int,vector<GString>&){
    Sleep(sleept);
    return false;
}

bool fndd(int,int,vector<GString>&){
    Sleep(sleept/2);
    return false;
}

bool fnss(int,int,vector<GString>&){
    Sleep(sleept);
    music.setPlayingOffset(music.getPlayingOffset() - sf::milliseconds(sleept + 5));
    return false;
}

GString operator +(vector<GString> d,int v){
    if(v < 0 || v >= (int)d.size())return Str("");
    return d[v];
}
vector<GString> subvec(vector<GString> d,int st,int ed){
    vector<GString> ret;
    for(int i = st;i <= ed;++i){
        ret.push_back(d + i);
    }
    return ret;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_COMMAND:
            if(wParam == 1){
                PostQuitMessage(0);
            }
            break;
        case WM_DESTROY:
            break;
        case WM_CLOSE:
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

struct RectX{
    float x,y,w,h;
};
bool test_collision__2(RectX rect1, RectX rect2){
    int x1_1 = rect1.x;
    int y1_1 = rect1.y;
    int x1_2 = rect1.x + rect1.w;
    int y1_2 = rect1.y;
    int x1_3 = rect1.x;
    int y1_3 = rect1.y + rect1.h;
    int x1_4 = rect1.x + rect1.w;
     int y1_4 = rect1.y + rect1.h;



     int x2_1 = rect2.x;
     int y2_1 = rect2.y;
     int x2_2 = rect2.x + rect2.w;
     int y2_2 = rect2.y;
     int x2_3 = rect2.x;
     int y2_3 = rect2.y + rect2.h;
     int x2_4 = rect2.x + rect2.w;
     int y2_4 = rect2.y + rect2.h;

     // �жϾ���һ���ĸ�����֮һ�Ƿ��ھ��ζ���
    if( (x1_1 > x2_1 && x1_1 < x2_4) && (y1_1 > y2_1 && y1_1 < y2_4) )
     {
         return true;
     }

     if( (x1_2 > x2_1 && x1_2 < x2_4) && (y1_2 > y2_1 && y1_2 < y2_4) )
     {
         return true;
     }

     if( (x1_3 > x2_1 && x1_3 < x2_4) && (y1_3 > y2_1 && y1_3 < y2_4) )
     {
         return true;
     }

     if( (x1_4 > x2_1 && x1_4 < x2_4) && (y1_4 > y2_1 && y1_4 < y2_4) )
     {
         return true;
     }

     // �жϾ��ζ����ĸ�����֮һ�Ƿ��ھ���һ��
     if( (x2_1 > x1_1 && x2_1 < x1_4) && (y2_1 > y1_1 && y2_1 < y1_4) )
     {
         return true;
     }
    if( (x2_2 > x1_1 && x2_2 < x1_4) && (y2_2 > y1_1 && y2_2 < y1_4) )
    {
       return true;
    }

     if( (x2_3 > x1_1 && x2_3 < x1_4) && (y2_3 > y1_1 && y2_3 < y1_4) )
     {
         return true;
     }

     if( (x2_4 > x1_1 && x2_4 < x1_4) && (y2_4 > y1_1 && y2_4 < y1_4) )
     {
         return true;
     }

     return false;
}
void full_screen(HWND hwnd){
    int cx = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

    LONG l_WinStyle = GetWindowLong(hwnd,GWL_STYLE);   /* ��ȡ������Ϣ */
    /* ���ô�����Ϣ ��� ȡ�����������߿� */
    SetWindowLong(hwnd,GWL_STYLE,(l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, cx, cy, 0);
}
vector<GString> strings;

#define INIT_CMD "cls & color 0f & mode con cols=128 lines=32"

void CreateASyncPopups(int c,int id,string text,vector<string> & names,vector<thread*> threads,UINT flags){
    auto f = [&](string id,string text){MessageBox(NULL,text.c_str(),id.c_str(),flags);};
    for(int i = 0;i < c;++i){
        string name = "AsyncPopup"+ to_string(id) + to_string(i);
        std::thread * t = new std::thread(f,name,text);
        t->detach();
        threads.push_back(t);
    }
}

void DestroyAsyncPopup(vector<string> & names,vector<thread*> threads){
    for(string & s : names){
        HWND win = FindWindow(NULL,s.c_str());
        if(win){
            PostMessage(win,WM_CLOSE,0,0);
        }
    }
    for(std::thread* t : threads){
        delete t;
    }
}

void WithARanPos(vector<string> & names){
    for(string & s : names){
        HWND win = FindWindow(NULL,s.c_str());
        if(win){
            RECT rect;
            GetWindowRect(win,&rect);
            SetWindowPos(win,0,rand()%sysx,rand()%sysy,rect.right - rect.left,rect.bottom - rect.top,0);
        }
    }
}

void Disable(){
    //���ÿ���̨�����ñ༭
    auto hStdin = ::GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hStdin, mode);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&ci);
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&ci);
}
void * game(void *){
    int stageMSec[] = {60000,90000};
    int stageCounter = 0,initChecker = -1;
    cck::Clock clk,tw,click,stage;
    clk.GetOffset();
    tw.GetOffset();
    click.GetOffset();
    stage.GetOffset();
    string show;
    unsigned int tick = 0;
    LONG l_WinStyle = GetWindowLong(gameWin,GWL_STYLE);
    while(true){
        if(stage.Now().offset >= stageMSec[stageCounter]){
            stageCounter++;//��һ�׶�
        }
        if(initChecker != stageCounter){
            initChecker = stageCounter;
            clk.Pause();
            tw.Pause();
            click.Pause();
            stage.Pause();
            switch(stageCounter){
            case 0:
                break;
            case 1:
                music.stop();
                ShowWindow(gameWin,SW_SHOW);
                ShowWindow(heart,SW_HIDE);
                full_screen(gameWin);
                SetWindowPos(gameWin, HWND_TOP, 0, 0, sysx, sysy, 0);
                Disable();
                SetColor(CL_RED);
                EasyDelay(strings + 45,10);
                if(pl.hp > 100){
                    EasyDelay(strings + 49,10);
                    exit(0x114514);
                }else if(pl.hp == 100){
                    EasyDelay(strings + 50,10);
                }else if(pl.hp < 100 && pl.hp >= 80){
                    EasyDelay(strings + 46,10);
                }else if(pl.hp < 80 && pl.hp >= 40){
                    EasyDelay(strings + 47,10);
                }else if(pl.hp < 40){
                    EasyDelay(strings + 48,10);
                }
                EasyDelay(strings + 51,10);
                SetColor();
                Sleep(1000);
                ShowWindow(heart,SW_SHOW);
                ShowWindow(gameWin,SW_SHOW);
                SetWindowLong(gameWin,GWL_STYLE,l_WinStyle);
                system(INIT_CMD);
                /*{
                    vector<string> names;
                    vector<thread*> ts;
                    CreateASyncPopups(32,114514,"Fatal Errror!!!",names,ts,MB_OK | MB_ICONERROR | MB_TOPMOST);
                    WithARanPos(names);
                    Sleep(3200);
                    DestroyAsyncPopup(names,ts);
                }*/
                MessageBox(NULL,"Thanks for playing,this game is still being developing by aaaaa0ggmc(RokonDreaming)..","Not a Fatal Error",MB_OK);
                gameStatus = GAME_WIN;
                break;
            default:
                EasyDelay(strings + 44,10);
                exit(-114514);
            }
            clk.Resume();
            tw.Resume();
            click.Resume();
            stage.Resume();
        }
        if(click.Now().offset >= 10){
            click.GetOffset();
            if(IsAKeyPressed(VK_ESCAPE)){
                break;
            }else if(IsAKeyPressed('W')){
                if(pl.y - sysy/200 * pl.speed > 80){
                    pl.y -= sysy/200 * pl.speed;
                    SetWindowPos(heart,HWND_TOPMOST,(int)pl.x,(int)pl.y,(int)pl.w,(int)pl.h,0);
                }
            }else if(IsAKeyPressed('A')){
                if(pl.x - sysy/200 * pl.speed > 80){
                    pl.x -= sysy/200 * pl.speed;
                    SetWindowPos(heart,HWND_TOPMOST,(int)pl.x,(int)pl.y,(int)pl.w,(int)pl.h,0);
                }
            }else if(IsAKeyPressed('S')){
                if(pl.y + sysy/200 * pl.speed < sysy-pl.h){
                    pl.y += sysy/200 * pl.speed;
                    SetWindowPos(heart,HWND_TOPMOST,(int)pl.x,(int)pl.y,(int)pl.w,(int)pl.h,0);
                }
            }else if(IsAKeyPressed('D')){
                if(pl.x + sysy/200 * pl.speed < sysx-pl.w){
                    pl.x += sysy/200 * pl.speed;
                    SetWindowPos(heart,HWND_TOPMOST,(int)pl.x,(int)pl.y,(int)pl.w,(int)pl.h,0);
                }
            }
        }
        if(clk.Now().offset >= 10){
            clk.GetOffset();
            {
                vector<Bullet*> tmp;
                for(Bullet* b : bullets){
                    b->draw();
                    if(test_collision__2({b->x,b->y,b->w,b->h},{pl.x,pl.y,pl.w,pl.h})){
                        pl.hp --;
                    }
                    if(b->save)tmp.push_back(b);
                    else delete b;
                }
                bullets = tmp;
            }
        }
        if(tw.Now().offset >= 100){
            tw.GetOffset();
            ++tick;
            bullets.push_back(new TextBullet());
            if(tick % 4 == 0){
                bullets.push_back(new IconBullet());
            }
            for(Bullet* b : bullets){
                b->flush();
            }
        }
        if(gameStatus == GAME_WIN)break;
        if(pl.hp <= 0){
            config.deathTime ++;
            gameStatus = GAME_OVER;
            break;
        }
        show = "HP:";
        show += to_string((int)pl.hp) + "/" + to_string((int)pl.maxHp);
        TextOut(TextBullet::DC,pl.x - 16,pl.y - 16,show.c_str(),show.size());

    }
    if(gameStatus == GAME_OVER){
        music.stop();
        if(!music.openFromFile("data/gameover.ogg")){
            MessageBox(NULL,"Can not find music data/gameover.ogg!","Fatal Error",MB_TOPMOST | MB_OK | MB_ICONERROR);
            exit(-1);
        }
        music.play();
        ShowWindow(gameWin,SW_SHOW);
        ShowWindow(heart,SW_HIDE);
        full_screen(gameWin);
        SetWindowPos(gameWin, HWND_TOP, 0, 0, sysx, sysy, 0);
        Disable();
        EasyPrint(subvec(strings,25,26),fnxx);
        clrscr();
        SetColor(CL_YELLOW);
        sleept = 120;
        EasyPrint(subvec(strings,27,27),fnss,fnss);
        SetColor();
        Sleep(1000);
        ///Generate Error Code
        clrscr();
        vector<GString> tmp;
        GString code = Str("");
        for(int i = 0;i < 128;++i){
            code = Str("");
            for(int j = 0;j < 256;++j){
                code += (gchar)(ts[rand()%ts.size()]);
            }
            tmp.push_back(code);
        }
        system("color f0");
        music.setPitch(0.6);
        for(GString& str : tmp){
            sout << str;
            Sleep(1);
        }
    }
    ShowWindow(gameWin,SW_SHOW);
    PostMessage(heart,WM_COMMAND,1,0);
    return NULL;
}

TCHAR className[] = TEXT("Errtale_Wnd_Class");

int main()
{
    //����α�����
    srand(time(0));
    system(INIT_CMD);
    gameWin = GetConsoleWindow();
    SetWindowText(gameWin,"Errtale");
    {
        WNDCLASSEX wincl;        /* Data structure for the windowclass */

        /* The Window structure */
        wincl.hInstance = GetModuleHandle(NULL);
        wincl.lpszClassName = className;
        wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
        wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
        wincl.cbSize = sizeof (WNDCLASSEX);

        /* Use default icon and mouse-pointer */
        wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
        wincl.lpszMenuName = NULL;                 /* No menu */
        wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
        wincl.cbWndExtra = 0;                      /* structure or the window instance */
        /* Use Windows's default colour as the background of the window */
        wincl.hbrBackground = CreateSolidBrush(RGB(255,0,0));

        /* Register the window class, and if it fails quit the program */
        if (!RegisterClassEx (&wincl)){
            MessageBox(gameWin,"Can not register class!","Fatal Error",MB_OK | MB_ICONERROR);
            exit(-1);
        }
    }
    //Disable Console Controlls
    Disable();
    {
        sysx = GetSystemMetrics(SM_CXSCREEN);
        sysy = GetSystemMetrics(SM_CYSCREEN);
        pl.x = sysx/2;
        pl.y = sysy/2;
    }
    //Read config
    {
        int & lang = config.lang;
        gifstream ifs(CON);
        if(ifs.good() && !ifs.eof()){
            ifs >> lang;
            ifs >> config.deathTime;
            ifs.close();
            if(lang == 1)ifs.open(CN);
            else ifs.open(EN);
        }else{
            ifs.close();
            //Choose a language
            while(true){
                bool good = true;
                cout << "Please Select The Language ��ѡ�����ԣ�" << endl << "1.Simpled Chinese ��������" << endl << "2.English Ӣ��" << endl;
                char c = _getch();
                if(c == '1'){
                    ifs.open(CN);
                    if(!ifs.good()){
                        cout << "Can't load file " CN << "  �޷������ļ� " << CN <<endl;
                        good = false;
                    }
                    lang = 1;
                }else if(c == '2'){
                    ifs.open(EN);
                    if(!ifs.good()){
                        cout << "Can't load file " EN << "  �޷������ļ� " << EN <<endl;
                        good = false;
                    }
                    lang = 2;
                }else good = false;
                if(good){
                    break;
                }
                clrscr();
            }
            clrscr();
        }
        //if(lang != 2)solution2 = true;
        GString l;
        while(!ifs.eof()){
            getline(ifs,l);
            strings.push_back(l);
        }
    }
    music.setLoop(true);
    if(!music.openFromFile("data/OnceUponATime.ogg")){
        MessageBox(gameWin,"Game music OnceUponATime.ogg has lost","Fatal Error",MB_OK | MB_ICONERROR);
        exit(-1);
    }
    SetWindowLong(gameWin,GWL_STYLE,GetWindowLong(gameWin,GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    Sleep(1000);
    if(IsKeyPressed(VK_SHIFT) != TRUE){
        if(config.deathTime == 0){
            sleept = 5;
            clrscr();
            SwapPrint(subvec(strings,0,10),fnxx);
            Sleep(1000);
            clrscr();
            music.play();
            sleept = 200;
            EasyPrint(subvec(strings,11,19),fndd,fnxx);
            Sleep(4500);
            clrscr();
            SetColor(CL_RED);
            sleept = 40;
            EasyPrint(subvec(strings,20,23),fnss,fnxx);
            Sleep(800);
            clrscr();
            SetColor();
            music.stop();
        }else if(config.deathTime < 0){
            config.deathTime = 999999999;
            SetColor(CL_RED);
            EasyDelay(strings + 28,30);
            cout << endl;
            EasyDelay(strings + 29,30);
            SetColor();
            Sleep(400);
            clrscr();
        }else if(config.deathTime >= 99999999){
            SetColor(CL_RED);
            EasyDelay(strings + 30,30);
            cout << endl;
            EasyDelay(strings + 31,30);
            SetColor();
            Sleep(400);
            clrscr();
        }else if(config.deathTime <= 6){
            int & offset = config.deathTime;
            SetColor(CL_RED);
            EasyDelay(strings + (30+offset*2),30);
            cout << endl;
            EasyDelay(strings + (30+offset*2+1),30);
            SetColor();
            Sleep(400);
            clrscr();
        }
    }
    sleept = 50;
    EasyPrint(subvec(strings,24,24),fnxx);
    Sleep(100);
    system("cls");
    ShowWindow(gameWin,SW_HIDE);
    if(!music.openFromFile("data/Sans.ogg")){
        MessageBox(gameWin,"Game music Sans.ogg has lost","Fatal Error",MB_OK | MB_ICONERROR);
        exit(-1);
    }
    music.play();
    ///��Ϸ����
    heart = CreateWindowEx(0,className,"YourHeart",WS_POPUP,pl.x,pl.y,pl.w,pl.h,NULL,NULL,GetModuleHandle(NULL),NULL);
    //�����߳���Ӧ��Ϣ
    pthread_t gameT = 0;
    pthread_create(&gameT,NULL,game,NULL);
    pthread_detach(gameT);
    ShowWindow(heart,SW_SHOW);
    {
        MSG messages;            /* Here messages to the application are saved */
        /* Run the message loop. It will run until GetMessage() returns 0 */
        while (GetMessage(&messages, NULL, 0, 0))
        {
            if(gameStatus != GAME_CONT)break;
            /* Translate virtual-key messages into character messages */
            TranslateMessage(&messages);
            /* Send message to WindowProcedure */
            DispatchMessage(&messages);
        }
        SwitchToThisWindow(gameWin,TRUE);
        exit(0);
        //TerminateProcess(GetModuleHandle(NULL),0);
    }
}


struct ResourceLock{
    ~ResourceLock(){
        for(Bullet * b : bullets)delete b;
        gofstream ofs(CON);
        ofs << config.lang << endl << config.deathTime;
        ofs.close();
        FreeLibrary((HMODULE)IconBullet::shell32);
    }
};
ResourceLock resourceLock;
