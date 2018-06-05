#include "Application.h"
#include "Enemy_Blue_Ball.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Blue_Ball::Enemy_Blue_Ball(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,3,32,14 });
	fly.PushBack({ 36,3,68,16 });
	fly.PushBack({ 76,0,103,20 });
	fly.PushBack({ 22,27,46,49 });
	fly.PushBack({ 52,24,77,49 });
	fly.speed = 0.1f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 0, 0, 32, 25 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

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
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { 0,3 }, 1);
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { 1,1 });
		
	}
}
