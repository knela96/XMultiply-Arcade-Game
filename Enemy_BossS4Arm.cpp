#include "Application.h"
#include "Enemy_BossS4Arm.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"


/* FALTA CAMBIAR EL SPRITE DEL DISPAR*/

Enemy_BossS4Arm::Enemy_BossS4Arm(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 8,15,156,130 });
	fly.PushBack({ 170,15,156,130 });
	fly.PushBack({ 330,15,156,130 });

	fly.PushBack({ 5,170,156,130 });
	fly.PushBack({ 158,170,156,130 });
	fly.PushBack({ 310,168,156,130 });

	fly.PushBack({ 60,325,156,130 });

	fly.PushBack({260,325,156,130 });
	
	fly.PushBack({ 60,325,156,130 });
	fly.PushBack({ 310,168,156,130 });
	fly.PushBack({ 158,170,156,130 });
	fly.PushBack({ 5,170,156,130 });
	fly.PushBack({ 330,15,156,130 });
	fly.PushBack({ 170,15,156,130 });


	fly.speed = 0.15f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	live = 40;

	original_position.x = x;
	original_position.y = y;
}

void Enemy_BossS4Arm::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	
}
