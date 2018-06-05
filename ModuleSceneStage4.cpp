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
	right = false;
	resetmap = false;
	entering = true;
	cleaned = false;
	shipdone = false;
	aux_time = 0;
	start_time = 0;
	index1 = 0;
	index2 = 0;
	ground_bottom_y = 50;
	ground_top_y = -70;
	clearstage_fx = false;


	//App->player->enable_movement = true;
	App->tentacles->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->powerup->Enable();
	App->font->Enable();

	graphics = App->textures->Load("Assets/Tilemap4.1.png");
	font_gameover = App->font->Load("Assets/Sprites/UI/fonts.2.png", "0123456789·' ºººººººººººººabcdefghijklmnopqrstuvwxyz", 2);
	back = App->textures->Load("Assets/ForthLvlMap.png");

	//colliders

	//top
	CollidersTop1 = App->collision->AddCollider({ 0, ground_top_y, 5138, 100}, COLLIDER_WALL, this);
	CollidersTop2 = App->collision->AddCollider({ 197, ground_top_y, 57, 120 }, COLLIDER_WALL, this);
	CollidersTop3 = App->collision->AddCollider({ 330, ground_top_y, 43, 136 }, COLLIDER_WALL, this);
	CollidersTop4 = App->collision->AddCollider({ 648, ground_top_y, 42, 145 }, COLLIDER_WALL, this);
	CollidersTop5 = App->collision->AddCollider({ 840, ground_top_y, 45, 135 }, COLLIDER_WALL, this);
	CollidersTop6 = App->collision->AddCollider({ 1346, ground_top_y,53, 185 }, COLLIDER_WALL, this);
	CollidersTop7 = App->collision->AddCollider({ 1482, ground_top_y,42, 144 }, COLLIDER_WALL, this);
	CollidersTop8 = App->collision->AddCollider({ 1670, ground_top_y,52, 191 }, COLLIDER_WALL, this);
	CollidersTop9 = App->collision->AddCollider({ 1730, ground_top_y, 61, 129 }, COLLIDER_WALL, this);
	CollidersTop10 = App->collision->AddCollider({ 1990, ground_top_y, 182, 147 }, COLLIDER_WALL, this);
	CollidersTop11 = App->collision->AddCollider({ 2241, ground_top_y, 61, 144 }, COLLIDER_WALL, this);
	CollidersTop12 = App->collision->AddCollider({ 2371, ground_top_y, 368, 133 }, COLLIDER_WALL, this);
	CollidersTop13 = App->collision->AddCollider({ 2830, ground_top_y, 109, 143 }, COLLIDER_WALL, this);
	CollidersTop14 = App->collision->AddCollider({ 2950, ground_top_y, 118, 123 }, COLLIDER_WALL, this);
	CollidersTop15 = App->collision->AddCollider({ 3140, ground_top_y, 56, 189 }, COLLIDER_WALL, this);
	CollidersTop16 = App->collision->AddCollider({ 3330, ground_top_y, 121, 191 }, COLLIDER_WALL, this);
	CollidersTop17 = App->collision->AddCollider({ 3458, ground_top_y, 59, 141 }, COLLIDER_WALL, this);
	CollidersTop18 = App->collision->AddCollider({ 3590, ground_top_y, 50, 189 }, COLLIDER_WALL, this);
	CollidersTop19 = App->collision->AddCollider({ 3650, ground_top_y, 185, 150 }, COLLIDER_WALL, this);
	CollidersTop20 = App->collision->AddCollider({ 4168, ground_top_y, 54, 183 }, COLLIDER_WALL, this);
	CollidersTop21 = App->collision->AddCollider({ 4292, ground_top_y, 50, 135 }, COLLIDER_WALL, this);
	CollidersTop22 = App->collision->AddCollider({ 4548, ground_top_y, 113, 189 }, COLLIDER_WALL, this);
	//


	//bottom

	BigColliderBot = App->collision->AddCollider({ 0, ground_bottom_y + 142, 5138, 100 }, COLLIDER_WALL, this);
	ColliderBot1 = App->collision->AddCollider({ 199, ground_bottom_y + 60, 51, 76 }, COLLIDER_WALL, this);
	ColliderBot2 = App->collision->AddCollider({ 262, ground_bottom_y , 51, 119 }, COLLIDER_WALL, this);
	ColliderBot3 = App->collision->AddCollider({ 329, ground_bottom_y , 52, 122 }, COLLIDER_WALL, this);
	ColliderBot4 = App->collision->AddCollider({ 390, ground_bottom_y + 37, 52, 96 }, COLLIDER_WALL, this);
	ColliderBot5 = App->collision->AddCollider({ 850, ground_bottom_y + 91, 29, 75 }, COLLIDER_WALL, this);
	ColliderBot6 = App->collision->AddCollider({ 964, ground_bottom_y + 62, 56, 100 }, COLLIDER_WALL, this);
	ColliderBot7 = App->collision->AddCollider({ 1365, ground_bottom_y +91, 29, 75 }, COLLIDER_WALL, this);
	ColliderBot8 = App->collision->AddCollider({ 1475, ground_bottom_y + 62, 56, 100 }, COLLIDER_WALL, this);
	ColliderBot9 = App->collision->AddCollider({ 1736, ground_bottom_y + 127, 56, 62 }, COLLIDER_WALL, this);
	ColliderBot10 = App->collision->AddCollider({ 1866, ground_bottom_y + 127, 43, 62 }, COLLIDER_WALL, this);
	ColliderBot11 = App->collision->AddCollider({ 2179, ground_bottom_y + 61, 252, 100 }, COLLIDER_WALL, this);
	ColliderBot12 = App->collision->AddCollider({ 2522, ground_bottom_y + 98, 13, 67 }, COLLIDER_WALL, this);
	ColliderBot13 = App->collision->AddCollider({ 2636, ground_bottom_y + 69, 47, 105 }, COLLIDER_WALL, this);
	ColliderBot14 = App->collision->AddCollider({ 2890, ground_bottom_y + 69, 47, 105 }, COLLIDER_WALL, this);
	ColliderBot15 = App->collision->AddCollider({ 3014, ground_bottom_y + 65, 47, 105 }, COLLIDER_WALL, this);
	ColliderBot16 = App->collision->AddCollider({ 3144, ground_bottom_y + 116, 173, 77 }, COLLIDER_WALL, this);
	ColliderBot17 = App->collision->AddCollider({ 3331, ground_bottom_y + 62, 188, 119 }, COLLIDER_WALL, this);
	ColliderBot18 = App->collision->AddCollider({ 3596, ground_bottom_y + 104, 112, 65 }, COLLIDER_WALL, this);
	ColliderBot19 = App->collision->AddCollider({ 3714, ground_bottom_y + 64, 125, 108 }, COLLIDER_WALL, this);
	ColliderBot20 = App->collision->AddCollider({ 3978, ground_bottom_y + 101, 39, 78 }, COLLIDER_WALL, this);
	ColliderBot21 = App->collision->AddCollider({ 4046, ground_bottom_y + 71, 48, 111 }, COLLIDER_WALL, this);
	ColliderBot22 = App->collision->AddCollider({ 4238, ground_bottom_y + 67, 300, 111 }, COLLIDER_WALL, this);

	hud = App->textures->Load("Assets/UI.png");

	music = App->audio->LoadM("Assets/Audio Files/Music in OGG/10_Illegal_Illusion_Stage_4_.ogg");
	clear_stage = App->audio->LoadM("Assets/Audio Files/Music in OGG/06_Stage_Clear.ogg");

	App->audio->PlayMusic(music);

	App->player->godmode = true;

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
	if (entering) {
		enter();
	}
	if (right)
	{
		App->player->position.x += 1;

		App->render->camera.x += 1 * SCREEN_SIZE;
	}
	App->render->Blit(back, 0, 0, &background);
	App->render->Blit(graphics, 0, ground_top_y, &ground_top);
	App->render->Blit(graphics, 0, ground_bottom_y, &ground_bottom);
	App->render->Blit(hud, 0, 224, NULL, 0.0f, false);




	//colliders Update
	CollidersTop1->SetPos(0, ground_top_y);
	CollidersTop2->SetPos(197, ground_top_y);
	CollidersTop3->SetPos(330, ground_top_y);
	CollidersTop4->SetPos(648, ground_top_y);
	CollidersTop5->SetPos(840, ground_top_y);
	CollidersTop6->SetPos(1346, ground_top_y);
	CollidersTop7->SetPos(1482, ground_top_y);
	CollidersTop8->SetPos(1670, ground_top_y);
	CollidersTop9->SetPos(1730, ground_top_y);
	CollidersTop10->SetPos(1990, ground_top_y);
	CollidersTop11->SetPos(2241, ground_top_y);
	CollidersTop12->SetPos(2371, ground_top_y);
	CollidersTop13->SetPos(2830, ground_top_y);
	CollidersTop14->SetPos(2950, ground_top_y);
	CollidersTop15->SetPos(3140, ground_top_y);
	CollidersTop16->SetPos(3330, ground_top_y);
	CollidersTop17->SetPos(3458, ground_top_y);
	CollidersTop18->SetPos(3590, ground_top_y);
	CollidersTop19->SetPos(3650, ground_top_y);
	CollidersTop20->SetPos(4168, ground_top_y);
	CollidersTop21->SetPos(4292, ground_top_y);
	CollidersTop22->SetPos(4548, ground_top_y);

	BigColliderBot->SetPos(0,ground_bottom_y + 142);
	ColliderBot1 ->SetPos(199, ground_bottom_y +60);
	ColliderBot2->SetPos(262, ground_bottom_y);
	ColliderBot3->SetPos(329, ground_bottom_y);
	ColliderBot4->SetPos(390, ground_bottom_y + 37);
	ColliderBot5->SetPos(850, ground_bottom_y + 91);
	ColliderBot6->SetPos(964, ground_bottom_y + 62);
	ColliderBot7->SetPos(1365, ground_bottom_y + 91);
	ColliderBot8->SetPos(1475, ground_bottom_y + 62);
	ColliderBot9->SetPos(1736, ground_bottom_y + 127);
	ColliderBot10->SetPos(1866, ground_bottom_y + 127);
	ColliderBot11->SetPos(2179, ground_bottom_y + 61);
	ColliderBot12->SetPos(2522, ground_bottom_y + 98);
	ColliderBot13->SetPos(2636, ground_bottom_y + 69);
	ColliderBot14->SetPos(2890, ground_bottom_y + 69);
	ColliderBot15->SetPos(3014, ground_bottom_y + 65);
	ColliderBot16->SetPos(3144, ground_bottom_y + 116);
	ColliderBot17->SetPos(3331, ground_bottom_y + 62);
	ColliderBot18->SetPos(3596, ground_bottom_y + 104);
	ColliderBot19->SetPos(3714, ground_bottom_y + 64);
	ColliderBot20->SetPos(3978, ground_bottom_y + 101);
	ColliderBot21->SetPos(4046, ground_bottom_y + 71);
	ColliderBot22->SetPos(4238, ground_bottom_y + 67);

	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN) {
		ground_bottom_y--;
	}
	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN) {
		ground_top_y++;
	}

	if (App->player->position.x >= 5700) //4700
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

	if (App->render->camera.x == 4670) {
		right = false;
	}

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


	App->enemies->AddEnemy(NEMONA_TENTACLE, 400, 200, -1, true);

	App->enemies->AddEnemy(NEMONA_TENTACLE, 200, 200, -1, true);
	App->enemies->AddEnemy(NEMONA_TENTACLE, 450, 200, -1, true);


	App->enemies->AddEnemy(BOSS1, 450, 100, -1, true);
	App->enemies->AddEnemy(BOSSFACE, 450, 140, -1, true);

	App->enemies->AddEnemy(BOSSDISP, 544, 100, -1, true);
	App->enemies->AddEnemy(BOSSTENT, 555, 10, -1, true);

	App->enemies->AddEnemy(BOSSHEART, 450, 140, -1, true);
	App->enemies->AddEnemy(BOSSARM, 550, 100, -1, true);
	

}


void ModuleSceneStage4::enter() {

	if (!shipdone) {
		App->player->position.x = 0 - App->player->current_animation->frames->w;
		App->player->position.y = 100;
		shipdone = true;
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
			entering = false;

		}
	}
}