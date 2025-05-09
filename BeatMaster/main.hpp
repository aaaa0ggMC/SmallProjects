#pragma once
#include "Ball.hpp"
#include <malloc.h>

///С��ĸ���///
///�㶨��������������ball,ball2�����Է���///
#define BallNum 6

//�����ļ���λ��
//#define SAVE_PATH "D:\\c����\\��ҵ\\������Դ\\��6��\\�����ز�\\gameRecord.dat"
#define SAVE_PATH _T("D:\\0root.dat")

#define NO_MEDIA_COMP 

#define PER_SPEC 1000 //���ݴ洢����(α),�ĸ�С����

static const char inputs_show[BallNum] = {'a','d','k','s','j','l'};
static const TCHAR * media_paths[BallNum] = {_T("D:\\c����\\��ҵ\\������Դ\\��6��\\�����ز�\\jump.mp3"),
									  _T("D:\\c����\\��ҵ\\������Դ\\��6��\\�����ز�\\f_gun.mp3"),
									  _T("D:\\c����\\��ҵ\\������Դ\\��6��\\�����ز�\\jump.mp3"),
									  _T("D:\\c����\\��ҵ\\������Դ\\��6��\\�����ز�\\f_gun.mp3"),
									  _T("D:\\c����\\��ҵ\\������Դ\\��6��\\�����ز�\\jump.mp3"),
									  _T("D:\\c����\\��ҵ\\������Դ\\��6��\\�����ز�\\f_gun.mp3")};

/*
*@Summary ��ʼ�˵�����
*/
void startMenu();
/*
*@Summary  ��Ϸ��ͣ��˵����棬һ�㰴ESC���������ý���
*/
void pauseMenu();
/*
*@Summary ���ݳ�ʼ�� 
*/
void startup();
/*
*@Summary ��ʾ����
*/
void show();
/*
*@Summary ���û������޹صĸ���
*/
void updateWithoutInput();
/*
*@Summary ���û������йصĸ���
*/
void updateWithInput();
/*
*@Summary ��Ϸ��������������
*/
void gameover();
/*
*@Summary ��ȡ��Ϸ�����ļ��浵
*/
void readRecordFile();
/*
*@Summary �洢��Ϸ�����ļ��浵
*/
void writeRecordFile();
/*
*@Summary �ٶȵı仯
*/
float VeclocityMovement(float);
/*
*@Summary λ�õı仯
*/
Position PositionMovement(float x,float y);
/*
*@Summary ����������˵�������
*/
void GameCleanUp();