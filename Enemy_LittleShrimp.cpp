#include "Application.h"
#include "Enemy_LittleShrimp.h"
#include "ModuleCollision.h"

Enemy_LittleShrimp::Enemy_LittleShrimp(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,48,32 });
	fly.PushBack({ 49,0,48,32 });
	fly.speed = 0.01f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 0, 0, 48, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_LittleShrimp::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
}
