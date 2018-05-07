#include "Application.h"
#include "Enemy_Yellow_Ball.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Yellow_Ball::Enemy_Yellow_Ball(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,68,60 });
	fly.PushBack({ 0,75,68,125 });
	fly.PushBack({ 0,140,68,190 });
	fly.speed = 0.1f;

	animation = &fly;

	
	path->PushBack({ -1 , 0 }, 15, &fly);
	
	


	collider = App->collision->AddCollider({ 0, 0, 48, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_Yellow_Ball::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
}