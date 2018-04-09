#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
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
			App->particles->AddParticle(App->particles->shoot, position.x+40, position.y-18);
		//}
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && (downwardreturn.islastframe() && upwardreturn.islastframe()))
		current_animation = &idle;

	r = current_animation->GetCurrentFrame();

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


/*
start_time = (Uint32 *)SDL_GetTicks();

//Rectangle Movement

if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
if (start_time - shooting_delay > 250) {
for (int i = 0; i < 10 && (start_time - shooting_delay > 250); ++i) {
if (shoot.bullet == nullptr) {
shooting_delay = start_time;
shoot.bullet = new SDL_Rect{ player->position.x +  15, player->position.y, shoot.anim.h };
App->audio->PlaySound(shoot.common_fx);
shoot.position.x = App->player->position.x;
shoot.position.y = App->player->position.y;
break;
}
}
}
}
//Check Collisions
for (int i = 0; i < 10; ++i) {
for (int j = 0; j < 30; ++j) {
if (bullets[i].bullet != nullptr && App->enemy->enemies[j].collision != nullptr) {
if (checkCollision(bullets[i].bullet, App->enemy->enemies[j].collision)) {
bullets[i].bullet = nullptr;
App->enemy->enemies[j].collision = nullptr;
break;
}
}
}
}

;
return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleParticles::CleanUp()
{

for (int i = 0; i < 10; ++i) {
shoot.bullet = nullptr;
}
player = nullptr;

App->textures->Unload(graphics);
App->audio->UnloadS(shoot.common_fx);
return true;
}

bool ModuleParticles::checkCollision(SDL_Rect* bullet, SDL_Rect* enemy) {
//The sides of the rectangles
int leftA, leftB;
int rightA, rightB;
int topA, topB;
int bottomA, bottomB;

//Calculate the sides of rect A
leftA = bullet->x;
rightA = bullet->x + bullet->w;
topA = bullet->y;
bottomA = bullet->y + bullet->h;

//Calculate the sides of rect B
leftB = enemy->x;
rightB = enemy->x + enemy->w;
topB = enemy->y;
bottomB = enemy->y + enemy->h;

//If any of the sides from A are outside of B
if (bottomA <= topB)
{
return false;
}

if (topA >= bottomB)
{
return false;
}

if (rightA <= leftB)
{
return false;
}

if (leftA >= rightB)
{
return false;
}

//If none of the sides from A are outside B
return true;
}
*/