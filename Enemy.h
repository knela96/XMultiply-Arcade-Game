#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation * animation = nullptr;
	Collider* collider = nullptr;

public:
	iPoint position;
	ENEMY_TYPES type = NO_TYPE;
	float flip = false;
	int live = 1;
	bool hit = false;
	Uint32 start_time;
	uint score = 0;
public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites,float flip = 0.0f);
	virtual void OnCollision(Collider* collider);
};

#endif // __ENEMY_H__