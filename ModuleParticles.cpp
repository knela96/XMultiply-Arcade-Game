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
	
	graphics[PARTICLES_PLAYER] = App->textures->Load("Assets/Sprites/Character/Player.png");
	graphics[PARTICLES_LASERS] = App->textures->Load("Assets/Sprites/Character/Lasers.png");
	graphics[PARTICLES_EXPLOSION] = App->textures->Load("Assets/Sprites/Explosions/Explosions1.png");
	graphics[POWERUP] = App->textures->Load("Assets/PowerUp/PowerUp.png");

	shoot1.anim.PushBack({ 64, 30, 17, 18});
	shoot1.anim.loop = false;
	shoot1.anim.speed = 3.0f;
	shoot1.life = 2000;
	shoot1.fx = App->audio->LoadFx("Assets/Audio Files/SFX in WAV/xmultipl-114.wav");

	shoot2.anim.PushBack({ 50, 82, 12, 18 });
	shoot2.anim.loop = false;
	shoot2.anim.speed = 3.0f;
	shoot2.life = 2000;
	shoot2.fx = App->audio->LoadFx("Assets/Audio Files/SFX in WAV/xmultipl-114.wav");

	basic_laser.anim.PushBack({ 64, 30, 17, 18 });
	basic_laser.anim.loop = false;
	basic_laser.anim.speed = 3.0f;
	basic_laser.life = 2000;
	basic_laser.fx = App->audio->LoadFx("Assets/Audio Files/SFX in WAV/xmultipl-114.wav");

	animation = &shoot2.anim;

	path->PushBack({ 0 , 0 }, 1, &shoot2.anim);
	path->PushBack({ 1 , 1 }, 1, &shoot2.anim);
	path->PushBack({ 1.41f , 2 }, 1, &shoot2.anim);
	path->PushBack({ 1.73f, 3 }, 1, &shoot2.anim);
	path->PushBack({ 2, 4 }, 1, &shoot2.anim);
	path->PushBack({ 2.24f , 5 }, 1, &shoot2.anim);


	basic_laser.anim.PushBack({ 0, 4, 23, 7 });
	basic_laser.anim.loop = false;
	basic_laser.anim.speed = 3.0f;
	basic_laser.life = 2000;

	animation = &shoot2.anim;
	
	explosion_player.anim.PushBack({ 0, 144, 16, 16 });
	explosion_player.anim.PushBack({ 17, 144, 16, 16 });
	explosion_player.anim.PushBack({ 33, 144, 16, 16 });
	explosion_player.anim.PushBack({ 49, 144, 16, 16 });
	explosion_player.anim.PushBack({ 65, 144, 16, 16 });
	explosion_player.anim.PushBack({ 81, 144, 16, 16 });
	explosion_player.anim.PushBack({ 97, 144, 16, 16 });
	explosion_player.anim.PushBack({ 113, 144, 16, 16 });
	explosion_player.anim.loop = false;
	explosion_player.anim.speed = 0.2f;

	explosion_enemy.anim.PushBack({ 0, 64, 32, 48 });
	explosion_enemy.anim.PushBack({ 32, 64, 32, 48 });
	explosion_enemy.anim.PushBack({ 64, 64, 48, 48 });
	explosion_enemy.anim.PushBack({ 112, 64, 48, 48 });
	explosion_enemy.anim.PushBack({ 160, 64, 48, 48 });
	explosion_enemy.anim.PushBack({ 0, 112, 48, 48 });
	explosion_enemy.anim.PushBack({ 97, 112, 48, 48 });
	explosion_enemy.anim.PushBack({ 113, 112, 48, 48 });
	explosion_enemy.anim.loop = false;
	explosion_enemy.anim.speed = 0.2f;

	explosion_bullet.anim.PushBack({ 80, 32, 16, 16 });
	explosion_bullet.anim.PushBack({ 97, 32, 16, 16 });
	explosion_bullet.anim.loop = false;
	explosion_bullet.anim.speed = 0.2f;

	Powerup.anim.PushBack({ 0, 120, 16, 16 });
	Powerup.anim.loop = true;
	Powerup.anim.speed = 0.2f;

	return ret;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	for (uint i = 0; i < MAX_TEXTURES; ++i) {
		if (graphics[i] != nullptr)
		{
			App->textures->Unload(graphics[i]);
		}
	}

	App->audio->UnLoadFx(shoot1.fx);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr && active[i] != &Powerup)
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
			SDL_Texture* texture = nullptr;
			switch (p->type) {
			case PARTICLES_PLAYER:
				texture = graphics[PARTICLES_PLAYER];
				break;
			case PARTICLES_LASERS:
				texture = graphics[PARTICLES_LASERS];
				break;
			case PARTICLES_EXPLOSION:
				texture = graphics[PARTICLES_EXPLOSION];
				break;
			default:
				texture = graphics[NONE];
				break;
			}
			if(texture != nullptr)
 				App->render->Blit(texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if (p->fx_played == false)
			{
				if (p->type == PARTICLES_EXPLOSION || p->type == POWERUP)
					p->speed.x = 1;
				else
					p->speed.x = 3;
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, PARTICLE_TYPE type, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle, type);
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


void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	PARTICLE_TYPE bullet_type = NONE;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			switch (active[i]->type) {
			case PARTICLES_PLAYER:
				bullet_type = PARTICLES_PLAYER;
				break;
			case PARTICLES_LASERS:
				bullet_type = PARTICLES_LASERS;
				break;
			}
			AddParticle(explosion_bullet,bullet_type, c1->rect.x, c1->rect.y, COLLIDER_NONE);
			
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

Particle::Particle(const Particle& p, PARTICLE_TYPE type) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life), type(type)//, common_fx(p.common_fx)
{}

Particle::~Particle()
{
	if (collider != nullptr /*&& collider->gettype != COLLIDER_POWERUP*/)
		collider->to_delete = true; //BUG quan sona el sonido de dispar i es presiona ESC
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