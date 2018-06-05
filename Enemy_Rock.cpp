#include "Application.h"
#include "Enemy_Rock.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Rock::Enemy_Rock(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,5,48,48 });
	fly.speed = 0.1f;

	animation = &fly;

	path->PushBack({ 0 , -1 }, 89, &fly);
	path->PushBack({ 0 , 1 }, 89, &fly);

	collider = App->collision->AddCollider({ 0, 0, 48, 48 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->scene_stage4);

	original_position.x = x;
	original_position.y = y;

	
}

void Enemy_Rock::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	
}
