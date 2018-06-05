#include "Application.h"
#include "Enemy_BossS4Tenta.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneStage4.h"
#include "SDL/include/SDL_timer.h"


/* FALTA CAMBIAR EL SPRITE DEL DISPAR*/

Enemy_BossS4Tenta::Enemy_BossS4Tenta(int x, int y) : Enemy(x, y)
{
	/*
	fly.PushBack({ 185,140,141,125 });
	fly.PushBack({ 185,263,141,125 });
	fly.PushBack({ 185,387,141,125 });
	
	fly.PushBack({ 346,16,141,125 });
	fly.PushBack({ 346,137,141,125 });
	fly.PushBack({ 346,260,141,125 });
	fly.PushBack({ 346,383,141,125 });
	fly.PushBack({ 16,383,141,125 });
	fly.PushBack({ 185,13,141,125 });
	*/

	//anticlockwise
	fly.PushBack({ 16,383,141,125 });
	fly.PushBack({ 346,383,141,125 });
	fly.PushBack({ 346,260,141,125 });
	fly.PushBack({ 346,137,141,125 });
	fly.PushBack({ 346,16,141,125 });
	fly.PushBack({ 185,387,141,125 });
	fly.PushBack({ 185,263,141,125 });
	fly.PushBack({ 185,140,141,125 });

	fly.speed = 0.05f;

	spawn_head.PushBack({ 185,140,141,125 });
	spawn_head.PushBack({ 185,263,141,125 });
	spawn_head.PushBack({ 185,387,141,125 });
	spawn_head.PushBack({ 346,16,141,125 });
	spawn_head.PushBack({ 346,137,141,125 });
	spawn_head.PushBack({ 346,260,141,125 });
	spawn_head.PushBack({ 346,383,141,125 });
	spawn_head.PushBack({ 16,383,141,125 });
	spawn_head.speed = 0.05f;

	animation = &fly;

	path->PushBack({ 0 , 0 }, 2, animation);

	//collider = App->collision->AddCollider({ 5, 5, 52, 48 }, COLLIDER_TYPE::COLLIDER_BOSS, (Module*)App->enemies);

	original_position.x = x;
	original_position.y = y;
}

void Enemy_BossS4Tenta::Move()
{
	live = App->scene_stage4->lifes_Boss;

	if (App->scene_stage4->boss_phase2 == false ) {
		if (SDL_GetTicks() - App->scene_stage4->aux_time > 5000 && App->scene_stage4->move_head != true) {
			spawn_head.Reset();
			animation = &spawn_head;
			animation->setFrame(7 - App->scene_stage4->current_frame);
			App->scene_stage4->boss_phase2 = true;
		}
		else {
			int height = SCREEN_HEIGHT / 4;
			int pos = App->player->position.y;
			if (pos < height * 1) {
				animation->setFrame(App->scene_stage4->current_frame = 4);
			}
			else if (pos > height * 1 && pos < height * 2) {
				animation->setFrame(App->scene_stage4->current_frame = 5);
			}
			else if (pos > height * 2 && pos < height * 3) {
				animation->setFrame(App->scene_stage4->current_frame = 6);
			}
			else if (pos > height * 3 && pos < height * 4) {
				animation->setFrame(App->scene_stage4->current_frame = 7);
			}


			position = original_position + path->GetCurrentPosition(&animation);
			if (SDL_GetTicks() - shoot_delay >= 2000)
			{
				shoot_delay = SDL_GetTicks();
				App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_BOSS, { -2,0 });
				App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_BOSS, { -2,-1 });
				App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_BOSS, { -1,-2 });
				App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_BOSS, { 0,-2 });
				App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_BOSS, { 1,-2 });
				App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_BOSS, { 2,-1 });
				App->particles->AddParticle(App->particles->shrimp_shoot, position.x + fly.frames->w / 2.3, position.y + fly.frames->h / 2, COLLIDER_BOSS, { 2 ,0 });
			}
		}

		position = original_position + path->GetCurrentPosition(&animation);
	}
	else if(App->scene_stage4->boss_phase2 == true){
		animation = &spawn_head;
		App->scene_stage4->current_frame = animation->getFrame();
		if (App->scene_stage4->current_frame == 7) {
			animation->speed = 0.0f;
			App->scene_stage4->move_head = true;
			spawn_head.Reset();
			animation = &fly;
			App->scene_stage4->boss_phase2 = false;
		}
	}
	
}
