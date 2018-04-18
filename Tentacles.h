#ifndef __TENTACLES_H__
#define __TENTACLES_H__

#include "p2Point.h"

struct SDL_Texture;
struct SDL_Rect;

class Tentacles
{
public:
	iPoint first_point;
	iPoint second_point;
	SDL_Texture * graphics = nullptr;
	bool anchor = false;
	SDL_Rect* rect;

public:
	Tentacles(int x, int y);
	virtual ~Tentacles();
	
	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
};

#endif // __ENEMY_H__