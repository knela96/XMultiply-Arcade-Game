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
	
	graphics = App->textures->Load("Assets/TileMap1.1.png");

	back = App->textures->Load("Assets/FirstLvlMap3.png");

	music = App->audio->LoadM("Assets/Audio Files/Music in OGG/04_Into_the_Human_Body_Stage_1_.ogg");

	App->audio->PlayMusic(music);

	// Colliders ---
	App->collision->AddCollider({ 0, 213, 2540, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 503, 0, 2025, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 412, 195, 50, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 422, 184, 19, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 499, 189, 80, 36 }, COLLIDER_WALL);
	App->collision->AddCollider({ 578, 201, 19, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 642, 1, 66, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 764, 1, 50, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 773, 31, 19, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1026, 201, 67, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1011, 1, 80, 36 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1091, 1, 19, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1154, 1, 67, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1267, 189, 80, 36 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1347, 201, 19, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1484, 1, 63, 96 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1484, 129, 63, 96 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1450, 1, 34, 89 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1450, 136, 34, 99 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1422, 190, 28, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1422, 1, 28, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1667, 1, 67, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1788, 197, 50, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1797, 184, 19, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2010, 1, 129, 95 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2010, 130, 129, 95 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2139, 1, 39, 62 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2139, 164, 39, 62 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2178, 1, 33, 52 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2178, 172, 33, 52 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2428, 1, 50, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2437, 31, 19, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2545, 189, 80, 36 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2617, 201, 19, 25 }, COLLIDER_WALL);

	// Enemies
	App->enemies->AddEnemy(BROWN_WORM, 300, 50);
	App->enemies->AddEnemy(BROWN_WORM, 300, 100);
	App->enemies->AddEnemy(BROWN_WORM, 300, 150);
	App->enemies->AddEnemy(BROWN_WORM, 300, 200);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 400, 200);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 415, 200);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 440, 200);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 465, 200);
	App->enemies->AddEnemy(NEMONA_TENTACLE, 520, 148);

	//POWERUPS
	App->enemies->AddEnemy(POWERUPSHIP, 400, 150);
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

	App->player->position.x += 1;

	App->render->camera.x += 1 * SCREEN_SIZE;

	if (App->render->camera.x > 2657*SCREEN_SIZE && App->render->camera.x < 3428*SCREEN_SIZE) App->render->camera.y += 1 ;

	App->render->Blit(back, ScrollingOffset, 0, &ground, 0.1f);

	App->render->Blit(back, ScrollingOffset + 512, 0, &ground, 0.1f);
	

	App->render->Blit(graphics, 0, 0, &background);


	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_stage1, App->scene_stage2, 1);
	}
	
	

	return UPDATE_CONTINUE;
}