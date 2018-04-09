#ifndef __ModuleParticles_H__
#define __ModuleParticles_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"

struct SDL_Rect;
struct SDL_Texture;
struct Mix_Chunk;

typedef unsigned int Uint32;

struct Particle {
	SDL_Rect* bullet;
	iPoint position;
	Animation anim;
	uint fx = 0;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	Particle() {};
	Particle(const Particle& p) {  };
	bool Update() {};;

	
};

class ModuleParticles : public Module
{
public:

	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	bool checkCollision(SDL_Rect* bullet, SDL_Rect* enemy);
	void AddParticle(const Particle& particle, int x, int y, Uint32 delay = 0);
public:
	
	SDL_Rect* shoot;
	ModulePlayer* player;
	Mix_Chunk* shoot_fx = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation singleshot;
	Particle* bullets;
	Uint32* start_time = 0;
	Uint32* shooting_delay;
};

#endif // __ModuleInput_H__
