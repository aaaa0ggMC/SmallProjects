//ֻ����һ��
#pragma once

//����
typedef struct{
	float x;
	float y;
} Position;

//float����Ϊ��һ�ε��ٶȣ�float����Ϊ�µ��ٶ�
//�ٶȱ仯�ĺ���ָ��
typedef float (*VeclocityMovementFunction)(float);
//�������ɵĺ���
typedef Position (*PositionSummoner)(float x,float y);

//һ����
typedef struct{
	float x;
	float y;
	float veclocity;
} Ball;


Ball GenerateNewBall(const Ball *,VeclocityMovementFunction,PositionSummoner);
