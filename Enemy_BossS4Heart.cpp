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

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 5, 5, 50, 60 }, COLLIDER_TYPE::COLLIDER_BOSS, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_BossS4Heart::Move()
{
	live = App->scene_stage4->lifes_Boss;
}
