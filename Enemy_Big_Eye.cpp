#include "Application.h"
#include "Enemy_Big_Eye.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"

Enemy_Big_Eye::Enemy_Big_Eye(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 11,10,70,68 });

	fly.PushBack({ 88,10,70,68});

	fly.PushBack({ 165,10,70,68 });


	fly.PushBack({ 11,160,70,68 });

	
	
	fly.PushBack({ 11,77,70,68 });

	fly.PushBack({ 88,77,70,68 });



	fly.PushBack({ 165,77,70,68 });
	fly.PushBack({ 11,10,70,68 });
	
	
	fly.speed = 0.065f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);

	collider = App->collision->AddCollider({ 13, 10, 70, 68 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_Big_Eye::Move()
{
	position = original_position + path->GetCurrentPosition(&animation);
	if (SDL_GetTicks() - shoot_delay >= 1000)
	{
		shoot_delay = SDL_GetTicks();
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2, position.y + fly.frames->h / 2, COLLIDER_ENEMY_SHOT, { -3,0});
		
	}
}
