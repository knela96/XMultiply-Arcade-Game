#ifndef __ENEMY_BOSSS4TENTA_H_
#define __ENEMY_BOSSS4TENTA_H__

#include "Enemy.h"


class Enemy_BossS4Tenta : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	Animation spawn_head;
	Uint32 shoot_delay = 0;


public:

	iPoint original_position;
	Path* path = new Path();
	Enemy_BossS4Tenta(int x, int y);

	void Move();
};

#endif // __ENEMY_BIG_EYE_H__