#include "Application.h"
#include "Enemy_Worm_Body.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Worm_Body::Enemy_Worm_Body(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,5,48,48 });
	fly.PushBack({ 49,5,50,48 });
	fly.PushBack({ 112,5,50,48 });
	fly.speed = 0.1f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_Worm_Body::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
};
