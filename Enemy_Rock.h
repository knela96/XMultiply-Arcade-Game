#ifndef __ENEMY_ROCK_H__
#define __ENEMY_ROCK_H__

#include "Enemy.h"


class Enemy_Rock : public Enemy
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
	Enemy_Rock(int x, int y, bool move_up);

	void Move(Collider* c1, Collider* c2);
};

#endif // __ENEMY_ROCK_H__
