#include "Application.h"
#include "Enemy_BossS4Heart.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleSceneStage4.h"


/* FALTA CAMBIAR EL SPRITE DEL DISPAR*/

Enemy_BossS4Heart::Enemy_BossS4Heart(int x, int y) : Enemy(x, y)
{
	score = 300000;

	fly.PushBack({ 220,50,50,60 });
	fly.PushBack({ 275,50,50,60 });
	fly.PushBack({ 160,50,60,60 });
	fly.PushBack({ 275,50,50,60 });

	fly.speed = 0.1f;


	animation = &fly;

	live = 20;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 5, 5, 50, 60 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;

	App->enemies->AddEnemy(BOSS1, 4950, 119, -1, true);
	App->enemies->AddEnemy(BOSSARM, 4930, 127, -1, true);


	App->enemies->AddEnemy(BOSSDISP, 4949, 119, -1, true);
	App->enemies->AddEnemy(BOSSTENT, 4956, 26, -1, true);
	App->enemies->AddEnemy(BOSSFACE, 4995, 119, -1, true);
}

void Enemy_BossS4Heart::Move()
{
}
