#include "Application.h"
#include "Enemy_PowerupShip.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

Enemy_PowerupShip::Enemy_PowerupShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 68, 11,28,18 });
	fly.PushBack({ 68, 11,28,18 });
	fly.speed = 0.05f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 0, 0, 48, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_PowerupShip::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
}

void Enemy_PowerupShip::OnCollision(Collider* collider)
{
	
	App->particles->AddParticle(App->particles->Powerup, position.x, position.y,COLLIDER_POWERUP);
}
