#pragma once
#include "Ball.hpp"
#include <malloc.h>

///小球的个数///
///你定义了两个变量，ball,ball2，所以翻倍///
#define BallNum 6

//保存文件的位置
//#define SAVE_PATH "D:\\c语言\\作业\\随书资源\\第6章\\音乐素材\\gameRecord.dat"
#define SAVE_PATH _T("D:\\0root.dat")

#define NO_MEDIA_COMP 

#define PER_SPEC 1000 //数据存储精度(伪),四个小数点

static const char inputs_show[BallNum] = {'a','d','k','s','j','l'};
static const TCHAR * media_paths[BallNum] = {_T("D:\\c语言\\作业\\随书资源\\第6章\\音乐素材\\jump.mp3"),
									  _T("D:\\c语言\\作业\\随书资源\\第6章\\音乐素材\\f_gun.mp3"),
									  _T("D:\\c语言\\作业\\随书资源\\第6章\\音乐素材\\jump.mp3"),
									  _T("D:\\c语言\\作业\\随书资源\\第6章\\音乐素材\\f_gun.mp3"),
									  _T("D:\\c语言\\作业\\随书资源\\第6章\\音乐素材\\jump.mp3"),
									  _T("D:\\c语言\\作业\\随书资源\\第6章\\音乐素材\\f_gun.mp3")};

/*
*@Summary 初始菜单界面
*/
void startMenu();
/*
*@Summary  游戏暂停后菜单界面，一般按ESC键后启动该界面
*/
void pauseMenu();
/*
*@Summary 数据初始化 
*/
void startup();
/*
*@Summary 显示画面
*/
void show();
/*
*@Summary 与用户输入无关的更新
*/
void updateWithoutInput();
/*
*@Summary 与用户输入有关的更新
*/
void updateWithInput();
/*
*@Summary 游戏结束、后续处理
*/
void gameover();
/*
*@Summary 读取游戏数据文件存档
*/
void readRecordFile();
/*
*@Summary 存储游戏数据文件存档
*/
void writeRecordFile();
/*
*@Summary 速度的变化
*/
float VeclocityMovement(float);
/*
*@Summary 位置的变化
*/
Position PositionMovement(float x,float y);
/*
*@Summary 清除返回主菜单的数据
*/
void GameCleanUp();