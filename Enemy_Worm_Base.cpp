#include "Application.h"
#include "Enemy_Worm_Base.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Worm_Base::Enemy_Worm_Base(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,5,48,48 });
	fly.PushBack({ 49,5,50,48 });
	fly.PushBack({ 112,5,50,48 });
	fly.speed = 0.1f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 0, 0, 31, 23 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_Worm_Base::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
};
