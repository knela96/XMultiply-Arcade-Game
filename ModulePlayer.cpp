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

#include<stdio.h>

#include "SDL/include/SDL.h"

ModulePlayer::ModulePlayer()
{

	position.x = 100;
	position.y = 130;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 97, 0, 48, 16 });
	idle.loop = true;
	idle.speed = 0.1f;
	
	forward.PushBack({ 97, 0, 48, 16 });
	forward.loop = false;
	forward.speed = 0.1f;

	backward.PushBack({ 97, 0, 48, 16 });
	backward.loop = false;
	backward.speed = 0.1f;


	upward.PushBack({ 49 , 0 , 48 , 16 });
	upward.PushBack({ 0, 0, 48 , 16 });
	upward.loop = false;
	upward.speed = 0.075f;

	upwardreturn.PushBack({ 49 , 0 , 48 , 16 });
	upwardreturn.PushBack({ 97, 0, 48, 16 });
	upwardreturn.loop = false;
	upwardreturn.speed = 0.075f;

	downward.PushBack({ 145, 0, 48, 16 });
	downward.PushBack({ 193, 0, 48, 16 });
	downward.loop = false;
	downward.speed = 0.075f;

	downwardreturn.PushBack({ 145, 0, 48, 16 });
	downwardreturn.PushBack({ 97, 0, 48, 16 });
	downwardreturn.loop = false;
	downwardreturn.speed = 0.075f;

	current_animation = &idle;



}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Player.png"); // arcade version

	start_time = 0;
	dead = false;

	//Add a collider to the player
	collider = App->collision->AddCollider({ position.x, position.y, 10, 10 }, COLLIDER_PLAYER, this);

	powerup[BASIC_SHOOT] = true;
	powerup[PARABOLA_SHOOT] = true;

	font_score = App->font->Load("Assets/fonts.1.png", "0123456789ם.-=יט()ףעבת`´!?abcdefghijklmnopqrstuvwxyz", 2);

	

	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, false);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, false);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, false);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, false);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, false);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, false);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, true);
	App->tentacles->AddTentacle(App->tentacles->tentacle, position.x, position.y, true);

	

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		current_animation = &upward;
		
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP) {
		if (current_animation == &upward || current_animation == &upwardreturn) {
			current_animation = &upwardreturn;
			current_animation->Reset();
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed; 
		current_animation = &downward;
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP) {
		if (current_animation == &downward || current_animation == &downwardreturn) {
			current_animation = &downwardreturn;
			current_animation->Reset();
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		//if (start_time - SDL_GetTicks() > 250) {
			//start_time = SDL_GetTicks();

		if (powerup[BASIC_SHOOT] == true)
			App->particles->AddParticle(App->particles->shoot1, position.x + 40, position.y, COLLIDER_PLAYER_SHOT);
		
		
		if (powerup[PARABOLA_SHOOT] == true) {
			App->particles->AddParticle(App->particles->shoot1, position.x + 40, position.y, COLLIDER_PLAYER_SHOT);
			//score += 13;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && (downwardreturn.islastframe() && upwardreturn.islastframe()))
		current_animation = &idle;


	//Collider nau
	collider->SetPos(position.x+10, position.y+6);


	// Draw everything --------------------------------------
	if (!dead)
		App->render->Blit(graphics, position.x, position.y, &current_animation->GetCurrentFrame());
	else
		if (SDL_GetTicks() - start_time >= 1000)
			App->fade->FadeToBlack((Module*)App->scene_stage1, (Module*)App->scene_MainMenu);

	
	sprintf_s(score_text, 10, "%7d", score);

	//Draw UI 
	App->font->BlitText(80, 240, font_score, score_text);
	App->font->BlitText(32, 240, font_score, "score");

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player assets");
	App->textures->Unload(graphics);
	position.x = 100;
	position.y = 130;
	return true;
}

void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2) {

	if (!dead) {
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE);
		dead = true;
		collider1->to_delete = true;
		start_time = SDL_GetTicks();
	}
}
