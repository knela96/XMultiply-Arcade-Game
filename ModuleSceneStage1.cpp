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
#include "ModuleFonts.h"
#include "ModuleTentacles.h"


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

	App->tentacles->Enable();
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->font->Enable();
	
	graphics = App->textures->Load("Assets/TileMap1.2.png");

	back = App->textures->Load("Assets/FirstLvlMap3.png");

	hud = App->textures->Load("Assets/UI.png");

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
	App->collision->AddCollider({ 2642, 202, 220, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2692, 187, 157, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2661, 222, 222, 34 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2850, 257, 100, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2926, 288, 115, 33 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2937, 1, 103, 34 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2920, 1, 17, 23 }, COLLIDER_WALL);
	//
	App->collision->AddCollider({ 3042, 325, 120, 28 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3165, 345, 59, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3225, 360, 67, 23 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3288, 393, 48, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3343, 416, 84, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3425, 442, 54, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3480, 450, 67, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3547, 474, 1414, 12 }, COLLIDER_WALL);
	//
	App->collision->AddCollider({ 3040, 45, 55, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3047, 60, 57, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3112, 70, 42, 8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3150, 74, 19, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3171, 83, 56, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3226, 94, 35, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3260, 113, 42, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3303, 126, 51, 32 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3354, 150, 18, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3372, 158, 55, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3427, 171, 33, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3461, 183, 50, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3511, 201, 50, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3561, 213, 47, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3612, 226, 21, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3634, 238, 35, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3670, 248, 40, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3711, 258, 1248, 10 }, COLLIDER_WALL);
	//
	App->collision->AddCollider({ 3740, 267, 156, 60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3896, 266, 68, 45 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3969, 269, 68, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3955, 449, 93, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4226, 457, 67, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4348, 454, 49, 27 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4359, 440, 18, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4341, 257, 91, 34 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4541, 257, 73, 92 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4541, 388, 73, 92 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4522, 404, 19, 77 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4522, 257, 19, 77 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4494, 441, 28, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4494, 257, 28, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4884, 389, 38, 83 }, COLLIDER_WALL);



	// Enemies
	App->enemies->AddEnemy(BROWN_WORM, 600, 100);
	App->enemies->AddEnemy(BROWN_WORM, 615, 100);
	App->enemies->AddEnemy(BROWN_WORM, 630, 100);
	App->enemies->AddEnemy(BROWN_WORM, 645, 100);
	App->enemies->AddEnemy(BROWN_WORM, 660, 100);
	App->enemies->AddEnemy(BROWN_WORM, 675, 100);
	App->enemies->AddEnemy(BROWN_WORM, 690, 100);//

	App->enemies->AddEnemy(BROWN_WORM, 900, 100);
	App->enemies->AddEnemy(BROWN_WORM, 915, 100);
	App->enemies->AddEnemy(BROWN_WORM, 930, 100);
	App->enemies->AddEnemy(BROWN_WORM, 945, 100);
	App->enemies->AddEnemy(BROWN_WORM, 960, 100);


	App->enemies->AddEnemy(LITTLE_SHRIMP, 400, 50);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 415, 50);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 440, 50);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 465, 50);//

	App->enemies->AddEnemy(LITTLE_SHRIMP, 800, 100);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 815, 100);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 840, 100);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 865, 100);//

	App->enemies->AddEnemy(LITTLE_SHRIMP, 1100, 150);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 1115, 150);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 1140, 150);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 1165, 150);

	App->enemies->AddEnemy(NEMONA_TENTACLE, 520, 148);
	App->enemies->AddEnemy(NEMONA_TENTACLE, 1038, 164);
	App->enemies->AddEnemy(NEMONA_TENTACLE, 1280, 140);

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
	App->font->Disable();
	music = nullptr;

	App->render->camera.x = App->render->camera.y = 0;
	
	return ret;

}
// Update: draw background
update_status ModuleSceneStage1::Update()
{
	if (!App->player->dead) {
		--ScrollingOffset;
		if (ScrollingOffset <= -512)
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

	App->render->Blit(hud, 0, 224, NULL, 0.0f, false);

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_stage1, App->scene_stage2, 1);
	}
	
	

	return UPDATE_CONTINUE;
}