#ifndef __ENEMY_BOSSS4HEART_H_
#define __ENEMY_BOSSS4HEART_H__

#include "Enemy.h"


class Enemy_BossS4Heart : public Enemy
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
	Enemy_BossS4Heart(int x, int y);

	void Move();
};

#endif // __ENEMY_BIG_EYE_H__