#include "Application.h"
#include "Enemy_BossS4.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneStage4.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleSceneStage4.h"




Enemy_BossS4::Enemy_BossS4(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 14,35,145,104});
	fly.PushBack({ 14,140,145,104 });
	fly.PushBack({ 14,253,145,104 });
	
	fly.speed = 0.0f;

	animation = &fly;

	immortal = true;
	live = 40;

	collider = App->collision->AddCollider({ 50, 150, 145, 70 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	offset.y = 40;
	original_position.x = x;
	original_position.y = y;
}

void Enemy_BossS4::Move()
{
	if (App->scene_stage4->lifes_Boss > 30) {
		animation->setFrame(0);
	}
	else if (App->scene_stage4->lifes_Boss > 20) {
		animation->setFrame(1);
	}
	else {
		animation->setFrame(2);
	}
	position = original_position + path->GetCurrentPosition(&animation);
}
