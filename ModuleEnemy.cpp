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


	anim.PushBack({ 0, 0, 43, 32 });
	anim.PushBack({ 44, 0, 43, 32 });
	anim.speed = 0.05f;

	for (int i = 0; i < 30; ++i) {
		enemies[i].collider = nullptr;
		// forward animation 
		enemies[i].forward = anim;
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
	return ret;
}

// Called every draw update
update_status ModuleEnemy::Update()
{
	start_time = (Uint32 *)SDL_GetTicks();


	for (int i = 0; i < 30; ++i) {
		
		Animation* current_animation = &enemies[i].forward;

		if (enemies[i].position.x <= 0) {
			enemies[i].collider = nullptr;
		}

		if ((start_time - spawn_delay > 200) && enemies[i].collider == nullptr) {
			spawn_delay = start_time;

           //HEY ERIC EN TEORIA AIXO ES UN INIT DEL COLLIDER PER CADA ENEMIC//
			enemies[i].collider = App->collision->AddCollider({ enemies[i].position.x, enemies[i].position.y, 48, 16 }, COLLIDER_ENEMY, this);
			
			enemies[i].position.x = SCREEN_WIDTH;
			enemies[i].position.y = rand() % (SCREEN_HEIGHT-40)+30;
		}
		if (enemies[i].collider != nullptr) {
			enemies[i].position.x -= 1;
			enemies[i].collider->SetPos(enemies[i].position.x, enemies[i].position.y);
			App->render->Blit(enemies[i].graphics, enemies[i].position.x, enemies[i].position.y, &current_animation->GetCurrentFrame());
		}
		
		
	}
	

	return update_status::UPDATE_CONTINUE;
}


void ModuleEnemy::OnCollision(Collider* collider1, Collider* collider2){
	if (collider2->type == COLLIDER_PLAYER_SHOT) {
		App->particles->AddParticle(App->particles->explosion, collider2->rect.x, collider2->rect.y, COLLIDER_NONE);
	}
}
