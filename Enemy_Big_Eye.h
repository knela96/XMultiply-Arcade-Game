#ifndef __ENEMY_BIG_EYE_H_
#define __ENEMY_BG_EYE_H__

#include "Enemy.h"


class Enemy_Big_Eye : public Enemy
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
	Enemy_Big_Eye(int x, int y);

	void Move();
};

#endif // __ENEMY_BIG_EYE_H__