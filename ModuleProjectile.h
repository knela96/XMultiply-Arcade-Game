#ifndef __ModuleProjectile_H__
#define __ModuleProjectile_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"

struct SDL_Rect;
struct SDL_Texture;
struct Mix_Chunk;

typedef unsigned int Uint32;

struct Bullet {
	SDL_Rect* bullet;
	iPoint position;
};

class ModuleProjectile : public Module
{
public:

	ModuleProjectile();
	~ModuleProjectile();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool checkCollision(SDL_Rect* bullet, SDL_Rect* enemy);

public:
	
	SDL_Rect* shoot;
	ModulePlayer* player;
	Mix_Chunk* shoot_fx = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation singleshot;
	Bullet bullets[10] = { false,{ 0,0 } };
	Uint32* start_time = 0;
	Uint32* shooting_delay;
};

#endif // __ModuleInput_H__
