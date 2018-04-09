#ifndef __ModuleParticles_H__
#define __ModuleParticles_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Rect;
struct SDL_Texture;
struct Mix_Chunk;

struct Particle {
	SDL_Rect* bullet;

	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	bool Update();

	Mix_Chunk* common_fx = nullptr;
	
};

class ModuleParticles : public Module
{
public:

	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, Uint32 delay = 0);

public:
	Uint32 * start_time = 0;
	Uint32* shooting_delay;
	Particle shoot;

private: 
	SDL_Texture * graphics = nullptr;
	Particle * active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;
};

#endif // __ModuleInput_H__
