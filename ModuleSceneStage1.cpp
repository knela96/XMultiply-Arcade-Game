#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneStage1.h"
#include "ModuleSceneStage2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"

ModuleSceneStage1::ModuleSceneStage1()
{
	//ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 512;
	ground.h = 512;

	// Background / sky
	background.x = 0;
	background.y = 1;
	background.w = 4961;
	background.h = 513;	
}

ModuleSceneStage1::~ModuleSceneStage1()
{}

// Load assets
bool ModuleSceneStage1::Start()
{
	LOG("Loading background assets");

	bool ret = true;


	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemy->Enable();
	
	graphics = App->textures->Load("Assets/TileMap1.png");

	back = App->textures->Load("Assets/FirstLvlMap3.png");

	// Colliders ---
	App->collision->AddCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1380, 0, 100, 100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1380, 140, 100, 120 }, COLLIDER_WALL);
	
	return ret;
}

bool ModuleSceneStage1::CleanUp()
{
	LOG("Cleaning backround assets");
	bool ret = true;

	App->textures->Unload(graphics);
	App->textures->Unload(back);
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();
	//App->enemy->Disable();

	App->render->camera.x = App->render->camera.y = 0;
	return ret;

}
// Update: draw background
update_status ModuleSceneStage1::Update()
{
	if (!App->player->dead) {
		--ScrollingOffset;
		if (ScrollingOffset < -512)
		{
			ScrollingOffset = 0;
		}
	}


	App->render->Blit(back, ScrollingOffset, 0, &ground, 0.1f);

	App->render->Blit(back, ScrollingOffset + 512, 0, &ground, 0.1f);


	App->render->Blit(graphics, 0, 0, &background);


	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_stage1, App->scene_stage2, 1);
	}
	
	

	return UPDATE_CONTINUE;
}