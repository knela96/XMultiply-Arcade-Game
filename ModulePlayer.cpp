#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleTentacles.h"
#include "ModuleSceneStage1.h"
#include "ModuleAudio.h"
#include <assert.h>
#include<stdio.h>

#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer()
{

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 97, 0, 48, 16 });
	idle.loop = true;
	idle.speed = 0.1f;

	nitro.PushBack({ 208,80,48,16 });
	nitro.PushBack({ 208,64,48,16 });
	nitro.PushBack({ 208,48,48,16});
	nitro.PushBack({ 240,144,16,16 });
	nitro.loop = true;
	nitro.speed = 0.1f;

	forward.PushBack({ 97, 0, 48, 16 });
	forward.loop = false;
	forward.speed = 0.1f;

	backward.PushBack({ 97, 0, 48, 16 });
	backward.loop = false;
	backward.speed = 0.1f;


	upward.PushBack({ 49 , 0 , 48 , 16 });
	upward.PushBack({ 0, 0, 48 , 16 });
	upward.loop = false;
	upward.speed = 0.06f;

	upwardreturn.PushBack({ 49 , 0 , 48 , 16 });
	upwardreturn.PushBack({ 97, 0, 48, 16 });
	upwardreturn.loop = false;
	upwardreturn.speed = 0.06f;

	downward.PushBack({ 145, 0, 48, 16 });
	downward.PushBack({ 193, 0, 48, 16 });
	downward.loop = false;
	downward.speed = 0.06f;

	downwardreturn.PushBack({ 145, 0, 48, 16 });
	downwardreturn.PushBack({ 97, 0, 48, 16 });
	downwardreturn.loop = false;
	downwardreturn.speed = 0.06f;

	current_animation = &idle;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Sprites/Character/Player.png"); // arcade version
	
	death_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-044.wav");

	current_animation = &idle;

	camera_offset.x = App->render->camera.x;
	camera_offset.y = App->render->camera.y;

	speed = 2;
	 
	nitroanim = false;

	start_time = 0;
	life = 3;
	dead = false;

	//Add a collider to the player
	collider = App->collision->AddCollider({ position.x+4, position.y+1, 22, 14 }, COLLIDER_PLAYER, this);

	powerup[BASIC_SHOOT] = true;
	powerup[BOMB_SHOOT] = false;

	font_score = App->font->Load("Assets/Sprites/UI/fonts.1.png", "0123456789í.-=éè()óòáú`´!?abcdefghijklmnopqrstuvwxyz", 2);
	font_gameover = App->font->Load("Assets/Sprites/UI/fonts.2.png", "0123456789·' ºººººººººººººabcdefghijklmnopqrstuvwxyz", 2);

	music = App->audio->LoadM("Assets/Audio Files/Music in OGG/16_Game_Over.ogg");

	return ret;
}

bool ModulePlayer::CleanUp()
{
	position.x = 100;
	position.y = 130;

	LOG("Unloading Player assets");
	App->textures->Unload(graphics);
	graphics = nullptr;
	App->font->UnLoad(font_score);
	font_score = -1;
	App->font->UnLoad(font_gameover);
	font_gameover = -1;
	App->audio->UnloadS(death_fx);
	death_fx = nullptr;
	App->audio->UnloadM(music);
	music = nullptr;
	return true;
}
// Update: draw background
update_status ModulePlayer::Update()
{
	if (nitroanim) {
		if (counter < 60) {
			App->render->Blit(graphics, position.x - 25, position.y + 2, &(nitro.GetCurrentFrame()));
			counter +=1;
		}
		else {
			nitro.Reset();
			counter = 0;
			nitroanim = false;
		}
	}

	
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN)
	{
		godmode = !godmode;
	}
	if (godmode == true)
	App->font->BlitText(0, 0, App->player->font_score, _godmode);

	if (enable_movement) {

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && position.x < App->render->camera.x / SCREEN_SIZE + SCREEN_WIDTH-40)
		{
			position.x += speed;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && position.x > App->render->camera.x / SCREEN_SIZE)
		{
			position.x -= speed;
		}
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && position.y > App->render->camera.y/SCREEN_SIZE)
		{
			position.y -= speed;
			current_animation = &upward;
			current_animation->Reset();
		}
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && position.y > App->render->camera.y/SCREEN_SIZE)
		{
			position.y -= speed;
			current_animation = &upward;

		}
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP) {
			if (current_animation == &upward || current_animation == &upwardreturn) {
				current_animation = &upwardreturn;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN && position.y < App->render->camera.y /SCREEN_SIZE + SCREEN_HEIGHT-50)
		{
			position.y += speed * 1.5f;
			current_animation = &downward;
			current_animation->Reset();

		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && position.y < App->render->camera.y /SCREEN_SIZE + SCREEN_HEIGHT - 50)
		{
			position.y += speed * 1.5f;
			current_animation = &downward;
		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP) {
			if (current_animation == &downward || current_animation == &downwardreturn) {
				current_animation = &downwardreturn;
				current_animation->Reset();
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN) {
			position.x = 4700;
			position.y = 100;
			App->scene_stage1->disableModules();
		}

		if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN && enable_movement) {
			life = 0;
			dead = true;
			text_delay = 0;
		}

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {

			if (powerup[BASIC_SHOOT] == true) {
				App->particles->AddParticle(App->particles->basic_shoot, position.x + 40, position.y, COLLIDER_PLAYER_SHOT);
				App->tentacles->ShootLaser();
				App->audio->PlaySound(App->particles->basic_shoot.fx);
			}

			if (SDL_GetTicks() - start_time >= 1000) {
				if (powerup[BOMB_SHOOT] == true) {
					App->particles->AddParticle(App->particles->bomb, position.x + 20, position.y, COLLIDER_PLAYER_SHOT);
				}
			}
			start_time = SDL_GetTicks();

		}
		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
			if (powerup[BASIC_SHOOT] == true) {
				if (SDL_GetTicks() - start_time >= 500) {
					start_time = SDL_GetTicks();
					App->tentacles->ShootLaser();
					App->particles->AddParticle(App->particles->basic_shoot, position.x + 40, position.y, COLLIDER_PLAYER_SHOT);
					App->audio->PlaySound(App->particles->basic_shoot.fx);
				}
			}

			if (powerup[BOMB_SHOOT] == true) {
				if (SDL_GetTicks() - aux_time >= 1000) {
					aux_time = SDL_GetTicks();
					App->particles->AddParticle(App->particles->bomb, position.x + 20, position.y, COLLIDER_PLAYER_SHOT);
				}
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE	&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
			&& (downwardreturn.islastframe() && upwardreturn.islastframe())) {
			current_animation = &idle;
			current_animation->Reset();
		}

	}
	//Collider nau
	collider->SetPos(position.x+10, position.y+3);


	// Draw everything --------------------------------------
	if (!dead)
		App->render->Blit(graphics, position.x, position.y, &current_animation->GetCurrentFrame());
	if (godmode == true)
		App->font->BlitText(0, 0, App->player->font_score, _godmode);
	
	collider->SetPos(position.x + 4, position.y + 1);//SET POS PLAYER_COLLIDER
	
	if (dead) {
		if (life < 1) {
			if (text_delay == 0) {
				App->scene_stage1->disableModules();
				App->audio->PlayMusic(music);
			}
			if (text_delay++ <= 200) {
				App->font->BlitText(120, 100, font_gameover, "game over");
			}
			else {
				App->fade->FadeToBlack((Module*)App->scene_stage1, (Module*)App->scene_MainMenu);
			}
		}
		else {
			App->scene_stage1->resetmap = true;
		}
	}
	LOG("%i", life);
	

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2) {

	
	if (!dead && godmode == false && collider2->type != COLLIDER_POWERUP) {

		App->particles->AddParticle(App->particles->explosion_player, position.x, position.y-24, COLLIDER_NONE);
		App->audio->PlaySound(death_fx);
		dead = true;
		App->scene_stage1->right = false;
		life--;
		start_time = 0;
		enable_movement = false;
		
	}
}

void ModulePlayer::resetPlayer() {
	speed = 2;
	score = 0;
	enable_movement = false;
	current_animation = &idle;
	App->audio->PlayMusic(App->scene_stage1->music);
	powerup[TENTACLE_SHOOT] = false;
	powerup[BOMB_SHOOT] = false;
}


bool ModulePlayer::AddTentacles() {

	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y);
	App->tentacles->AddTentacle(App->tentacles->anchor_top, position.x + 16, position.y, false, true);

	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x + 16, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->anchor_bottom, position.x + 16, position.y, false, true);

	return true;
}