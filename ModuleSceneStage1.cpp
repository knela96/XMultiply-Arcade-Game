#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneStage1.h"
#include "ModuleSceneStage2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
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
	App->enemies->Enable();
	
	graphics = App->textures->Load("Assets/TileMap1.png");

	back = App->textures->Load("Assets/FirstLvlMap3.png");

	music = App->audio->LoadM("Assets/Audio Files/Music in OGG/04_Into_the_Human_Body_Stage_1_.ogg");

	App->audio->PlayMusic(music);

	// Colliders ---
	App->collision->AddCollider({ 0, 208, 3930, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1380, 0, 100, 100 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1380, 140, 100, 120 }, COLLIDER_WALL);

	// Enemies
	App->enemies->AddEnemy(BROWN_WORM, 300, 50);
	App->enemies->AddEnemy(BROWN_WORM, 300, 100);
	App->enemies->AddEnemy(BROWN_WORM, 300, 150);
	App->enemies->AddEnemy(BROWN_WORM, 300, 200);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 400, 50);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 400, 100);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 400, 150);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 400, 200);
<<<<<<< HEAD
	
=======
	App->enemies->AddEnemy(LITTLE_SHRIMP, 400, 200);
	App->enemies->AddEnemy(NEMONA_TENTACLE, 520, 148);

	//POWERUPS
<<<<<<< HEAD
	App->enemies->AddEnemy(POWERUPSHIP, 400, 150);
=======
	App->enemies->AddEnemy(POWERUPSHIP, 500, 200);
	App->enemies->AddEnemy(POWERUPSHIP, 500, 200);
	App->enemies->AddEnemy(POWERUPSHIP, 500, 200);
	App->enemies->AddEnemy(POWERUPSHIP, 500, 200);
>>>>>>> 0c78227c73cde2aec574f209fbfe4204a5700841
>>>>>>> 655b2a7029169713bf9e0d494573265211868cd5
	return ret;
}

bool ModuleSceneStage1::CleanUp()
{
	LOG("Cleaning backround assets");
	bool ret = true;

	App->textures->Unload(graphics);
	App->textures->Unload(back);
	App->player->Disable();
	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->audio->UnloadM(music);
	music = nullptr;

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


	int scroll_speed = 1;

	App->player->position.x += 1;

	App->render->camera.x += 1 * SCREEN_SIZE;

	App->render->Blit(back, ScrollingOffset, 0, &ground, 0.1f);

	App->render->Blit(back, ScrollingOffset + 512, 0, &ground, 0.1f);
	

	App->render->Blit(graphics, 0, 0, &background);


	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_stage1, App->scene_stage2, 1);
	}
	
	

	return UPDATE_CONTINUE;
}