#include "Application.h"
#include "Enemy_BlueSentinel.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_BlueSentinel::Enemy_BlueSentinel(int x, int y) : Enemy(x, y)
{
	score = 5000;
	fly.PushBack({ 2 ,3 ,29,30 });
	fly.speed = 0.2f;

	animation = &fly;

	path->PushBack({ -1 , -1 }, 35, &fly);
	path->PushBack({ -1 , 0 }, 15, &fly);
	path->PushBack({ -1 , 1 }, 35, &fly);
	path->PushBack({ -1 , 0 }, 15, &fly);


	collider = App->collision->AddCollider({ 0, 0, 29, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;


	live = 2;
}

void Enemy_BlueSentinel::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	if (SDL_GetTicks() - shoot_delay >= 1250)
	{
		shoot_delay = SDL_GetTicks();
		App->particles->AddParticle(App->particles->bluesentinelshot, position.x, position.y, COLLIDER_ENEMY_SHOT, { 1, 2 });
		App->particles->AddParticle(App->particles->bluesentinelshot, position.x, position.y, COLLIDER_ENEMY_SHOT, { 1,-2 });

	}
}