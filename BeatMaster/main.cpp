#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include "main.hpp"
#include "Ball.hpp"

using namespace std;

///窗口的宽///
#define Width 700
///窗口的高///
#define Height 600

//导入变量
extern const char inputs_show[BallNum];
extern const TCHAR * media_paths[BallNum];

///方便折叠代码时注释一下///
#define Block(x)

///导入winmm库以使用mciXXX///
#pragma comment(lib,"winmm.lib")

#define OneDragon(X) score++;BallNum[(X)] = GenerateNewBall(&BallNum[(X)],VeclocityMovement,PositionMovement);

///分数///
int score = 0;

///游戏状态///
///0:初始彩蛋///
///1:正常游戏///
///2:退出///
///3.暂停///
int gameStatus = 0;

///小球的半径///
int radius = 15;

///用户的输入///
char input = '\0';

int i = 0;

Ball balls[BallNum] = {
	{100,0,2},
	{300,0,1},
	{500,0,3},
	{200,0,4},
	{400,0,6},
	{600,0,5}
};

///主函数///
int main(void){
	startup();  // 数据初始化
    while (1){
        show();  // 显示画面
        updateWithoutInput();  // 与用户输入无关的更新
        updateWithInput();     // 与用户输入有关的更新
    }
    gameover();     // 游戏结束、后续处理
    return 0;
}

///方便折叠代码，对游戏运行毫无影响///
#if 1 //这里实现main.h的内容

///速度的变化，自己计算///
float VeclocityMovement(float in){
	return in + 1;
}

///位置的变化，自己计算///
Position PositionMovement(float x,float y){
	Position ps = {0,0};
	ps.x = (float)(rand() % Width);
	ps.y = 0;//从顶端生出
	return ps;
}

///初始菜单界面///
void startMenu(){
	///设置背景色为蓝色///
    setbkcolor(RGB(80,130,190));
	///用背景色清空屏幕///
    cleardevice();
	///设置输出字体颜色为透明///
    setbkmode(TRANSPARENT);
	///设置输出字体颜色为黑色///
    settextcolor(BLACK);
    settextstyle(50,0,_T("黑体"));
    outtextxy(233,120,_T("1 新游戏"));
    outtextxy(233,180,_T("2 读取游戏存档"));
    outtextxy(233,240,_T("3 退出"));
    FlushBatchDraw();
	Sleep(2);
	///判断是否有输入///
    if(_kbhit()){
		///根据用户的不同输入来移动，不必输入回车///
        input = _getch(); 
        if (input == '1')gameStatus = 1;
        else if (input == '2'){
            readRecordFile();
            gameStatus = 1;
        }
        else if (input == '3'){
			//这个代码不会走到gameover函数，这是你自己的原因，别赖我，其他的也一样，只不过我帮你改了
            gameStatus = 2;
            gameover();
			exit(0);
        }
    }
}

///游戏暂停后菜单界面，一般按ESC键后启动该界面///
void pauseMenu(){
	///设置背景色为蓝色 ///
    setbkcolor(RGB(80,130,190));
	///用背景色清空屏幕 ///
    cleardevice();
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(50,0,_T("黑体"));
    outtextxy(233,120,_T("1 继续游戏"));
    outtextxy(233,180,_T("2 保存档案"));
    outtextxy(210,240,_T("3 返回主菜单"));
    FlushBatchDraw();
	Sleep(2);
	///判断是否有输入///
    if(_kbhit())  
    {
        input = _getch();  // 根据用户的不同输入来移动，不必输入回车
        if (input == '1') 
            gameStatus = 1;
        else if (input == '2')
        {
            writeRecordFile();
            gameStatus = 1;
        }
        else if (input == '3')
        {
            gameStatus = 0;
        }
    }
}

void startup(){
	///初始化种子///
	srand((unsigned int)time(0));
	initgraph(Width,Height);
    ///获取窗口句柄///
    HWND hwnd = GetHWnd();
    ///设置窗口标题文字///
    SetWindowText(hwnd,_T("节奏大师 v1.0"));
    BeginBatchDraw();    
    while (gameStatus==0)
        startMenu(); //初始菜单界面
}

void updateWithoutInput(){}

void updateWithInput(){}

void gameover(){
    EndBatchDraw();
    _getch();
    closegraph();
}

void GameCleanUp(){
	
}

void show(){
    while(1){
		while (gameStatus==3){
			///游戏暂停后菜单界面///
			pauseMenu(); 
		}
		while(gameStatus==0){
			startMenu();
		}
		if(gameStatus == 2)return;
		setbkcolor(RGB(0,0,0));
		cleardevice();
		line(0,500,700,500);
        // 绘制黑线、黑色填充的圆
        setcolor(BLACK);
        setfillcolor(BLACK);
        for (i=0;i<BallNum;i++)
        {
			fillcircle((int)balls[i].x,(int) balls[i].y, radius);
        }
        for (i=0;i<BallNum;i++)
        {
            //ball_x[i] = ball_x[i]; //+ ball_vx[i];
			balls[i].y += balls[i].veclocity;
			if(balls[i].y > 590) 
            {
                balls[i] = GenerateNewBall(&balls[i],VeclocityMovement,PositionMovement);
            }
        }
        // 绘制黄线、绿色填充的圆
        setcolor(YELLOW);
        setfillcolor(GREEN);
        for (i=0;i< (BallNum/2);i++)
        {
			fillcircle((int)balls[i].x, (int)balls[i].y, radius);
        }
        setcolor(YELLOW);
        setfillcolor(BLUE);
        for (i=(BallNum/2);i<BallNum;i++)
        {
			fillcircle((int)balls[i].x, (int)balls[i].y, radius);
        }
		Block(处理输入，播放音乐){
		if(_kbhit()){  
			input = _getch();  // 根据用户的不同输入来移动，不必输入回车
			if (input ==27){
				gameStatus = 3;
				continue;
			}
			for(i = 0;i < BallNum;i++){
				if(inputs_show[i] == input && balls[i].y > 500){
					score++;
					balls[i] = GenerateNewBall(&balls[i],VeclocityMovement,PositionMovement);
					#ifndef NO_MEDIA_COMP //由于本机没有音频文件，所以本机不变音乐部分，如果要编译，注释掉main.h中的 NO_MEDIS_COMP即可
					TCHAR * AllocString = (TCHAR *)malloc(sizeof(TCHAR) * 512);
					memset(AllocString,0,sizeof(TCHAR)*512);
					//如果为乱码，wsprintf(AllocString,L"open .%s alias gemusic",media_paths[i]);
					sprintf(AllocString,"open .%s alias gemusic",media_paths[i]);
					mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // 先把前面一次的音乐停止
					mciSendString(_T("close gemusic"), NULL, 0, NULL); // 先把前面一次的音乐关闭
					mciSendString（AllocString, NULL, 0, NULL); // 打开跳动音乐
					mciSendString(_T("play gemusic"), NULL, 0, NULL); // 仅播放一次
					#endif
				}
			}
		}
		}
		TCHAR s[64];
	    //如果乱码了,例子如下
		//wsprintf(s,L"Score:%d",score);
		sprintf(s,"Score:%d",score);
		settextstyle(16,0,_T("黑体"));
		outtextxy(1,1,s);
		FlushBatchDraw();
		Sleep(50);
	}
}

//魔改时善意的提醒：读取出来的ball_x只是一串无用字符串哦！
void readRecordFile(){
    FILE * fp = NULL;
	fopen_s(&fp,SAVE_PATH,"r");
	if(!fp){
		::string str = "读取时无法打开文件";
		str += SAVE_PATH;
		MessageBox(NULL,str.c_str(),_T("Error"),MB_TOPMOST | MB_OK | MB_ICONERROR);
		return;
	}
	for(int i = 0;i < BallNum;i++){
		///读取数据///
		int x,y,v;
		fscanf_s(fp,"%d %d %d",&x,&y,&v);
		balls[i].x = (float)((float)x/(float)PER_SPEC);
		balls[i].y = (float)((float)y/(float)PER_SPEC);
		balls[i].veclocity = (float)((float)v/(float)PER_SPEC);
	}
	fscanf_s(fp," %d",&score);
    fclose(fp);
}

void writeRecordFile(){
	FILE * fp = NULL;
    fopen_s(&fp,SAVE_PATH,"w");
    if(!fp){
		::string str = _T("写入时无法打开文件");
		str += SAVE_PATH;
		MessageBox(NULL,str.c_str(),_T("Error"),MB_TOPMOST | MB_OK | MB_ICONERROR);
		/*如果乱码
			::wstring str = _T("写入时无法打开文件");
			str += SAVE_PATH;
			MessageBox(NULL,str.c_str(),_T("Error"),MB_TOPMOST | MB_OK | MB_ICONERROR);
		*/
		return;
	}
	for(int i = 0;i < BallNum;i++){
		///写入数据///
		fprintf_s(fp,"%d %d %d",(int)(balls[i].x * PER_SPEC),(int)(balls[i].y * PER_SPEC),(int)(balls[i].veclocity * PER_SPEC));
	}
	fprintf_s(fp," %d",&score);
    fclose(fp);
}

#endif