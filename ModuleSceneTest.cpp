#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleTentacles.h"
#include "ModuleInput.h"
#include "ModuleSceneTest.h";

ModuleSceneTest::ModuleSceneTest()
{
}

ModuleSceneTest::~ModuleSceneTest()
{}

// Load assets
bool ModuleSceneTest::Start()
{
	App->player->Enable();
	App->tentacles->Enable();
	App->player->AddTentacles();
	App->player->enable_movement = false;
	App->player->powerup[1] = true;
	return true;
}

// Update: draw background
update_status ModuleSceneTest::Update()
{
	
	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneTest::CleanUp()
{
	
	return true;
}