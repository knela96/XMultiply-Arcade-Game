#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"
#include "Enemy_BrownWorm.h"
#include "ModuleTextures.h"

#define MAX_ENEMIES 200

struct Mix_Chunk;

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	bool move_up;
	float flip;
	int x, y;
	uint PU;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y, uint PU = -1, bool move_up = false, bool flip = false);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites[MAX_TEXTURES];
	Mix_Chunk* Brownworm_fx;
	Mix_Chunk* LittleShrimp_fx;
	Mix_Chunk* Nemona_fx;
	Mix_Chunk* Powership_fx;
};

#endif // __ModuleEnemies_H__