#include "Application.h"
#include "Enemy_BrownWorm.h"
#include "ModuleCollision.h"

Enemy_BrownWorm::Enemy_BrownWorm(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,16,16 }); 
	fly.PushBack({ 17,0,33,16 });
	fly.PushBack({ 34,0,50,16 });
	animation = &fly;

	path->PushBack({ -1 , 0 }, 2, &fly);
	
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	original_position.x = x;
	original_position.y = y;
}

void Enemy_BrownWorm::Move()
{
	position = original_position + path->GetCurrentPosition();
}
