#ifndef __ENEMY_NEMONA_H__
#define __ENEMY_NEMONA_H__

#include "Enemy.h"


class Enemy_Nemona : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;


public:

	iPoint original_position;
	Path* path = new Path();
	Enemy_Nemona(int x, int y);

	void Move();
};

#endif // __ENEMY_NEMONA__