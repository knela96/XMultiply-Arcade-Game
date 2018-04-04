#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{

	position.x = 100;
	position.y = 130;


	//({ 4, 4, 36, 10 })

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 97, 0, 48, 16 });
	idle.speed = 0.1f;
	
	forward.PushBack({ 97, 0, 48, 16 });
	forward.speed = 0.1f;

	backward.PushBack({ 97, 0, 48, 16 });
	backward.speed = 0.1f;


	upward.PushBack({ 49 , 0 , 48 , 16 });
	upward.PushBack({ 0, 0, 48 , 16 });
	upward.speed = 0.075f;

	upwardreturn.PushBack({ 49 , 0 , 48 , 16 });
	upwardreturn.PushBack({ 97, 0, 48, 16 });
	upwardreturn.speed = 0.075f;

	downward.PushBack({ 145, 0, 48, 16 });
	downward.PushBack({ 193, 0, 48, 16 });
	downward.speed = 0.075f;

	downwardreturn.PushBack({ 145, 0, 48, 16 });
	downwardreturn.PushBack({ 97, 0, 48, 16 });
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
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	//position.x += speed; //uncomment when camera moves
	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		position.y -= speed;
		current_animation = &upward;
		r = current_animation->GetCurrentFrameNotCycling(1);
		upwardreturn.reset_currentFrame();
		
	}
	else if (App->input->keyboard[SDL_SCANCODE_W] == 0) {
		if (current_animation == &upward || current_animation == &upwardreturn) {
			current_animation = &upwardreturn;
			r = current_animation->GetCurrentFrameNotCycling(2);
			upward.reset_currentFrame();
			if (current_animation->islastframe()) {
				current_animation = &idle;
			}
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		position.y += speed; 
		current_animation = &downward;
		r = current_animation->GetCurrentFrameNotCycling(1);
		downwardreturn.reset_currentFrame();
	}
	else if (App->input->keyboard[SDL_SCANCODE_S] == 0) {
		if (current_animation == &downward || current_animation == &downwardreturn) {
			current_animation = &downwardreturn;
			r = current_animation->GetCurrentFrameNotCycling(2);
			downward.reset_currentFrame();
			if (current_animation->islastframe()) {
				current_animation = &idle;
			}
		}
	}

	if (current_animation == &idle) {
		r = current_animation->GetCurrentFrame();
	}

	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	LOG("Unloading ken scene");
	App->textures->Unload(graphics);
	position.x = 100;
	position.y = 130;
	return true;
}