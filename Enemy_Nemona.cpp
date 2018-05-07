#include "Application.h"
#include "Enemy_Nemona.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Nemona::Enemy_Nemona(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,5,48,48 });
	fly.PushBack({ 49,5,50,48 });
	fly.PushBack({ 112,5,50,48 });
	fly.speed = 0.1f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 0, 0, 48, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_Nemona::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	if (SDL_GetTicks() - shoot_delay >= 2000)
	{
		shoot_delay = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w/2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { -3,-0.5 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { -2,-1 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { 0,-3 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { 2,-1 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { 3,-0.5 });
	}
}
