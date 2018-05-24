#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneStage4.h"
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

ModuleSceneStage4::ModuleSceneStage4()
{

	//ground
	ground_top.x = 0;
	ground_top.y = 0;
	ground_top.w = 5138;
	ground_top.h = 201;

	ground_bottom.x = 0;
	ground_bottom.y = 260;
	ground_bottom.w = 5138;
	ground_bottom.h = 319;

	// Background 
	background.x = 0;
	background.y = 1;
	background.w = 4961;
	background.h = 513;

}


ModuleSceneStage4::~ModuleSceneStage4()
{}

// Load assets

bool ModuleSceneStage4::Start()
{

	LOG("Loading background assets");

	bool ret = true;
	right = true;
	resetmap = false;
	cleaned = false;
	aux_time = 0;
	start_time = 0;
	index1 = 0;
	index2 = 0;
	clearstage_fx = false;

	App->tentacles->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->powerup->Enable();
	App->font->Enable();

	graphics = App->textures->Load("Assets/Tilemap4.png");
	font_gameover = App->font->Load("Assets/Sprites/UI/fonts.2.png", "0123456789·' ºººººººººººººabcdefghijklmnopqrstuvwxyz", 2);
	back = App->textures->Load("Assets/ForthLvlMap.png");

	hud = App->textures->Load("Assets/UI.png");

	music = App->audio->LoadM("Assets/Audio Files/Music in OGG/10_Illegal_Illusion_Stage_4_.ogg");
	clear_stage = App->audio->LoadM("Assets/Audio Files/Music in OGG/06_Stage_Clear.ogg");

	App->audio->PlayMusic(music);


	AddEnemies();//Add Enemies

	return ret;
}

bool ModuleSceneStage4::CleanUp()
{
	LOG("Cleaning backround assets");
	bool ret = true;
	App->textures->Unload(graphics);
	graphics = nullptr;
	App->font->UnLoad(font_gameover);
	font_gameover = -1;
	App->textures->Unload(back);
	back = nullptr;
	App->audio->UnloadM(music);
	music = nullptr;
	App->audio->UnloadM(clear_stage);
	clear_stage = nullptr;
	App->textures->Unload(hud);
	hud = nullptr;
	App->audio->UnloadM(clear_stage);
	clear_stage = nullptr;


	App->player->Disable();
	App->tentacles->Disable();
	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->font->Disable();


	App->render->camera.x = App->render->camera.y = 0;

	return ret;

}


update_status ModuleSceneStage4::Update()
{
	if (right)
	{
		App->player->position.x += 1;

		App->render->camera.x += 1 * SCREEN_SIZE;
	}

	App->render->Blit(back, 0, -50, &ground_top);
	App->render->Blit(back, 0, 200, &ground_bottom);
	App->render->Blit(graphics, 0, 0, &background);
	App->render->Blit(hud, 0, 224, NULL, 0.0f, false);

	if (App->player->position.x >= 4700) //4700
	{
		if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || App->input->controller[START] == KEY_STATE::KEY_DOWN) {
			App->fade->FadeToBlack((Module*)App->scene_stage4, (Module*)App->scene_MainMenu);
		}
		if (!clearstage_fx) {
			App->audio->PlayMusic(App->scene_stage4->clear_stage);
			clearstage_fx = true;
		}
		if (rgb < 1) {
			rgb = 0;
		}
		else {
			rgb--;
		}
		SDL_SetTextureColorMod(graphics, rgb, rgb, rgb);
		SDL_SetTextureColorMod(back, rgb, rgb, rgb);
		SDL_SetTextureColorMod(hud, rgb, rgb, rgb);

		if (SDL_GetTicks() - start_time >= 250) {
			start_time = SDL_GetTicks();

			if (index1 < 11) {
				_stageendblit[index1 + 1] = _stageend[11];
				_stageendblit[index1] = _stageend[index1];
				index1++;
			}
			if (index1 == 11) {
				show = true;
			}
			if (index2 < 17 && show) {
				_stageendblit2[index2 + 1] = _stageend2[17];
				_stageendblit2[index2] = _stageend2[index2];
				index2++;
			}

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

void ModuleSceneStage4::resetMap() {

	if (!App->fade->isBlack) {
		App->fade->FadeonlyBlack();
	}
	else {
		if (!cleaned) {
			disableModules();
			enableModules();
			App->player->dead = false;
			App->player->position.x = 0 - App->player->current_animation->frames->w;
			App->player->position.y = 100;
		}
		else {
			if (App->player->position.x < 100) {
				App->player->nitroanim = true;
				App->player->position.x++;
				App->render->camera.x = 0;
				App->render->camera.y = 0;
			}
			else {
				App->player->enable_movement = true;
				right = true;
				resetmap = false;
				cleaned = false;
			}
		}
	}
}

void ModuleSceneStage4::disableModules() {
	right = false;
	App->player->resetPlayer();
	App->enemies->Disable();
	App->powerup->Disable();
	App->particles->removeParticles();
	App->tentacles->RemoveTentacle();

}

void ModuleSceneStage4::enableModules() {
	App->enemies->Enable();
	App->powerup->Enable();
	App->particles->Enable();
	AddEnemies();
	App->fade->isBlack = true;
	App->fade->resetStep();
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	cleaned = true;
}

void ModuleSceneStage4::AddEnemies() {
}