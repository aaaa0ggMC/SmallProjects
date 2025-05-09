//只包含一次
#pragma once

//坐标
typedef struct{
	float x;
	float y;
} Position;

//float参数为上一次的速度，float返回为新的速度
//速度变化的函数指针
typedef float (*VeclocityMovementFunction)(float);
//坐标生成的函数
typedef Position (*PositionSummoner)(float x,float y);

//一个球
typedef struct{
	float x;
	float y;
	float veclocity;
} Ball;


Ball GenerateNewBall(const Ball *,VeclocityMovementFunction,PositionSummoner);
