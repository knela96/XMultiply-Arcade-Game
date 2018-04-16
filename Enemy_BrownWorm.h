#ifndef __ENEMY_BROWNWORM_H__
#define __ENEMY_BROWNWORM_H__

#include "Enemy.h"


class Enemy_BrownWorm : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;


public:

	iPoint original_position;
	Path* path = new Path();
	Enemy_BrownWorm(int x, int y);

	void Move();
};

#endif // __ENEMY_BROWNWORM_H__