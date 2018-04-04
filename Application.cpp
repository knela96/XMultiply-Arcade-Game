#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleEnemy.h"
#include "ModuleProjectile.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMainMenu.h"
#include "ModuleSceneChoosePlayer.h"
#include "ModuleSceneStage1.h"
#include "ModuleSceneStage2.h"
#include "ModuleSceneCongrats.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	modules[12] = player = new ModulePlayer();
	modules[11] = projectile = new ModuleProjectile();
	modules[10] = enemy = new ModuleEnemy();
	modules[8] = scene_MainMenu = new ModuleSceneMainMenu();
	modules[9] = scene_choosePlayer = new ModuleSceneChoosePlayer();
	modules[7] = scene_stage1 = new ModuleSceneStage1();
	modules[6] = scene_stage2 = new ModuleSceneStage2();
	modules[5] = scene_congrats = new ModuleSceneCongrats();
	modules[13] = fade = new ModuleFadeToBlack();//Must be after all scenes
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Disable the modules that do not want to start
	scene_choosePlayer->Disable();
	scene_stage1->Disable();
	scene_stage2->Disable();
	scene_congrats->Disable();
	audio->Disable();

	player->Disable();
	enemy->Disable();
	projectile->Disable();


	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}