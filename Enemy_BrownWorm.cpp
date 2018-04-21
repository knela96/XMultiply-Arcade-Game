#include "Application.h"
#include "Enemy_BrownWorm.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"

Enemy_BrownWorm::Enemy_BrownWorm(int x, int y, bool move_up) : Enemy(x, y)
{
	fly.PushBack({ 0,0,32,32 });
	fly.PushBack({ 32,0,32,32 });
	fly.PushBack({ 64,0,32,32 });
	fly.speed = 0.01f;
	
	animation = &fly;
	
	this->move_up = move_up;

	collider = App->collision->AddCollider({ 5, 5, 25, 25 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	original_position.x = x;
	original_position.y = y;
}

void Enemy_BrownWorm::Move()
{
	angle += 0.08f;

	if (original_position.x - 118 == position.x) {
		_return = true;
	}

	if (move_up) position.y = original_position.y + sinf(angle) *1.9f * radius;
	else position.y = original_position.y + sinf(-angle) * 1.9f * radius;

	if (!_return) {
		position.x -= 1;
	}
	else {
		position.x += 3;
	}

}
