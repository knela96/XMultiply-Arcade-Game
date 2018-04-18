#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles() : Module() {

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles() {}

// Called before render is available
bool ModuleParticles::Start()
{
	bool ret = true;
	
	LOG("Loading player textures");
	
	graphics = App->textures->Load("Assets/Player.png");
	//graphics = App->textures->Load("Assets/PowerUp/PowerUp.png");

	shoot1.anim.PushBack({ 64, 30, 17, 18});
	shoot1.anim.loop = false;
	shoot1.anim.speed = 3.0f;
	shoot1.life = 2000;
	shoot1.common_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-114.wav");

	shoot2.id = 1;

	shoot2.anim.PushBack({ 50, 82, 12, 18 });
	shoot2.anim.loop = false;
	shoot2.anim.speed = 3.0f;
	shoot2.life = 2000;
	shoot2.common_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-114.wav");

	animation = &shoot2.anim;

	path->PushBack({ 0 , 0 }, 10, &shoot2.anim);
	path->PushBack({ 1 , -1 }, 10, &shoot2.anim);
	path->PushBack({ 1.41f , -2 }, 10, &shoot2.anim);
	path->PushBack({ 1.73f, -3 }, 10, &shoot2.anim);
	path->PushBack({ 2, -4 }, 10, &shoot2.anim);
	path->PushBack({ 2.24f , -5}, 10, &shoot2.anim);
	


	explosion.anim.PushBack({ 0, 144, 16, 16 });
	explosion.anim.PushBack({ 17, 144, 16, 16 });
	explosion.anim.PushBack({ 33, 144, 16, 16 });
	explosion.anim.PushBack({ 49, 144, 16, 16 });
	explosion.anim.PushBack({ 65, 144, 16, 16 });
	explosion.anim.PushBack({ 81, 144, 16, 16 });
	explosion.anim.PushBack({ 97, 144, 16, 16 });
	explosion.anim.PushBack({ 113, 144, 16, 16 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.2f;

	explosion_bullet.anim.PushBack({ 80, 32, 16, 16 });
	explosion_bullet.anim.PushBack({ 97, 32, 16, 16 });
	explosion_bullet.anim.loop = false;
	explosion_bullet.anim.speed = 0.2f;

	Powerup.anim.PushBack({ 0, 120, 16, 16 });
	Powerup.anim.loop = false;
	Powerup.anim.speed = 0.2f;

	return ret;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	App->audio->UnloadS(shoot1.common_fx);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				p->speed.x = 2;
				App->audio->PlaySound(p->common_fx);
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			if(particle.id != 0){
			
				Particle* p = new Particle(particle);
				p->born = SDL_GetTicks() + delay;
				p->position.x = x;
				p->position.y = y;
				p->position = p->position + path->GetCurrentPosition(&animation);
				if (collider_type != COLLIDER_NONE)
					p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				active[i] = p;
				break;
			
				
				
			}else {	
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
			
			}
		}
	}
}


void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			AddParticle(explosion_bullet, c1->rect.x, c1->rect.y, COLLIDER_NONE);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
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
	fx(p.fx), born(p.born), life(p.life), common_fx(p.common_fx)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

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

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}