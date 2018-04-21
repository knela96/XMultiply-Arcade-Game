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
#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL_render.h"
#include "ModulePlayer.h"
#include <stdio.h>


ModuleSceneStage1::ModuleSceneStage1()
{
	//ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 5120;
	ground.h = 512;

	// Background 
	background.x = 0;
	background.y = 1;
	background.w = 4961;
	background.h = 513;	

	//injection 
	injection.PushBack({ 0, 0, 48, 102});
	injection.PushBack({ 79, 0, 48, 105});
	injection.PushBack({ 160, 0, 48, 103});
	injection.PushBack({ 238, 0, 48, 112 });
	injection.PushBack({ 307, 0, 48, 120 });
	injection.PushBack({ 386, 0, 48, 120});
	injection.speed = 2.0f;
	entering = { 0, 0, 48, 102 };

}

ModuleSceneStage1::~ModuleSceneStage1()
{}

// Load assets
bool ModuleSceneStage1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	timer = 0;

	down = false;

	right = false;

	injected = false;

	shipdeployed = false;


	App->tentacles->Enable();
	App->player->Disable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	App->font->Enable();
	
	injectiontex = App->textures->Load("Assets/Sprites/Stage1/Tilemap/Injection.png");

	graphics = App->textures->Load("Assets/TileMap1.2.png");
	font_gameover = App->font->Load("Assets/Sprites/UI/fonts.2.png", "0123456789·' ºººººººººººººabcdefghijklmnopqrstuvwxyz", 2);
	back = App->textures->Load("Assets/FirstLvlMap3.1.png");

	hud = App->textures->Load("Assets/UI.png");

	music = App->audio->LoadM("Assets/Audio Files/Music in OGG/04_Into_the_Human_Body_Stage_1_.ogg");	

	App->audio->PlayMusic(music);

	 injectxy.x = 100;

	 injectxy.y = -30;

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
	App->enemies->AddEnemy(BROWN_WORM, 455, 100,true);
	App->enemies->AddEnemy(BROWN_WORM, 465, 100, true);
	App->enemies->AddEnemy(BROWN_WORM, 475, 100, true);
	App->enemies->AddEnemy(BROWN_WORM, 485, 100, true);
	App->enemies->AddEnemy(BROWN_WORM, 495, 100, true);
	App->enemies->AddEnemy(BROWN_WORM, 505, 100, true);
	App->enemies->AddEnemy(BROWN_WORM, 515, 100, true);//
	
	App->enemies->AddEnemy(BROWN_WORM, 455, 100);
	App->enemies->AddEnemy(BROWN_WORM, 465, 100);
	App->enemies->AddEnemy(BROWN_WORM, 475, 100);
	App->enemies->AddEnemy(BROWN_WORM, 485, 100);
	App->enemies->AddEnemy(BROWN_WORM, 495, 100);
	App->enemies->AddEnemy(BROWN_WORM, 505, 100);
	App->enemies->AddEnemy(BROWN_WORM, 515, 100);

	App->enemies->AddEnemy(BROWN_WORM, 900, 100, true);
	App->enemies->AddEnemy(BROWN_WORM, 910, 100, true);
	App->enemies->AddEnemy(BROWN_WORM, 920, 100, true);
	App->enemies->AddEnemy(BROWN_WORM, 930, 100, true);
	App->enemies->AddEnemy(BROWN_WORM, 940, 100, true);

	App->enemies->AddEnemy(BROWN_WORM, 900, 100);
	App->enemies->AddEnemy(BROWN_WORM, 910, 100);
	App->enemies->AddEnemy(BROWN_WORM, 920, 100);
	App->enemies->AddEnemy(BROWN_WORM, 930, 100);
	App->enemies->AddEnemy(BROWN_WORM, 940, 100);


	App->enemies->AddEnemy(LITTLE_SHRIMP, 530, 50);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 545, 40);
	

	App->enemies->AddEnemy(LITTLE_SHRIMP, 600, 50);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 615, 40);

	App->enemies->AddEnemy(LITTLE_SHRIMP, 1100, 60);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 1150, 40);


	

	App->enemies->AddEnemy(NEMONA_TENTACLE, 520, 148);
	App->enemies->AddEnemy(NEMONA_TENTACLE, 1038, 160);
	App->enemies->AddEnemy(NEMONA_TENTACLE, 1038, 164);
	App->enemies->AddEnemy(NEMONA_TENTACLE, 1280, 150);

	//POWERUPS
	App->enemies->AddEnemy(POWERUPSHIP, 600, 130);
	App->enemies->AddEnemy(POWERUPSHIP, 1050, 100);
	App->enemies->AddEnemy(POWERUPSHIP, 1075, 75);
	App->enemies->AddEnemy(POWERUPSHIP, 1200, 100);
	return ret;
}

bool ModuleSceneStage1::CleanUp()
{
	LOG("Cleaning backround assets");
	bool ret = true;

	App->textures->Unload(graphics);
	App->textures->Unload(back);
	App->player->Disable();
	App->tentacles->Disable();
	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->font->Disable();

	App->audio->UnloadM(music);
	music = nullptr;

	App->render->camera.x = App->render->camera.y = 0;
	
	return ret;

}
// Update: draw background
update_status ModuleSceneStage1::Update()
{
	if (right)
	{
		App->player->position.x += 1;

		App->render->camera.x += 1 * SCREEN_SIZE;
	}

	if (down)
	{
		App->render->camera.y += 1;
	}


	if (App->render->camera.x > 2657 * SCREEN_SIZE && App->render->camera.x < 3428 * SCREEN_SIZE) 
	{
		down = true;

	}

	else down = false;
		

	App->render->Blit(back, 0, 0, &ground, 0.5f , 0, true, false);
	

	App->render->Blit(graphics, 0, 0, &background);


	App->render->Blit(hud, 0, 224, NULL, 0.0f, false);

	
	//Draw UI 
	

	if (!injected) {


		injectpos();


		App->render->Blit(injectiontex, injectxy.x, injectxy.y, &entering, 0.5f);

	}


	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_stage1, App->scene_stage2, 1);
	}
	
	
	
	if(App->player->position.x >= 600 )
	{
		App->particles->Disable();
		App->enemies->Disable();
		//App->collision->Disable();
		hud = nullptr;
		
		//App->player->score = NULL;
		
		

		SDL_SetTextureColorMod(graphics, 0 , 0, 0);

		SDL_SetTextureColorMod(back, 0, 0, 0);
		
		char _stageend[15] = "stage clear";
		char _stageendblit[15];
		
		
		/*if (SDL_GetTicks() - start_time >= 500) {
   			start_time = SDL_GetTicks();

		

 				_stageendblit[i] = _stageend[i];	
			
			
		}
		*/
		App->font->BlitText(100, 100, font_gameover, _stageendblit);
		
		
		//App->font->BlitText(100, 100, font_gameover, "stage clear");
		App->font->BlitText(60, 136, font_gameover, "stage bonus 10000");
		
	}
	else {
		sprintf_s(App->player->score_text, 10, "%7d", App->player->score);
		App->font->BlitText(80, 240, App->player->font_score, App->player->score_text);
		App->font->BlitText(32, 240, App->player->font_score, "score");

	}
	
	return UPDATE_CONTINUE;
}

void ModuleSceneStage1::injectpos() {

	switch (shipdeployed) {

	case false:
		if (injectxy.y == 0) {
			
			App->player->Enable();

			shipdeployed = true;

			right = true;

			injectxy.y--;
		}
		else injectxy.y++;

		break;

	case true:
		if (injectxy.y == -100) {

			injected = true;
		}
		else { 

			while (timer < 7) {
				entering = injection.GetCurrentFrame();
				timer++;
			}
			injectxy.y--; }
	}

}