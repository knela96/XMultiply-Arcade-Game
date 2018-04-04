#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMainMenu.h"
#include "ModuleSceneChoosePlayer.h"
#include "ModuleAudio.h"

ModuleSceneMainMenu::ModuleSceneMainMenu()
{
	// Background
	background = {0, 0, 384, 256};
}

ModuleSceneMainMenu::~ModuleSceneMainMenu()
{}

// Load assets
bool ModuleSceneMainMenu::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	App->audio->Enable();
	graphics = App->textures->Load("../Screenshots/Menu.png");
	return ret;
}

// Update: draw background
update_status ModuleSceneMainMenu::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 1.0f); // back of the room
	
	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_MainMenu, App->scene_choosePlayer, 2);
	}
	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneMainMenu::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading MainMenu stage");
	App->textures->Unload(graphics);
	App->audio->Disable();
	return true;
}