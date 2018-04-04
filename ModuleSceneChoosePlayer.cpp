#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneChoosePlayer.h"
#include "ModuleSceneStage1.h"



ModuleSceneChoosePlayer::ModuleSceneChoosePlayer()
{
	// Background / sky
	background = {0, 0, 384, 256};
}

ModuleSceneChoosePlayer::~ModuleSceneChoosePlayer()
{}

// Load assets
bool ModuleSceneChoosePlayer::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	player1 = App->textures->Load("../Screenshots/1Player.png");
	player2 = App->textures->Load("../Screenshots/2Players.png");
	graphics = player1;
	return ret;
}

// Load assets
bool ModuleSceneChoosePlayer::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading ChoosePlayer stage");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleSceneChoosePlayer::Update()
{
	if (App->fade->isBlack) {
		graphics = (player1 == graphics) ? player2 : player1;
	}
	else {
		App->fade->FadeToBlack(5);
	}

	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &background, 1.0f);

	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_choosePlayer, App->scene_stage1, 1);
	}
	return UPDATE_CONTINUE;
}