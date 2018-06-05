#include "Application.h"
#include "Enemy_BossS4Disp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_timer.h"


/* FALTA CAMBIAR EL SPRITE DEL DISPAR*/

Enemy_BossS4Disp::Enemy_BossS4Disp(int x, int y) : Enemy(x, y)
{
	//1 phase

	fly.PushBack({ 100,13,42,40 });

	fly.PushBack({ 2,13,46,40 });
	
	fly.PushBack({ 48,13,46,40 });

	fly.PushBack({ 133,13,46,40 });
	
	
	
	//2 phase
	fly.PushBack({ 52,52,46,42 });

	fly.PushBack({ 102,52,39,42 });

	fly.PushBack({ 2,52,46,46 });

	fly.PushBack({ 135,52,35,42 });


	//3 phase

	fly.PushBack({ 52,92,46,42 });

	fly.PushBack({ 102,92,39,42 });

	fly.PushBack({ 2,92,46,46 });

	fly.PushBack({ 136,92,36,42 });

	//2 phase
	fly.PushBack({ 52,52,46,42 });

	fly.PushBack({ 102,52,39,42 });

	fly.PushBack({ 2,52,46,46 });

	fly.PushBack({ 135,52,35,42 });


	//Particle pushback

	//Phase 1 BOSS SHOOT 
	
	//	fly.PushBack({ 50,135,46,40 });

	//	fly.PushBack({ 101,135,38,42 });

	//	fly.PushBack({ 2,135,46,46 });

	//	fly.PushBack({ 136,135,36,42 });

	
	// Phase 2 Boss shoot to repeat

	//	fly.PushBack({ 50,178,46,40 });

	//	fly.PushBack({ 100,178,37,42 });

	//	fly.PushBack({ 2,178,46,46 });

	//	fly.PushBack({ 135,178,36,42 });

	// Phase 3 Boss shoot

	//	fly.PushBack({ 50,222,46,40 });

	//	fly.PushBack({ 100,222,36,42 });

	//	fly.PushBack({ 2,222,46,46 });

	//	fly.PushBack({ 135,222,35,42 });

	// Phase 2 Boss shoot to repeat

	//	fly.PushBack({ 50,178,46,40 });

	//	fly.PushBack({ 100,178,37,42 });

	//	fly.PushBack({ 2,178,46,46 });

	//	fly.PushBack({ 135,178,36,42 });


	fly.speed = 0.08f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, &fly);
	/*path->PushBack({ 1 , 2 }, 2, &fly);
	path->PushBack({ 1.8 , 3 }, 2, &fly);
	path->PushBack({ 2.5 , 3.5 }, 2, &fly);
	path->PushBack({ 4 , 4 }, 2, &fly);*/
	

	collider = App->collision->AddCollider({ 5, 5, 52, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_BossS4Disp::Move()
{
	int i = 1;
	position = original_position + path->GetCurrentPosition(&animation);
	if (SDL_GetTicks() - shoot_delay >= 2000)
	{
		shoot_delay = SDL_GetTicks();
		

	
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -3,-1 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -2,-1 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -1,-2 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -2,0 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -1, 2 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -2, 1 });
		App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_ENEMY, { -3, 1 });
		

	}
}
