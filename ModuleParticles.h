#ifndef __ModuleParticles_H__
#define __ModuleParticles_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
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

enum PARTICLE_TEXTURE
{
	PARTICLES_PLAYER,
	PARTICLES_LASERS,
	POWERUP,
	PARTICLES_EXPLOSION,
	PARTICLES_ENEMYSHOOT,
};
enum PARTICLE_TYPE
{
	NONE,
	BASIC_SHOOT,
	TENTACLE_SHOOT,
	BASIC_LASER,
	BOMB_SHOOT,
	BOMB_EXPLOSION,
	PLAYER_EXPLOSION,
	ENEMY_EXPLOSION,
	TENTACLE_EXPLOSION,
	BASIC_SHOOT_EXPLOSION,
	ANEMONA_SHOOT,
	SHRIMP_SHOOT,
	STAGE4BOSS_SHOOT,

};

struct Particle {

	Collider* collider = nullptr;
	Animation anim;
	Mix_Chunk* fx = 0;
	Mix_Chunk* hit_fx = 0;
	iPoint position;
	fPoint speed;
	fPoint direction_speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	int id = 0;
	PARTICLE_TYPE type = NONE;
	Path* path = new Path();

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();

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
	void removeParticles();

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, fPoint direction_speed = { 0,0 }, Uint32 delay = 0);
	
	
public:

	Uint32 * start_time = 0;
	Uint32* shooting_delay;
	Particle basic_laser;
	Particle basic_shoot;
	Particle tentacle_shoot;
	Particle bomb;
	Particle explosion_player;
	Particle explosion_enemy;
	Particle explosion_bullet;
	Particle explosion_tentacle_bullet;
	Particle explosion_bomb;
	Particle anemona_shoot;
	Particle shrimp_shoot;
	Particle Stage4Boss_shoot;
	Particle Powerup;
	Animation* animation = nullptr;

private: 
	SDL_Texture * graphics[MAX_PARTICLE_TEXTURES];
	Particle * active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;
};

#endif // __ModuleInput_H__
