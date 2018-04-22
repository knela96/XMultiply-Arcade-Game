#ifndef __ENEMY_POWERUPSHIP_H__
#define __ENEMY_POWERUPSHIP_H__

#include "Enemy.h"


struct PowerUp;

class Enemy_PowerupShip : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	PowerUp* p = nullptr;

public:

	iPoint original_position;
	Path* path = new Path();
	Enemy_PowerupShip(int x, int y, uint PU);
	virtual void OnCollision(Collider* collider);
	void Move();
};

#endif // __ENEMY_POWERUPSHIP_H_