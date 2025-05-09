#include <graphics.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include "main.hpp"
#include "Ball.hpp"

using namespace std;

///���ڵĿ�///
#define Width 700
///���ڵĸ�///
#define Height 600

//�������
extern const char inputs_show[BallNum];
extern const TCHAR * media_paths[BallNum];

///�����۵�����ʱע��һ��///
#define Block(x)

///����winmm����ʹ��mciXXX///
#pragma comment(lib,"winmm.lib")

#define OneDragon(X) score++;BallNum[(X)] = GenerateNewBall(&BallNum[(X)],VeclocityMovement,PositionMovement);

///����///
int score = 0;

///��Ϸ״̬///
///0:��ʼ�ʵ�///
///1:������Ϸ///
///2:�˳�///
///3.��ͣ///
int gameStatus = 0;

///С��İ뾶///
int radius = 15;

///�û�������///
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

///������///
int main(void){
	startup();  // ���ݳ�ʼ��
    while (1){
        show();  // ��ʾ����
        updateWithoutInput();  // ���û������޹صĸ���
        updateWithInput();     // ���û������йصĸ���
    }
    gameover();     // ��Ϸ��������������
    return 0;
}

///�����۵����룬����Ϸ���к���Ӱ��///
#if 1 //����ʵ��main.h������

///�ٶȵı仯���Լ�����///
float VeclocityMovement(float in){
	return in + 1;
}

///λ�õı仯���Լ�����///
Position PositionMovement(float x,float y){
	Position ps = {0,0};
	ps.x = (float)(rand() % Width);
	ps.y = 0;//�Ӷ�������
	return ps;
}

///��ʼ�˵�����///
void startMenu(){
	///���ñ���ɫΪ��ɫ///
    setbkcolor(RGB(80,130,190));
	///�ñ���ɫ�����Ļ///
    cleardevice();
	///�������������ɫΪ͸��///
    setbkmode(TRANSPARENT);
	///�������������ɫΪ��ɫ///
    settextcolor(BLACK);
    settextstyle(50,0,_T("����"));
    outtextxy(233,120,_T("1 ����Ϸ"));
    outtextxy(233,180,_T("2 ��ȡ��Ϸ�浵"));
    outtextxy(233,240,_T("3 �˳�"));
    FlushBatchDraw();
	Sleep(2);
	///�ж��Ƿ�������///
    if(_kbhit()){
		///�����û��Ĳ�ͬ�������ƶ�����������س�///
        input = _getch(); 
        if (input == '1')gameStatus = 1;
        else if (input == '2'){
            readRecordFile();
            gameStatus = 1;
        }
        else if (input == '3'){
			//������벻���ߵ�gameover�������������Լ���ԭ�򣬱����ң�������Ҳһ����ֻ�����Ұ������
            gameStatus = 2;
            gameover();
			exit(0);
        }
    }
}

///��Ϸ��ͣ��˵����棬һ�㰴ESC���������ý���///
void pauseMenu(){
	///���ñ���ɫΪ��ɫ ///
    setbkcolor(RGB(80,130,190));
	///�ñ���ɫ�����Ļ ///
    cleardevice();
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(50,0,_T("����"));
    outtextxy(233,120,_T("1 ������Ϸ"));
    outtextxy(233,180,_T("2 ���浵��"));
    outtextxy(210,240,_T("3 �������˵�"));
    FlushBatchDraw();
	Sleep(2);
	///�ж��Ƿ�������///
    if(_kbhit())  
    {
        input = _getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
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
	///��ʼ������///
	srand((unsigned int)time(0));
	initgraph(Width,Height);
    ///��ȡ���ھ��///
    HWND hwnd = GetHWnd();
    ///���ô��ڱ�������///
    SetWindowText(hwnd,_T("�����ʦ v1.0"));
    BeginBatchDraw();    
    while (gameStatus==0)
        startMenu(); //��ʼ�˵�����
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
			///��Ϸ��ͣ��˵�����///
			pauseMenu(); 
		}
		while(gameStatus==0){
			startMenu();
		}
		if(gameStatus == 2)return;
		setbkcolor(RGB(0,0,0));
		cleardevice();
		line(0,500,700,500);
        // ���ƺ��ߡ���ɫ����Բ
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
        // ���ƻ��ߡ���ɫ����Բ
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
		Block(�������룬��������){
		if(_kbhit()){  
			input = _getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
			if (input ==27){
				gameStatus = 3;
				continue;
			}
			for(i = 0;i < BallNum;i++){
				if(inputs_show[i] == input && balls[i].y > 500){
					score++;
					balls[i] = GenerateNewBall(&balls[i],VeclocityMovement,PositionMovement);
					#ifndef NO_MEDIA_COMP //���ڱ���û����Ƶ�ļ������Ա����������ֲ��֣����Ҫ���룬ע�͵�main.h�е� NO_MEDIS_COMP����
					TCHAR * AllocString = (TCHAR *)malloc(sizeof(TCHAR) * 512);
					memset(AllocString,0,sizeof(TCHAR)*512);
					//���Ϊ���룬wsprintf(AllocString,L"open .%s alias gemusic",media_paths[i]);
					sprintf(AllocString,"open .%s alias gemusic",media_paths[i]);
					mciSendString(_T("stop gemusic"), NULL, 0, NULL);   // �Ȱ�ǰ��һ�ε�����ֹͣ
					mciSendString(_T("close gemusic"), NULL, 0, NULL); // �Ȱ�ǰ��һ�ε����ֹر�
					mciSendString��AllocString, NULL, 0, NULL); // ����������
					mciSendString(_T("play gemusic"), NULL, 0, NULL); // ������һ��
					#endif
				}
			}
		}
		}
		TCHAR s[64];
	    //���������,��������
		//wsprintf(s,L"Score:%d",score);
		sprintf(s,"Score:%d",score);
		settextstyle(16,0,_T("����"));
		outtextxy(1,1,s);
		FlushBatchDraw();
		Sleep(50);
	}
}

//ħ��ʱ��������ѣ���ȡ������ball_xֻ��һ�������ַ���Ŷ��
void readRecordFile(){
    FILE * fp = NULL;
	fopen_s(&fp,SAVE_PATH,"r");
	if(!fp){
		::string str = "��ȡʱ�޷����ļ�";
		str += SAVE_PATH;
		MessageBox(NULL,str.c_str(),_T("Error"),MB_TOPMOST | MB_OK | MB_ICONERROR);
		return;
	}
	for(int i = 0;i < BallNum;i++){
		///��ȡ����///
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
		::string str = _T("д��ʱ�޷����ļ�");
		str += SAVE_PATH;
		MessageBox(NULL,str.c_str(),_T("Error"),MB_TOPMOST | MB_OK | MB_ICONERROR);
		/*�������
			::wstring str = _T("д��ʱ�޷����ļ�");
			str += SAVE_PATH;
			MessageBox(NULL,str.c_str(),_T("Error"),MB_TOPMOST | MB_OK | MB_ICONERROR);
		*/
		return;
	}
	for(int i = 0;i < BallNum;i++){
		///д������///
		fprintf_s(fp,"%d %d %d",(int)(balls[i].x * PER_SPEC),(int)(balls[i].y * PER_SPEC),(int)(balls[i].veclocity * PER_SPEC));
	}
	fprintf_s(fp," %d",&score);
    fclose(fp);
}

#endif