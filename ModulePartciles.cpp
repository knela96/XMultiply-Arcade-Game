#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleEnemy.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleParticles::ModuleParticles() : Module() {

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
	

}

// Destructor



ModuleParticles::~ModuleParticles() {}

// Called before render is available
bool ModuleParticles::Start()
{
	bool ret = true;
	
	
	LOG("Loading player textures");

	shoot.common_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-114.wav");
	
	graphics = App->textures->Load("Assets/Player.png"); // arcade version
	shoot.anim.PushBack({ 64, 30, 17, 18});
	shoot.anim.speed = 0.1f;
	return ret;
}

// Called every draw update
update_status ModuleParticles::Update()
{
	player = App->player;

	


	
	start_time = (Uint32 *)SDL_GetTicks();

	//Rectangle Movement

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		if (start_time - shooting_delay > 250) {
			for (int i = 0; i < 10 && (start_time - shooting_delay > 250); ++i) {
				if (shoot.bullet == nullptr) {
					shooting_delay = start_time;
					shoot.bullet = new SDL_Rect{ player->position.x +  15, player->position.y  };
					App->audio->PlaySound(shoot.common_fx);
					shoot.position.x = App->player->position.x;
					shoot.position.y = App->player->position.y;
					break;
				}
			}
		}
	}
	/*
	/*
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
	*/
	for (int i = 0; i < 10; ++i) {
		if (shoot.bullet != nullptr) {
			if (shoot.position.x > SCREEN_WIDTH) {
				shoot.bullet = nullptr;
			}
			else {
				shoot.position.x += 2;
				App->render->Blit(graphics, shoot.position.x, shoot.position.y - 15, shoot.bullet);
			}
		}
	}
	;
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleParticles::CleanUp()
{
	/*
	for (int i = 0; i < 10; ++i) {
		bullets[i].bullet = nullptr;
	}
	player = nullptr;

	App->textures->Unload(graphics);
	App->audio->UnloadS(shoot_fx);*/
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}