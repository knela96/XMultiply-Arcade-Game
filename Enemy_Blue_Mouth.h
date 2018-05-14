#ifndef __ENEMY_BLUE_MOUTH_H__
#define __ENEMY_BLUE_MOUTH_H__

#include "Enemy.h"


class Enemy_Blue_Mouth : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	Uint32 shoot_delay = 0;


public:

	iPoint original_position;
	Path* path = new Path();
	Enemy_Blue_Mouth(int x, int y);

	void Move();
};

#endif // __ENEMY_BLUE_MOUTH_H__