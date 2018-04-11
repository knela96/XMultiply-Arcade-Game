#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneStage2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneCongrats.h"
#include "ModulePlayer.h"
#include "ModuleEnemy.h"
#include "ModuleParticles.h"


ModuleSceneStage2::ModuleSceneStage2()
{
	//ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 512;
	ground.h = 512;

	// Background / sky
	background.x = 0;
	background.y = 0;
	background.w = 4608;
	background.h = 256;
}

ModuleSceneStage2::~ModuleSceneStage2()
{}

// Load assets
bool ModuleSceneStage2::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics = App->textures->Load("Assets/TileMap2.png");

	back = App->textures->Load("Assets/FirstLvlMap3.png");

	App->player->Enable();

	App->enemy->Enable();

	return ret;
}

bool ModuleSceneStage2::CleanUp()
{
	LOG("Cleaning backround assets");
	bool ret = true;

	App->textures->Unload(graphics);

	App->textures->Unload(back);

	App->player->Disable();

	App->enemy->Disable();

	return ret;

}
// Update: draw background
update_status ModuleSceneStage2::Update()
{
	--ScrollingOffset;
	if (ScrollingOffset < -512)
	{
		ScrollingOffset = 0;
	}


	App->render->Blit(back, ScrollingOffset, 0, &ground, 0.1f);
	App->render->Blit(back, ScrollingOffset + 512, 0, &ground, 0.1f);


	App->render->Blit(graphics, -50, -35, &background);

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_stage2, App->scene_congrats, 1);
	}



	return UPDATE_CONTINUE;
}