#ifndef __ModulePowerUp_H__
#define __ModulePowerUp_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "Path.h"

#define MAX_POWERUP 10

struct SDL_Rect;
struct SDL_Texture;

struct Mix_Chunk;

struct Collider;
enum COLLIDER_TYPE;

enum POWERUP_TYPE
{
	_NONE,
	TENTACLES_POWERUP,
	BOMB_POWERUP,
	SPEED_POWERUP
};


struct PowerUp {

	bool enabled;
	Collider* collider = nullptr;
	Animation anim;
	iPoint position;
	POWERUP_TYPE type = _NONE;
	Path* path = new Path();

	PowerUp();
	PowerUp(const PowerUp& p);
	~PowerUp();
	void PU_Effect();
	bool Update();


};

class ModulePowerUp : public Module
{
public:

	ModulePowerUp();
	~ModulePowerUp();

	bool Start();

	update_status Update();

	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	PowerUp* AddPowerUp(const PowerUp& powerup, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE);


public:

	PowerUp bomb_powerup;
	PowerUp tentacles_powerup;
	PowerUp speed_powerup;

private:

	SDL_Texture * graphics;
	PowerUp * active[MAX_POWERUP];
};

#endif // __ModuleInput_H__
