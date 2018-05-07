#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_BrownWorm.h"
#include "Enemy_LittleShrimp.h"
#include "Enemy_PowerupShip.h"
#include "Enemy_Nemona.h"
#include "ModuleAudio.h"
#include "ModuleSceneStage1.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
	for (uint i = 0; i < MAX_TEXTURES; ++i)
		sprites[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites[ENEMY_TYPES::BROWN_WORM] = App->textures->Load("Assets/Sprites/Stage1/Enemies/monsterball.png");
	sprites[ENEMY_TYPES::LITTLE_SHRIMP] = App->textures->Load("Assets/Sprites/Stage1/Enemies/littleshrimp.png");
	sprites[ENEMY_TYPES::NEMONA_TENTACLE] = App->textures->Load("Assets/Sprites/Stage1/Enemies/nemona.png");
	sprites[ENEMY_TYPES::POWERUPSHIP] = App->textures->Load("Assets/Sprites/PowerUp/PowerUp.png");
	sprites[ENEMY_TYPES::BIG_EYE] = App->textures->Load("Assets/Sprites/Stage1/Enemies/BigEye.png");
	sprites[ENEMY_TYPES::BIG_SHRIMP] = App->textures->Load("Assets/Sprites/Stage1/Enemies/BigShrimp.png");
	sprites[ENEMY_TYPES::BLUE_MOUTH] = App->textures->Load("Assets/Sprites/Stage1/Enemies/BlueMouth.png");
	sprites[ENEMY_TYPES::BLUE_SENTINEL] = App->textures->Load("Assets/Sprites/Stage1/Enemies/2ndlvlmonster.png");
	sprites[ENEMY_TYPES::YELLOW_BALL] = App->textures->Load("Assets/Sprites/Stage1/Enemies/YellowBall.png");
	sprites[ENEMY_TYPES::BOUNCER] = App->textures->Load("Assets/Sprites/Stage1/Enemies/Yelloweye.png");

	Brownworm_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-100.wav");
	LittleShrimp_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-100.wav");
	Nemona_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-094.wav");
	Powership_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-055.wav");

	return true;
}
// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");
	App->audio->UnloadS(Brownworm_fx);
	Brownworm_fx = nullptr;
	App->audio->UnloadS(LittleShrimp_fx);
	LittleShrimp_fx = nullptr;
	App->audio->UnloadS(Nemona_fx);
	Nemona_fx = nullptr;
	App->audio->UnloadS(Powership_fx);
	Powership_fx = nullptr;

	for (uint i = 0; i < MAX_TEXTURES; ++i) {
		if (sprites[i] != nullptr)
		{
			App->textures->Unload(sprites[i]);
			sprites[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		if (queue[i].type != ENEMY_TYPES::NO_TYPE) {
			queue[i].type = ENEMY_TYPES::NO_TYPE;
		}
	}


	return true;
}

void ModuleEnemies::removeEnemies()
{
	LOG("Rmoving enemies");
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		if (queue[i].type != ENEMY_TYPES::NO_TYPE) {
			queue[i].type = ENEMY_TYPES::NO_TYPE;
		}
	}

}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) {
			switch(enemies[i]->type) {
			case BROWN_WORM:
				enemies[i]->Draw(sprites[BROWN_WORM]);
				break;
			case LITTLE_SHRIMP:
				enemies[i]->Draw(sprites[LITTLE_SHRIMP],enemies[i]->flip);
				break;
			case NEMONA_TENTACLE:
				enemies[i]->Draw(sprites[NEMONA_TENTACLE]);
				break;
			case POWERUPSHIP:
				enemies[i]->Draw(sprites[POWERUPSHIP]);
				break;
			case BIG_EYE:
				enemies[i]->Draw(sprites[BIG_EYE]);
				break;
			case BIG_SHRIMP:
				enemies[i]->Draw(sprites[BIG_SHRIMP]);
				break;
			case BOUNCER:
				enemies[i]->Draw(sprites[BOUNCER]);
				break;
			case YELLOW_BALL:
				enemies[i]->Draw(sprites[YELLOW_BALL]);
				break;
			case BLUE_SENTINEL:
				enemies[i]->Draw(sprites[BLUE_SENTINEL]);
				break;
			case BLUE_MOUTH:
				enemies[i]->Draw(sprites[BLUE_MOUTH]);
				break;
			}
		}

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}



bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, uint PU, bool move_up, bool flip)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].move_up = move_up;
			queue[i].flip = flip;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].PU = PU;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::BROWN_WORM:
			enemies[i] = new Enemy_BrownWorm(info.x, info.y, info.move_up);
			enemies[i]->type = ENEMY_TYPES::BROWN_WORM;
			break;
		case ENEMY_TYPES::LITTLE_SHRIMP:
			enemies[i] = new Enemy_LittleShrimp(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::LITTLE_SHRIMP;
			break;
		case ENEMY_TYPES::NEMONA_TENTACLE:
			enemies[i] = new Enemy_Nemona(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::NEMONA_TENTACLE;
			break;
		case ENEMY_TYPES::POWERUPSHIP:
			enemies[i] = new Enemy_PowerupShip(info.x, info.y, info.PU);
			enemies[i]->type = ENEMY_TYPES::POWERUPSHIP;
			break;

		case ENEMY_TYPES::BIG_EYE:
			enemies[i] = new Enemy_BigEye(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BIG_EYE;
			break;

		case ENEMY_TYPES::BIG_SHRIMP:
			enemies[i] = new Enemy_Big_Shrimp(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BIG_SHRIMP;
			break;

		case ENEMY_TYPES::BLUE_MOUTH:
			enemies[i] = new Enemy_BigMouth(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BLUE_MOUTH;
			break;

		case ENEMY_TYPES::BLUE_SENTINEL:
			enemies[i] = new Enemy_BlueSentinel(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BLUE_SENTINEL;
			break;

		case ENEMY_TYPES::BOUNCER:
			enemies[i] = new Enemy_Bouncer(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BOUNCER;
			break;

		case ENEMY_TYPES::YELLOW_BALL:
			enemies[i] = new Enemy_YellowBall(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::YELLOW_BALL;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && (c2->type == COLLIDER_PLAYER || c2->type == COLLIDER_PLAYER_SHOT))
		{
			switch (enemies[i]->type) {
				case ENEMY_TYPES::BROWN_WORM:
					App->audio->PlaySound(Brownworm_fx);
					break;
				case ENEMY_TYPES::LITTLE_SHRIMP:
					App->audio->PlaySound(LittleShrimp_fx);
					break;
				case ENEMY_TYPES::NEMONA_TENTACLE:
					App->audio->PlaySound(Nemona_fx);
					break;
				case ENEMY_TYPES::POWERUPSHIP:
					App->audio->PlaySound(Powership_fx);

					break;
			}
			enemies[i]->OnCollision(c2);
			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}