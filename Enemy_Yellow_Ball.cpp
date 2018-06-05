#include "Application.h"
#include "Enemy_Yellow_Ball.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Yellow_Ball::Enemy_Yellow_Ball(int x, int y) : Enemy(x, y)
{
	score = 200;
	fly.PushBack({ 10,5,70,30 });
	fly.PushBack({ 10,40,70,30 });
	fly.PushBack({ 10,79,70,32 });
	fly.speed = 0.13f;

	animation = &fly;

	
	path->PushBack({ -1 , 0 }, 15, &fly);
	

	collider = App->collision->AddCollider({ 10, 0, 40, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_Yellow_Ball::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
}