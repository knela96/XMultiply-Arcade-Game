#include "Application.h"
#include "Enemy_BossS4Face.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"


/* FALTA CAMBIAR EL SPRITE DEL DISPAR*/

Enemy_BossS4Face::Enemy_BossS4Face(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 5,5,56,50 });
	fly.PushBack({ 5,52,56,50 });
	fly.PushBack({ 66,5,56,50 });
	fly.PushBack({ 5,52,56,50 });
	fly.PushBack({ 5,5,56,50 });
	fly.speed = 0.05f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 5, 5, 52, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_BossS4Face::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	if (SDL_GetTicks() - shoot_delay >= 2000)
	{
		shoot_delay = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -2,0 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -2,-1 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -1,-2 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { 0,-2 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { 1,-2 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { 2,-1 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { 2 ,0 });


	}
}
