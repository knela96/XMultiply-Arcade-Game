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
#include "ModuleProjectile.h"

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

	App->enemy->Enable();

	App->projectile->Enable();

	graphics = App->textures->Load("Assets/TileMap.png");

	back = App->textures->Load("Assets/FirstLvlMap3.png");

	
	return ret;
}

bool ModuleSceneStage1::CleanUp()
{
	LOG("Cleaning backround assets");
	bool ret = true;

	App->textures->Unload(graphics);
	App->textures->Unload(back);
	App->player->Disable();
	App->enemy->Disable();
	App->projectile->Disable();
	return ret;

}
// Update: draw background
update_status ModuleSceneStage1::Update()
{
	--ScrollingOffset;
	if (ScrollingOffset < -512)
	{
		ScrollingOffset = 0;
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