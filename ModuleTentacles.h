#ifndef __MODULETENTACLES_H__
#define __MODULETENTACLES_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleCollision.h"

#define MAX_TENTACLES 14

struct SDL_Texture;
struct SDL_Rect;
struct Collider;

struct Tentacle {
	Collider* collider = nullptr;
	iPoint first_point;
	iPoint second_point;
	bool anchor = false;
	Animation anim;
	bool flip = false;

	Tentacle();
	Tentacle(const Tentacle& p);
	bool Update();
};


class ModuleTentacles : public Module
{
public:
	Tentacle tentacle;
	Tentacle anchor;
	Tentacle* tentacles[MAX_TENTACLES];
private:
	SDL_Texture * graphics = nullptr;
public:
	ModuleTentacles();
	~ModuleTentacles();
	bool Start();
	update_status Update();
	bool CleanUp();
	void AddTentacle(const Tentacle& tentacle, int x, int y, bool flip = false, bool anchor = false);
	void setPosition(int x, int y);
	void ShootLaser();
};

#endif // __ENEMY_H__