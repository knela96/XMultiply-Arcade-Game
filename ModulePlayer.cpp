#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{

	position.x = 100;
	position.y = 130;


	//({ 4, 4, 36, 10 })

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
	collider = App->collision->AddCollider({ position.x, position.y, 48, 16 }, COLLIDER_PLAYER, this);
	
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	//position.x += speed; //uncomment when camera moves
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
			App->particles->AddParticle(App->particles->shoot, position.x+40, position.y, COLLIDER_PLAYER_SHOT);
		//}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && (downwardreturn.islastframe() && upwardreturn.islastframe()))
		current_animation = &idle;

	r = current_animation->GetCurrentFrame();

	collider->SetPos(position.x, position.y);
	// Draw everything --------------------------------------
	if (!dead)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	else
		if (SDL_GetTicks() - start_time >= 1000)
			App->fade->FadeToBlack((Module*)App->scene_stage1, (Module*)App->scene_MainMenu);


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

void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2) {

	if (collider2->type != COLLIDER_PLAYER) {
		bool ret = true;
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = collider1->rect.x;
		rightA = collider1->rect.x + collider1->rect.w;
		topA = collider1->rect.y;
		bottomA = collider1->rect.y + collider1->rect.h;

		//Calculate the sides of rect B
		leftB = collider2->rect.x;
		rightB = collider2->rect.x + collider2->rect.w;
		topB = collider2->rect.y;
		bottomB = collider2->rect.y + collider2->rect.h;

		//If any of the sides from A are outside of B
		if (bottomA <= topB)
		{
			ret = false;
		}

		if (topA >= bottomB)
		{
			ret = false;
		}

		if (rightA <= leftB)
		{
			ret = false;
		}

		if (leftA >= rightB)
		{
			ret = false;
		}

		if (ret == true)
			if (!dead) {
				App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE);
				dead = true;
				start_time = SDL_GetTicks();
			}
	}
}
