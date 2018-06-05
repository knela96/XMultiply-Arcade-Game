#include "Application.h"
#include "Enemy_BossS4Face.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include"ModuleSceneStage4.h"
#include "SDL/include/SDL_timer.h"


/* FALTA CAMBIAR EL SPRITE DEL DISPAR*/

Enemy_BossS4Face::Enemy_BossS4Face(int x, int y) : Enemy(x, y)
{

	fly.PushBack({360,157,56,50 });
	/*
	fly.PushBack({ 305,155,52,50 });
	fly.PushBack({ 255,155,56,50 });
	fly.PushBack({ 210,155,56,50 });

	fly.PushBack({ 370,105,56,50 });

	fly.PushBack({ 320,105,56,50 });
	fly.PushBack({ 270,105,56,50 });
	fly.PushBack({ 215,105,56,50 });
	fly.PushBack({ 160,105,56,50 });*/

	fly.speed = 0.08f;

	fly.loop = false;

	animation = &fly;

	//path to do

	path->PushBack({ -2 , -1 }, 40, &fly);
	//path->PushBack({ -2 , 0 }, 80, &fly);

	up = false;

	collider = App->collision->AddCollider({ 5, 5, 56, 50 }, COLLIDER_TYPE::COLLIDER_BOSS, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_BossS4Face::Move()
{
	live = App->scene_stage4->lifes_Boss;
	if (App->scene_stage4->move_head) {
		if (position.x <= 4800) {
			original_position.x = 4800;

			if (SDL_GetTicks() - shoot_delay >= 100 && SDL_GetTicks() - move_delay <= 400)
			{
				shoot_delay = SDL_GetTicks();
				App->particles->AddParticle(App->particles->shrimp_shoot, original_position.x, original_position.y + fly.frames->h / 2, COLLIDER_BOSS, { -2,-0.5f });
				App->particles->AddParticle(App->particles->shrimp_shoot, original_position.x, original_position.y + fly.frames->h / 2, COLLIDER_BOSS, { -2,0.5f });
			}
			if(SDL_GetTicks() - move_delay > 400){
				if (original_position.y > 50 && up)
					original_position.y--;
				else if (original_position.y < SCREEN_HEIGHT - 100 && !up)
					original_position.y++;

				if (original_position.y <= 50 || original_position.y >= SCREEN_HEIGHT - 100)
					up = !up;

				position = original_position + newpath->GetCurrentPosition(&animation);
			}
			if(SDL_GetTicks() - move_delay > 1500)
				move_delay = SDL_GetTicks();
		}
		else {
			position = original_position + path->GetCurrentPosition(&animation);
			if (position.x <= 4800) {
				original_position.x = 4800;
				original_position.y = 35;
			}
		}
	}
}
