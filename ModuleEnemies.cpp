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
#include "Enemy_Big_Eye.h"
#include "Enemy_Blue_Mouth.h"
#include "Enemy_BlueSentinel.h"
#include "Enemy_Yellow_Ball.h"
#include "Enemy_Bouncer.h"
#include "Enemy_Rock.h"
#include "Enemy_Worm_Body.h"
#include "Enemy_Worm_Head.h"
#include "Enemy_Worm_Base.h"
#include "Enemy_Blue_Ball.h"
#include "Enemy_BossS4.h"
#include "Enemy_BossS4Arm.h"
#include "Enemy_BossS4Disp.h"
#include "Enemy_BossS4Face.h"
#include "Enemy_BossS4Heart.h"
#include "Enemy_BossS4Tenta.h"
#include "ModuleAudio.h"
#include "ModuleSceneStage1.h"
#include "SDL/include/SDL_timer.h"


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
	sprites[ENEMY_TYPES::BOSS1] = App->textures->Load("Assets/Sprites/Stage4/Boss/boss4_1.png");
	sprites[ENEMY_TYPES::BOSSTENT] = sprites[ENEMY_TYPES::BOSS1];
	sprites[ENEMY_TYPES::BOSSARM] = App->textures->Load("Assets/Sprites/Stage4/Boss/boss4_2.png");
	sprites[ENEMY_TYPES::BOSSFACE] = App->textures->Load("Assets/Sprites/Stage4/Boss/boss4_3.png");
	sprites[ENEMY_TYPES::BOSSHEART] = sprites[ENEMY_TYPES::BOSSFACE];
	sprites[ENEMY_TYPES::BOSSDISP] = sprites[ENEMY_TYPES::BOSSFACE];
	sprites[ENEMY_TYPES::WORM_HEAD] = App->textures->Load("Assets/Sprites/Stage4/Enemies/Worm_Head.png");
	sprites[ENEMY_TYPES::WORM_BODY] = App->textures->Load("Assets/Sprites/Stage4/Enemies/Worm_Body.png");
	sprites[ENEMY_TYPES::WORM_BASE] = App->textures->Load("Assets/Sprites/Stage4/Enemies/Worm_Base.png");
	sprites[ENEMY_TYPES::BLUE_BALL] = App->textures->Load("Assets/Sprites/Stage4/Enemies/Blue_Ball.png");
	sprites[ENEMY_TYPES::ROCK] = App->textures->Load("Assets/Sprites/Stage4/Enemies/Rock.png");


	Brownworm_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-100.wav");
	LittleShrimp_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-100.wav");
	Nemona_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-094.wav");
	Powership_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-055.wav");
	Yellowball_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-093.wav");
	BigEye_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-094.wav");
	Bouncer_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-057.wav");
	Blue_Ball_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-090.wav");
	hit = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-104.wav");
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
	App->audio->UnloadS(Bouncer_fx);
	Bouncer_fx = nullptr;
	App->audio->UnloadS(Yellowball_fx);
	Yellowball_fx = nullptr;
	App->audio->UnloadS(BigEye_fx);
	BigEye_fx = nullptr;
	App->audio->UnloadS(Blue_Ball_fx);
	Blue_Ball_fx = nullptr;

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
			SDL_Texture* texture = nullptr;
			switch (enemies[i]->type) {
			case BROWN_WORM:
				texture = sprites[BROWN_WORM];
				break;
			case LITTLE_SHRIMP:
				texture = sprites[LITTLE_SHRIMP];
				break;
			case NEMONA_TENTACLE:
				texture = sprites[NEMONA_TENTACLE];
				break;
			case POWERUPSHIP:
				texture = sprites[POWERUPSHIP];
				break;
			case BIG_EYE:
				texture = sprites[BIG_EYE];
				break;
			case BIG_SHRIMP:
				texture = sprites[BIG_SHRIMP];
				break;
			case BOUNCER:
				texture = sprites[BOUNCER];
				break;
			case YELLOW_BALL:
				texture = sprites[YELLOW_BALL];
				break;
			case BLUE_SENTINEL:
				texture = sprites[BLUE_SENTINEL];
				break;
			case BLUE_MOUTH:
				texture = sprites[BLUE_MOUTH];
				break;
			case BOSS1:
				texture = sprites[BOSS1];
				break;
			case BOSSARM:
				texture = sprites[BOSSARM];
				break;
			case BOSSDISP:
				texture = sprites[BOSSDISP];
				break;
			case BOSSTENT:
				texture = sprites[BOSSTENT];
				break;
			case BOSSFACE:
				texture = sprites[BOSSFACE];
				break;
			case BOSSHEART:
				texture = sprites[BOSSHEART];
				break;
			case WORM_BASE:
				texture = sprites[WORM_BASE];
				break;
			case WORM_BODY:
				texture = sprites[WORM_BODY];
				break;
			case WORM_HEAD:
				texture = sprites[WORM_HEAD];
				break;
			case BLUE_BALL:
				texture = sprites[BLUE_BALL];
				break;
			case ROCK:
				texture = sprites[ROCK];
				break;
			}

			if (enemies[i]->hit && (SDL_GetTicks() - enemies[i]->start_time <= 200)) {
				App->render->changeColor(texture,true);
			}else{
				App->render->changeColor(texture,false);
				enemies[i]->hit = false;
			}

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
			case BOSS1:
				enemies[i]->Draw(sprites[BOSS1]);
				break;
			case BOSSARM:
				enemies[i]->Draw(sprites[BOSSARM]);
				break;
			case BOSSDISP:
				enemies[i]->Draw(sprites[BOSSDISP]);
				break;
			case BOSSTENT:
				enemies[i]->Draw(sprites[BOSSTENT]);
				break;
			case BOSSFACE:
				enemies[i]->Draw(sprites[BOSSFACE]);
				break;
			case BOSSHEART:
				enemies[i]->Draw(sprites[BOSSHEART]);
				break;
			case WORM_BASE:
				enemies[i]->Draw(sprites[WORM_BASE]);
				break;
			case WORM_BODY:
				enemies[i]->Draw(sprites[WORM_BODY]);
				break;
			case WORM_HEAD:
				enemies[i]->Draw(sprites[WORM_HEAD]);
				break;
			case BLUE_BALL:
				enemies[i]->Draw(sprites[BLUE_BALL]);
				break;
			case ROCK:
				enemies[i]->Draw(sprites[ROCK]);
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
			enemies[i] = new Enemy_Big_Eye(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BIG_EYE;
			break;
		case ENEMY_TYPES::BIG_SHRIMP:
			//enemies[i] = new Enemy_Big_Shrimp(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BIG_SHRIMP;
			break;

		case ENEMY_TYPES::BLUE_MOUTH:
			enemies[i] = new Enemy_Blue_Mouth(info.x, info.y);
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
			enemies[i] = new Enemy_Yellow_Ball(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::YELLOW_BALL;
			break;
		case ENEMY_TYPES::BOSS1:
			enemies[i] = new Enemy_BossS4(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BOSS1;
			break;
		case ENEMY_TYPES::BOSSARM:
			enemies[i] = new Enemy_BossS4Arm(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BOSSARM;
			break;

		case ENEMY_TYPES::BOSSDISP:
			enemies[i] = new Enemy_BossS4Disp(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BOSSDISP;
			break;

		case ENEMY_TYPES::BOSSTENT:
			enemies[i] = new Enemy_BossS4Tenta(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BOSSTENT;
			break;

		case ENEMY_TYPES::BOSSFACE:
			enemies[i] = new Enemy_BossS4Face(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BOSSFACE;
			break;

		case ENEMY_TYPES::BOSSHEART:
			enemies[i] = new Enemy_BossS4Heart(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BOSSHEART;
			break;
		case ENEMY_TYPES::BLUE_BALL:
			enemies[i] = new Enemy_Blue_Ball(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::BLUE_BALL;
			break;
		case ENEMY_TYPES::ROCK:
			enemies[i] = new Enemy_Rock(info.x, info.y);
			enemies[i]->type = ENEMY_TYPES::ROCK;
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
			if (enemies[i]->live > 1) {
				enemies[i]->live--;
				App->audio->PlaySound(hit);
				enemies[i]->hit = true;
				enemies[i]->start_time = SDL_GetTicks();
			}
			else {
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
				case ENEMY_TYPES::YELLOW_BALL:
					App->audio->PlaySound(Yellowball_fx);
					break;
				case ENEMY_TYPES::BIG_EYE:
					App->audio->PlaySound(BigEye_fx);
					break;
				case ENEMY_TYPES::BOUNCER:
					App->audio->PlaySound(Bouncer_fx);
					break;
				case ENEMY_TYPES::BLUE_BALL:
					App->audio->PlaySound(Blue_Ball_fx);
					break;
				}
				enemies[i]->OnCollision(c2);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}