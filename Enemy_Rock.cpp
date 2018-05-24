#include "Application.h"
#include "Enemy_Rock.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"

Enemy_Rock::Enemy_Rock(int x, int y, bool move_up) : Enemy(x, y)
{
	this->move_up = move_up;

	collider = App->collision->AddCollider({ 0, 0, 48, 45 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}


//MAKE IT CHANGE DIRECTION ON CONTACT WITH A WALL

/*void Enemy_Rock::Move()
{
	
}*/
