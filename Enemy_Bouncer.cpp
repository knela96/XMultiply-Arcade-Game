#include "Application.h"
#include "Enemy_Bouncer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Bouncer::Enemy_Bouncer(int x, int y) : Enemy(x, y)
{
	score = 400;
	fly.PushBack({ 10,17,40,23 });
	fly.PushBack({ 63,17,40,23 });
	fly.PushBack({ 63,46,40,23 });
	fly.PushBack({ 10,46,40,23 });
	fly.PushBack({ 63,46,40,23 });
	fly.PushBack({ 63,17,40,23 });
	fly.speed = 0.1f;

	animation = &fly;

	path->PushBack({ -1 , -1 }, 35, &fly);
	path->PushBack({ -1 , 0 }, 15, &fly);
	path->PushBack({ -1 , 1 }, 35, &fly);
	path->PushBack({ -1 , 0 }, 15, &fly);


	collider = App->collision->AddCollider({ 0, 0, 40, 23 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;

	live = 1;
}

void Enemy_Bouncer::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	if (SDL_GetTicks() - shoot_delay >= 1250)
	{
		shoot_delay = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x, position.y, COLLIDER_ENEMY_SHOT);
	}
}