#include "Application.h"
#include "Enemy_Blue_Ball.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Blue_Ball::Enemy_Blue_Ball(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 3,87,35,26 });
	fly.PushBack({ 3,55,35,22 });
	fly.PushBack({ 45,6,35,22 });
	fly.PushBack({ 2,31,35,22 });
	fly.PushBack({ 3,6,35,22 });
	fly.PushBack({ 2,31,35,22 });
	fly.PushBack({ 45,6,35,22 });
	fly.PushBack({ 3,55,35,22 });

	fly.speed = 0.1f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 0, 0, 32, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;

	live = 2;
}

void Enemy_Blue_Ball::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	if (SDL_GetTicks() - shoot_delay >= 2000)
	{
		shoot_delay = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { -1,1 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { 1,1 });
		
	}
}
