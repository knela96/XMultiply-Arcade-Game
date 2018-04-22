#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMainMenu.h"
#include "ModuleSceneCongrats.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleSceneStage1.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "ModuleFonts.h"

ModuleSceneCongrats::ModuleSceneCongrats()
{
	// Background
	background = { 0, 0, 384, 256 };
}

ModuleSceneCongrats::~ModuleSceneCongrats()
{}

// Load assets
bool ModuleSceneCongrats::Start()
{
	
	App->player->Enable();
	App->particles->Enable();
	App->font->Enable();

	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Assets/Credits.png");
	return ret;
}

// Update: draw background
update_status ModuleSceneCongrats::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 1.0f);
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_congrats, App->scene_MainMenu, 2);
	}
	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneCongrats::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading MainMenu stage");
	App->textures->Unload(graphics);
	graphics = nullptr;
	return true;
}