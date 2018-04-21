#ifndef __ENEMY_BROWNWORM_H__
#define __ENEMY_BROWNWORM_H__

#include "Enemy.h"


class Enemy_BrownWorm : public Enemy
{
private:
	int wave = 1;
	bool move_up = true;
	int original_y = 0;
	Animation fly;
	int radius = 20;
	float angle = 0;
	bool _return = false;


public:

	iPoint original_position;
	Path* path = new Path();
	Enemy_BrownWorm(int x, int y, bool move_up);

	void Move();
};

#endif // __ENEMY_BROWNWORM_H__