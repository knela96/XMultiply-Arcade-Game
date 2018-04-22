#include "Application.h"
#include "Enemy_PowerupShip.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePowerUp.h"


Enemy_PowerupShip::Enemy_PowerupShip(int x, int y, uint PU) : Enemy(x, y)
{
	fly.PushBack({ 68, 11,28,18 });
	fly.PushBack({ 68, 11,28,18 });
	fly.speed = 0.05f;

	animation = &fly;

	path->PushBack({ -1 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 0, 0, 30, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;

	switch (PU)
	{
	case 1: 
		p = App->powerup->AddPowerUp(App->powerup->tentacles_powerup, position.x + 2, position.y + 10, COLLIDER_POWERUP);
		break;
	case 2: 
		p = App->powerup->AddPowerUp(App->powerup->bomb_powerup, position.x + 2, position.y + 10, COLLIDER_POWERUP); 
		break;
	case 3:
		p= App->powerup->AddPowerUp(App->powerup->speed_powerup, position.x + 2, position.y + 10, COLLIDER_POWERUP);
	}
}

void Enemy_PowerupShip::Move()
{
	//position = original_position + path->GetCurrentPosition(&animation);
	position.x = position.x -0.7f;
}

void Enemy_PowerupShip::OnCollision(Collider* collider)
{
	if (p != nullptr)p->enabled = true;

}
