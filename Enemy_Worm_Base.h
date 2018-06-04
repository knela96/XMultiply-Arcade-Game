#ifndef __ENEMY_WORM_BASE_H__
#define __ENEMY_WORM_BASE_H__

#include "Enemy.h"


class Enemy_Worm_Base : public Enemy
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
	Enemy_Worm_Base(int x, int y);

	void Move();
};

#endif // __ENEMY_WORM_BASE_H__
