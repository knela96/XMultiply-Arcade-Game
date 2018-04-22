#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneStage1.h"
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
#include "ModulePowerUp.h"
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
	injection.PushBack({ 79, 0, 48, 105 });
	injection.PushBack({ 160, 0, 48, 103});
	injection.PushBack({ 238, 0, 48, 112 });
	injection.PushBack({ 307, 0, 48, 120 });
	injection.PushBack({ 386, 0, 48, 120});
	injection.speed = 0.75f;
	injection.loop = false;

	injection_up.PushBack({ 386, 0, 48, 120 });
	injection_up.PushBack({ 307, 0, 48, 120 });
	injection_up.PushBack({ 238, 0, 48, 112 });
	injection_up.PushBack({ 160, 0, 48, 103 });
	injection_up.PushBack({ 79, 0, 48, 105 });
	injection_up.PushBack({ 0, 0, 48, 102 });
	injection_up.speed = 0.75f;
	injection_up.loop = false;

	entering = { 0, 0, 48, 102 };
}

ModuleSceneStage1::~ModuleSceneStage1()
{}

// Load assets
bool ModuleSceneStage1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	down = false;

	right = false;

	injected = false;

	shipdeployed = false;


	App->tentacles->Enable();
	App->player->Disable();
	App->enemies->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->powerup->Enable();
	App->font->Enable();
	
	injectiontex = App->textures->Load("Assets/Sprites/Stage1/Tilemap/Injection.png");

	graphics = App->textures->Load("Assets/TileMap1.2.png");
	font_gameover = App->font->Load("Assets/Sprites/UI/fonts.2.png", "0123456789·' ºººººººººººººabcdefghijklmnopqrstuvwxyz", 2);
	back = App->textures->Load("Assets/FirstLvlMap3.1.png");

	hud = App->textures->Load("Assets/UI.png");

	music = App->audio->LoadM("Assets/Audio Files/Music in OGG/04_Into_the_Human_Body_Stage_1_.ogg");
	injection_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-053.wav");
	clear_stage = App->audio->LoadM("Assets/Audio Files/Music in OGG/06_Stage_Clear.ogg");

	App->audio->PlayMusic(music);

	 injectxy.x = 100;

	 injectxy.y -= injection.frames->h;


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


	AddEnemies();//Add Enemies
	

	App->audio->PlaySound(injection_fx);

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
	App->audio->UnloadM(clear_stage);
	clear_stage = nullptr;

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

		
	App->render->Blit(back, 0, 0, &ground, 0.5f, 0, true, false);
	App->render->Blit(graphics, 0, 0, &background);


	App->render->Blit(hud, 0, 224, NULL, 0.0f, false);

	
	if(injecting){
		if (!shipdeployed) {
			injectpos();
		}
		else {
			while (SDL_GetTicks() - aux_time >= 100) {
				if (injection_up.Finished()) {
					injectxy.y--;
				}
				else if (injection.Finished()) {
					entering = injection_up.GetCurrentFrame();
				}
				else {
					entering = injection.GetCurrentFrame();
					App->player->position.y += 1;
				}
				aux_time = SDL_GetTicks();
			}

			if (injection_up.Finished()){
				if (injectxy.y > -100) {
					injectxy.y--;
				}else
					injecting = false;
			}

			if (injection.Finished()) {
				if (App->player->position.x < 150) {
					App->player->position.x += 1;
					right = true;
				}
				else {
					App->player->enable_movement = true;
				}
			}
		}
			
	}

	App->render->Blit(injectiontex, injectxy.x, injectxy.y, &entering, 0.5f);	
	
	if(App->player->position.x >= 4700 || App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN) //4700
	{
		App->particles->Disable();
		App->enemies->Disable();
		hud = nullptr;
		//App->player->score = NULL;
		
		
		

		App->audio->PlayMusic(clear_stage);
		
		SDL_SetTextureColorMod(graphics, 0, 0, 0);
		SDL_SetTextureColorMod(back, 0, 0, 0);

		if (SDL_GetTicks() - start_time >= 500 ) {
			start_time = SDL_GetTicks();
			
			if (index < 17) {

				_stageendblit[index] = _stageend[index];
				_stageendblit2[index] = _stageend2[index];
			}
			_stageendblit[index + 1] = _stageend[11];
			_stageendblit2[index + 1] = _stageend2[17];
			index++;


			

		}
		
		App->font->BlitText(100, 100, font_gameover, _stageendblit);
		App->font->BlitText(60, 136, font_gameover, _stageendblit2);
	}
	else {
		sprintf_s(App->player->score_text, 10, "%7d", App->player->score);
		App->font->BlitText(80, 240, App->player->font_score, App->player->score_text);
		App->font->BlitText(32, 240, App->player->font_score, "score");
	}

	if (resetmap)
		resetMap();

	
	return UPDATE_CONTINUE;
}

void ModuleSceneStage1::injectpos() {

	if (injectxy.y == 0) {
		App->player->position.y = entering.h;
		App->player->Enable();
		shipdeployed = true;
	}
	else
		injectxy.y++;
}

void ModuleSceneStage1::resetMap() {

	if (!App->fade->isBlack) {
		App->fade->FadeonlyBlack();
	}
	else {
		if (!cleaned) {
			App->enemies->Disable();
			App->powerup->Disable();
			App->particles->Disable();
			cleaned = true;
		}
		else {
			App->enemies->Enable();
			App->powerup->Enable();
			App->particles->Enable();
			App->player->Enable();
			AddEnemies();
			App->fade->isBlack = false;
			App->fade->resetStep();
			App->player->resetPlayer();
			App->render->camera.x = 0;
			App->render->camera.y = 0;
			right = true;
			resetmap = false;
		}
	}
}

void ModuleSceneStage1::AddEnemies(){

//first spiral
	App->enemies->AddEnemy(BROWN_WORM, 455, 50, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 465, 50, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 475, 50, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 485, 50, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 495, 50, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 505, 50, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 515, 50, -1, true);



	App->enemies->AddEnemy(BROWN_WORM, 455, 50, -1);
	App->enemies->AddEnemy(BROWN_WORM, 465, 50, -1);
	App->enemies->AddEnemy(BROWN_WORM, 475, 50, -1);
	App->enemies->AddEnemy(BROWN_WORM, 485, 50, -1);
	App->enemies->AddEnemy(BROWN_WORM, 495, 50, -1);
	App->enemies->AddEnemy(BROWN_WORM, 505, 50, -1);
	App->enemies->AddEnemy(BROWN_WORM, 515, 50, -1);

	
	
//2 shrimps

	App->enemies->AddEnemy(LITTLE_SHRIMP, 600, 100, -1);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 645, 80, -1);

//1 anemona
	App->enemies->AddEnemy(NEMONA_TENTACLE, 520, 148, -1);

// 2 shrimps
	App->enemies->AddEnemy(LITTLE_SHRIMP, 760, 50, -1);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 805, 60, -1);

//powerup1
	App->enemies->AddEnemy(POWERUPSHIP, 800, 100, 3);
	
	//second spiral
	App->enemies->AddEnemy(BROWN_WORM, 900, 100, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 910, 100, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 920, 100, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 930, 100, -1, true);
	App->enemies->AddEnemy(BROWN_WORM, 940, 100, -1, true);

	App->enemies->AddEnemy(BROWN_WORM, 900, 100, -1);
	App->enemies->AddEnemy(BROWN_WORM, 910, 100, -1);
	App->enemies->AddEnemy(BROWN_WORM, 920, 100, -1);
	App->enemies->AddEnemy(BROWN_WORM, 930, 100, -1);
	App->enemies->AddEnemy(BROWN_WORM, 940, 100, -1);

//powerup
	App->enemies->AddEnemy(POWERUPSHIP, 1000, 100, 2);
//anemona
	App->enemies->AddEnemy(NEMONA_TENTACLE, 1000, 168, -1);
//powerup
	App->enemies->AddEnemy(POWERUPSHIP, 1050, 100, 1);

//2 shrimps
	App->enemies->AddEnemy(LITTLE_SHRIMP, 1300, 50, -1);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 1300, 100, -1);

//powerup

	App->enemies->AddEnemy(POWERUPSHIP, 1350, 120, 1);

//anemona
	App->enemies->AddEnemy(NEMONA_TENTACLE, 1300, 150, -1);

//anemona
	App->enemies->AddEnemy(NEMONA_TENTACLE, 1350, 2, -1); //GIRA

//anemona
	App->enemies->AddEnemy(NEMONA_TENTACLE, 2225, 170, -1);
//anemona
	App->enemies->AddEnemy(NEMONA_TENTACLE, 2275, 170, -1);
//anemona
	App->enemies->AddEnemy(NEMONA_TENTACLE, 2325, 170, -1);
//anemona
	App->enemies->AddEnemy(NEMONA_TENTACLE, 2400, 170, -1);

//anemona
	App->enemies->AddEnemy(NEMONA_TENTACLE, 3050, 30, -1); //Gira
//powerup
	App->enemies->AddEnemy(POWERUPSHIP, 3100, 120, 3);
//2 shrimps
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3200, 120, -1);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3200, 200, -1);
//2 shrimps
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3300, 190, -1);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3300, 170, -1);
// shrimps
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3400, 200, -1);
//2 shrimps
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3500, 300, -1);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3500, 250, -1);
//2 shrimps
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3600, 280, -1);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3600, 300, -1);
//2 shrimps
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3700, 280, -1);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3750, 315, -1);
//2 shrimps
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3850, 300, -1);
	App->enemies->AddEnemy(LITTLE_SHRIMP, 3900, 330, -1);
// powerup
	App->enemies->AddEnemy(POWERUPSHIP, 4000, 330, 1);

	
}
