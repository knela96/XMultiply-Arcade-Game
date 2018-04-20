#include "Application.h"
#include "Enemy_BrownWorm.h"
#include "ModuleCollision.h"

Enemy_BrownWorm::Enemy_BrownWorm(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,32,32 });
	fly.PushBack({ 32,0,32,32 });
	fly.PushBack({ 64,0,32,32 });
	fly.speed = 0.01f;
	
	animation = &fly;

	
	path->PushBack({ -1 , 0 }, 10, &fly);
	path->PushBack({ -1 , -1 }, 10, &fly);
	path->PushBack({ 0 , -1 }, 10, &fly);
	path->PushBack({ -1 , -1 }, 10, &fly);
	path->PushBack({ -1 , 0 }, 10, &fly);
	path->PushBack({ -1 , 1 }, 10, &fly);
	path->PushBack({ 0 , 1 }, 10, &fly);
	path->PushBack({ -1 , 1 }, 10, &fly);
	
	collider = App->collision->AddCollider({ 5, 5, 25, 25 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	original_position.x = x;
	original_position.y = y;
}

void Enemy_BrownWorm::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	
}
