#include "Application.h"
#include "Enemy_BossS4Disp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneStage4.h"
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

	fly.PushBack({ 136,92,35,42 });

	//2 phase
	fly.PushBack({ 52,52,46,42 });

	fly.PushBack({ 102,52,39,42 });

	fly.PushBack({ 2,52,46,46 });

	fly.PushBack({ 135,52,35,42 });

	fly.speed = 3.0f;

		
	animation = &fly;


	live = 40;

	path->PushBack({ 0 , 0 }, 1, &fly);


	collider = App->collision->AddCollider({ 10, 10, 100, 28 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_position.x = 0;
	original_position.y = 0;
}

void Enemy_BossS4Disp::Move()
{
	if (App->scene_stage4->boss_phase2) {
		switch (App->scene_stage4->current_frame) {
		case 0:
			original_position = { 4949, 117 };
			break;
		case 1:
			original_position = { 4946, 105 };
			break;
		case 2:
			original_position = { 4946, 95 };
			break;
		case 3:
			original_position = { 4946, 83 };
			break;
		case 4:
			original_position = { 4946, 75 };
			break;
		case 5:
			original_position = { 4951, 70 };
			break;
		case 6:
			original_position = { 4961, 45 };
			break;
		case 7:
			original_position = { 4991, 30 };
			break;
		default:
			original_position = { 0, 0 };
			break;
		}

		position = original_position + path->GetCurrentPosition(&animation);
	}
	else {
		int height = SCREEN_HEIGHT / 4;
		iPoint pos = App->player->position;
		if (pos.y > 0 && pos.y < height * 1) {
			original_position = { 4946, 82 };
		}
		else if (pos.y > height * 1 && pos.y < height * 2) {
			original_position = { 4943, 95 };
		}
		else if (pos.y > height * 2 && pos.y < height * 3) {
			original_position = { 4946, 105 };
		}
		else if (pos.y > height * 3 && pos.y < height * 4) {
			original_position = { 4949, 119 };
		}
		double angle = atan2(pos.y - original_position.y, pos.x - original_position.x);
		if (angle < PI / 2)
			angle = 5 / 3 * PI;


		position = original_position + path->GetCurrentPosition(&animation);


		if (SDL_GetTicks() - shoot_delay >= 2000)
		{
			shoot_delay = SDL_GetTicks();
			App->particles->AddParticle(App->particles->Stage4Boss_shoot, original_position.x, original_position.y, COLLIDER_ENEMY_SHOT, { (float)(3 * cos(angle)),(float)(5 * sin(angle + 0.52)) });
			App->particles->AddParticle(App->particles->Stage4Boss_shoot, original_position.x, original_position.y, COLLIDER_ENEMY_SHOT, { (float)(3 * cos(angle)),(float)(5 * sin(angle)) });
			App->particles->AddParticle(App->particles->Stage4Boss_shoot, original_position.x, original_position.y, COLLIDER_ENEMY_SHOT, { (float)(3 * cos(angle)),(float)(5 * sin(angle - 0.52)) });


		}
	}
	
}
