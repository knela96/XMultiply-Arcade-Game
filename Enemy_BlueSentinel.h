#ifndef __ENEMY_BLUESENTINEL_H__
#define __ENEMY_BLUESENTINEL_H__

#include "Enemy.h"


class Enemy_BlueSentinel : public Enemy
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

	Enemy_BlueSentinel(int x, int y);

	void Move();
};

#endif // __ENEMY_BROWNWORM_H__
