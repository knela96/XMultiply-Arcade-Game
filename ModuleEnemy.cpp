#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include <time.h>
#include <stdlib.h>


ModuleEnemy::ModuleEnemy() {


	
	srand(time(NULL));


	anim1.PushBack({ 0, 0, 43, 32 });
	anim1.PushBack({ 44, 0, 43, 32 });
	anim1.speed = 0.05f;

	animpower.PushBack({68, 11,28,18 });
	animpower.PushBack({ 68, 11,28,18 });
	animpower.speed = 0.05f;

	for (int i = 0; i < 30; ++i) {
		enemies[i].collider = nullptr;
		// forward animation 
		enemies[i].forward = anim1;	
	}
	for (int i = 0; i < 15; ++i) {
		Powerups[i].collider = nullptr;
		Powerups[i].forward = animpower;

	}
}

// Destructor
ModuleEnemy::~ModuleEnemy() {}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading enemy textures");
	bool ret = true;
	for (int i = 0; i < 30; ++i) {
		enemies[i].graphics = App->textures->Load("Assets/littleshrimp.png"); // arcade version
		
	}
	for (int i = 0; i < 15; ++i) {
		Powerups[i].graphics = App->textures->Load("Assets/Sprites/PowerUp/PowerUp.png");
	}
	return ret;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading Enemy assets");
	for (int i = 0; i < 30; ++i) {
		if (enemies[i].collider != nullptr) {
			App->textures->Unload(enemies[i].graphics);
			enemies[i].collider = nullptr;
		}

	}
	for (int i = 0; i < 15; ++i) {
	if (Powerups[i].collider != nullptr) {
		App->textures->Unload(Powerups[i].graphics);
		Powerups[i].collider = nullptr;
		}
	}

	return true;
}

// Called every draw update
update_status ModuleEnemy::Update()
{
	start_time = (Uint32 *)SDL_GetTicks();


	for (int i = 0; i < 30; ++i) {
		
		Animation* current_animation = &enemies[i].forward;
		
		if ((start_time - spawn_delay > 200) && enemies[i].collider == nullptr) {
			spawn_delay = start_time;

			enemies[i].collider = App->collision->AddCollider({ enemies[i].position.x, enemies[i].position.y, 43, 32 }, COLLIDER_ENEMY, this);
			enemies[i].dead = false;
			enemies[i].position.x = SCREEN_WIDTH - App->render->camera.x;
			enemies[i].position.y = rand() % (SCREEN_HEIGHT-80)+40;
		}

		if (enemies[i].collider != nullptr && !enemies[i].dead) {
			enemies[i].position.x -= 1;
			enemies[i].collider->SetPos(enemies[i].position.x, enemies[i].position.y);
			App->render->Blit(enemies[i].graphics, enemies[i].position.x, enemies[i].position.y, &current_animation->GetCurrentFrame());
		}
	/*	
		if ((start_time - spawn_delay > 200) && Powerups[i].collider == nullptr) {
			

			Powerups[i].collider = App->collision->AddCollider({ Powerups[i].position.x, Powerups[i].position.y, 43, 32 }, COLLIDER_ENEMY, this);
			Powerups[i].dead = false;
			Powerups[i].position.x = SCREEN_WIDTH - App->render->camera.x;
			Powerups[i].position.y = (SCREEN_HEIGHT - SCREEN_HEIGHT / 2);
		}
		*/
		
	}
	

	return update_status::UPDATE_CONTINUE;
}


void ModuleEnemy::OnCollision(Collider* collider1, Collider* collider2){
	for (int i = 0; i < 30; ++i) {
		if ( enemies[i].collider != nullptr && enemies[i].collider == collider1 && collider2->type == COLLIDER_PLAYER_SHOT) {
			App->particles->AddParticle(App->particles->explosion, collider1->rect.x, collider1->rect.y, COLLIDER_NONE);
			enemies[i].dead = true;
			enemies[i].collider->to_delete = true;
		}
	}
	
}
