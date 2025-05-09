#include "Ball.hpp"

Ball GenerateNewBall(const Ball * originBall,VeclocityMovementFunction vFunc,PositionSummoner psFunc){
	Ball returnBall = {0,0,0};
	Position pos = {0,0};
	returnBall.veclocity = vFunc(originBall->veclocity);
	pos = psFunc(originBall->x,originBall->y);
	returnBall.x = pos.x;
	returnBall.y = pos.y;
	return returnBall;
}