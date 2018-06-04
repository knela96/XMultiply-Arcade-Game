#include "Application.h"
#include "Enemy_BossS4.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"




Enemy_BossS4::Enemy_BossS4(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 14,35,145,104});
	fly.PushBack({ 14,140,145,104 });
	fly.PushBack({ 14,253,145,104 });
	
	fly.speed = 0.05f;

	animation = &fly;


	collider = App->collision->AddCollider({ 50, 50, 145, 54 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_BossS4::Move()
{
	
}
