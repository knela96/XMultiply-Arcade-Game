#include "Application.h"
#include "Enemy_LittleShrimp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_LittleShrimp::Enemy_LittleShrimp(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,48,32 });
	fly.PushBack({ 49,0,48,32 });
	fly.speed = 0.2f;

	animation = &fly;

	path->PushBack({ -1 , -1 }, 35, &fly);
	path->PushBack({ -1 , 0 }, 15, &fly);
	path->PushBack({ -1 , 1 }, 35, &fly);
	path->PushBack({ -1 , 0 }, 15, &fly);
	

	collider = App->collision->AddCollider({ 0, 0, 48, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_LittleShrimp::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	if (SDL_GetTicks()-shoot_delay >= 1250) 
	{
		shoot_delay = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x, position.y, COLLIDER_ENEMY_SHOT, { -3,1 });
	}
}