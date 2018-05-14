#include "Application.h"
#include "Enemy_Blue_Mouth.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Blue_Mouth::Enemy_Blue_Mouth(int x, int y) : Enemy(x, y)
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

void Enemy_Blue_Mouth::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	if (SDL_GetTicks() - shoot_delay >= 1000)
	{
		shoot_delay = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { -3,0 });

	}
}
