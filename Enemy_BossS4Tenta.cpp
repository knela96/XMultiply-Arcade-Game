#include "Application.h"
#include "Enemy_BossS4Tenta.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"


/* FALTA CAMBIAR EL SPRITE DEL DISPAR*/

Enemy_BossS4Tenta::Enemy_BossS4Tenta(int x, int y) : Enemy(x, y)
{
	
	fly.PushBack({ 185,140,141,125 });
/*	fly.PushBack({ 185,263,141,125 });
	fly.PushBack({ 185,387,141,125 });
	
	fly.PushBack({ 346,16,141,125 });
	fly.PushBack({ 346,137,141,125 });
	fly.PushBack({ 346,260,141,125 });
	fly.PushBack({ 346,383,141,125 });
	
	fly.PushBack({ 16,383,141,125 });
	fly.PushBack({ 185,13,141,125 });

	//anticlockwise
	fly.PushBack({ 16,383,141,125 });
	fly.PushBack({ 346,383,141,125 });
	fly.PushBack({ 346,260,141,125 });
	fly.PushBack({ 346,137,141,125 });
	fly.PushBack({ 346,16,141,125 });
	fly.PushBack({ 185,387,141,125 });
	fly.PushBack({ 185,263,141,125 });*/

	fly.speed = 0.05f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 5, 5, 52, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_BossS4Tenta::Move()
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
