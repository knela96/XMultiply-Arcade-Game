#ifndef __ModuleParticles_H__
#define __ModuleParticles_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "Path.h"

#define MAX_ACTIVE_PARTICLES 100

#define MAX_PARTICLE_TEXTURES 5

struct SDL_Rect;
struct SDL_Texture;
struct Mix_Chunk;
struct Collider;
enum COLLIDER_TYPE;

enum PARTICLE_TYPE
{
	NONE,
	PARTICLES_PLAYER,
	PARTICLES_LASERS,
	POWERUP,
	PARTICLES_EXPLOSION,
};

struct Particle {

	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	int id = 0;
	PARTICLE_TYPE type = NONE;

	Particle();
	Particle(const Particle& p, PARTICLE_TYPE type);
	~Particle();
	bool Update();

	//Mix_Chunk* common_fx = nullptr;

	bool operator==(const Particle &g) const
	{
		return this->id == g.id;
	}

	
	
};

class ModuleParticles : public Module
{
public:

	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, PARTICLE_TYPE type, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	
	
public:

	Uint32 * start_time = 0;
	Uint32* shooting_delay;
	Particle shoot1;
	Particle shoot2;
	Particle explosion_player;
	Particle explosion_enemy;
	Particle explosion_bullet;
	Particle basic_laser;
	Particle Powerup;
	Animation* animation = nullptr;
	Path* path = new Path();

private: 
	SDL_Texture * graphics[MAX_PARTICLE_TEXTURES];
	Particle * active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;
};

#endif // __ModuleInput_H__
