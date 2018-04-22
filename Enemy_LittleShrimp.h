#ifndef __ENEMY_LITTLESHRIMP_H__
#define __ENEMY_LITTLESHRIMP_H__

#include "Enemy.h"


class Enemy_LittleShrimp : public Enemy
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
	Enemy_LittleShrimp(int x, int y);

	void Move();
};

#endif // __ENEMY_BROWNWORM_H__