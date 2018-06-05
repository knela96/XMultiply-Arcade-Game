#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_timer.h"
#include <cmath>


using namespace std;

ModuleParticles::ModuleParticles() : Module() {

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) {
		active[i] = nullptr;
	}

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
	graphics[PARTICLES_ENEMYSHOOT] = App->textures->Load("Assets/Sprites/Explosions/shots1.png");
	graphics[POWERUP] = App->textures->Load("Assets/Sprites/PowerUp/PowerUp.png");
	graphics[STAGE4BOSS_SHOOT] = App->textures->Load("Assets/Sprites/Stage4/Boss/boss4_3.png");

	basic_shoot.anim.PushBack({ 64, 32, 16, 16});
	basic_shoot.anim.loop = false;
	basic_shoot.anim.speed = 3.0f;
	basic_shoot.life = 2000;
	basic_shoot.type = BASIC_SHOOT;
	basic_shoot.fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-114.wav");
	basic_shoot.hit_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-079.wav");

	tentacle_shoot.anim.PushBack({ 112, 32, 16, 16 });
	tentacle_shoot.anim.loop = false;
	tentacle_shoot.anim.speed = 3.0f;
	tentacle_shoot.life = 2000;
	tentacle_shoot.type = TENTACLE_SHOOT;
	tentacle_shoot.hit_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-079.wav");

	bomb.anim.PushBack({ 0, 160, 16, 16 });
	bomb.anim.PushBack({ 16, 160, 16, 16 });
	bomb.anim.PushBack({ 32, 160, 16, 16 });
	bomb.anim.PushBack({ 48, 160, 16, 16 });
	bomb.anim.PushBack({ 64, 160, 16, 16 });
	bomb.anim.loop = false;
	bomb.life = 2000;
	bomb.anim.speed = 0.08f;
	bomb.type = BOMB_SHOOT;
	bomb.hit_fx = App->audio->LoadS("Assets/Audio Files/SFX in WAV/xmultipl-118.wav");
	
	basic_laser.anim.PushBack({ 0, 4, 23, 7 });
	basic_laser.anim.loop = false;
	basic_laser.anim.speed = 3.0f;
	basic_laser.type = BASIC_LASER;
	basic_laser.life = 2000;
	
	explosion_player.anim.PushBack({ 0, 175, 48, 65 });
	explosion_player.anim.PushBack({ 48, 175, 48, 65 });
	explosion_player.anim.PushBack({ 96, 175, 48, 65 });
	explosion_player.anim.PushBack({ 144, 175, 48, 65 });
	explosion_player.anim.PushBack({ 192, 175, 48, 65 });
	explosion_player.anim.loop = false;
	explosion_player.type = PLAYER_EXPLOSION;
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
	explosion_enemy.type = ENEMY_EXPLOSION;
	explosion_enemy.anim.speed = 0.2f;

	explosion_bullet.anim.PushBack({ 80, 32, 16, 16 });
	explosion_bullet.anim.PushBack({ 97, 32, 16, 16 });
	explosion_bullet.anim.loop = false;
	explosion_bullet.anim.speed = 0.2f;
	explosion_bullet.type = BASIC_SHOOT_EXPLOSION;

	explosion_tentacle_bullet.anim.PushBack({ 128, 32, 16, 16 });
	explosion_tentacle_bullet.anim.PushBack({ 144, 32, 16, 16 });
	explosion_tentacle_bullet.anim.PushBack({ 160, 32, 16, 16 });
	explosion_tentacle_bullet.anim.loop = false;
	explosion_tentacle_bullet.anim.speed = 0.2f;
	explosion_tentacle_bullet.type = TENTACLE_EXPLOSION;

	explosion_bomb.anim.PushBack({ 0, 0, 32, 32 });
	explosion_bomb.anim.PushBack({ 32, 0, 32, 32 });
	explosion_bomb.anim.PushBack({ 64, 0, 32, 32 });
	explosion_bomb.anim.PushBack({ 96, 0, 32, 32 });
	explosion_bomb.anim.loop = false;
	explosion_bomb.anim.speed = 0.2f;
	explosion_bomb.type = BOMB_EXPLOSION;

	Powerup.anim.PushBack({ 0, 120, 16, 16 });
	Powerup.anim.loop = true;
	Powerup.anim.speed = 0.2f;
	Powerup.type = NONE;

	anemona_shoot.anim.PushBack({ 3, 2, 8, 8});
	anemona_shoot.anim.PushBack({ 20, 2, 8, 8});
	anemona_shoot.anim.PushBack({ 3, 17, 8, 8});
	anemona_shoot.anim.PushBack({20, 17, 8, 8});
	anemona_shoot.anim.loop = true;
	anemona_shoot.anim.speed = 0.2f;
	anemona_shoot.type = ANEMONA_SHOOT;
	anemona_shoot.life = 2000;

	shrimp_shoot.anim.PushBack({ 3, 2, 8, 8 });
	shrimp_shoot.anim.PushBack({ 20, 2, 8, 8 });
	shrimp_shoot.anim.PushBack({ 3, 17, 8, 8 });
	shrimp_shoot.anim.PushBack({ 20, 17, 8, 8 });
	shrimp_shoot.anim.loop = true;
	shrimp_shoot.anim.speed = 0.2f;
	shrimp_shoot.type = SHRIMP_SHOOT;
	shrimp_shoot.life = 2000;

	spawn_missile.anim.PushBack({ 0, 64, 32, 16 });
	spawn_missile.anim.PushBack({ 0, 51, 32, 16 });
	missile.anim.loop = false;
	missile.anim.speed = 0.02f;
	missile.type = MISSILE_SHOOT;
	missile.life = 2000;

	missile.anim.PushBack({ 32, 51, 32, 16 });
	missile.anim.PushBack({ 64, 51, 32, 16 });
	missile.anim.loop = true;
	missile.anim.speed = 0.2f;
	missile.type = MISSILE_SHOOT;
	missile.life = 5000;

	explosion_missile.anim.PushBack({ 0,32,32,32 });
	explosion_missile.anim.PushBack({ 32,32,32,32 });
	explosion_missile.anim.PushBack({ 64,32,32,32 });
	explosion_missile.anim.PushBack({ 96,32,32,32 });
	explosion_missile.anim.PushBack({ 128,32,32,32 });
	explosion_missile.anim.PushBack({ 160,32,32,32 });
	explosion_missile.anim.loop = false;
	explosion_missile.anim.speed = 0.4f;
	explosion_missile.type = MISSILE_EXPLOSION;




	Stage4Boss_shoot.anim.PushBack({ 96, 137 ,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 2, 137 ,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 132, 137 ,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 49, 137 ,37,40 });




	// Phase 2 Boss shoot to repeat

	Stage4Boss_shoot.anim.PushBack({ 96,175,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 2,175,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 132,175,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 48,175,37,40 });

	// Phase 3 Boss shoot

	Stage4Boss_shoot.anim.PushBack({ 96,219,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 2,219,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 132,219,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 48,219,37,40 });

	// Phase 2 Boss shoot to repeat
	Stage4Boss_shoot.anim.PushBack({ 96,175,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 2,175,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 132,175,37,40 });

	Stage4Boss_shoot.anim.PushBack({ 48,175,37,40 });

	Stage4Boss_shoot.anim.loop = true;
	Stage4Boss_shoot.anim.speed = 0.4f;
	Stage4Boss_shoot.type = STAGE4BOSS_SHOOTN;
	Stage4Boss_shoot.life = 2000;
	

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

void ModuleParticles::removeParticles() {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}
}

update_status ModuleParticles::PostUpdate() {
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr) {
			if (active[i]->position.x * SCREEN_SIZE > App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + 50)
			{
				if (active[i]->type == MISSILE_SHOOT)
					active_missiles--;
				delete active[i];
				active[i] = nullptr;
			}
		}
	}
	return UPDATE_CONTINUE;
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
		else //if (SDL_GetTicks() >= p->born)
		{
			SDL_Texture* texture = nullptr;
			switch (p->type) {
			case BASIC_SHOOT:
			case BOMB_SHOOT:
			case TENTACLE_SHOOT:
				texture = graphics[PARTICLES_PLAYER];
				break;
			case BASIC_LASER:
				texture = graphics[PARTICLES_LASERS];
				break;
			case ENEMY_EXPLOSION:
			case BOMB_EXPLOSION:
				texture = graphics[PARTICLES_EXPLOSION];
				break;
			case ANEMONA_SHOOT:
				texture = graphics[PARTICLES_ENEMYSHOOT];
				break;
			case SHRIMP_SHOOT:
				texture = graphics[PARTICLES_ENEMYSHOOT];
				break;
			case MISSILE_SHOOT:
				texture = graphics[PARTICLES_PLAYER];
				MissilleMovement(p);
				break;
			case MISSILE_EXPLOSION:
				texture = graphics[PARTICLES_EXPLOSION];
				break;
			case STAGE4BOSS_SHOOTN:
				texture = graphics[STAGE4BOSS_SHOOT];
				break;
			default:
				texture = graphics[NONE];
				break;
			}



			if (p->fx_played == false)
			{
				switch (p->type) {
				case ENEMY_EXPLOSION:
				case PLAYER_EXPLOSION:
					p->speed.x = 1;
					break;
				case BASIC_SHOOT:
				case TENTACLE_SHOOT:
					p->speed.x = 7;
					break;
				case BOMB_SHOOT:
					p->speed.x = 5;
					p->speed.y = 0;
					break;
				case SHRIMP_SHOOT:
				case STAGE4BOSS_SHOOTN:
				case ANEMONA_SHOOT:
					p->speed.x = p->direction_speed.x;
					p->speed.y = p->direction_speed.y;
					break;
				}
				p->fx_played = true;
			}


			if (texture != nullptr) {
				App->render->Blit(texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()),1.0f,p->angle);
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::EnemyPositions(Particle *p) {
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		Enemy *enemy = App->enemies->enemies[i];
		if (enemy != nullptr) {
			int d = sqrt(pow(enemy->position.x - p->position.x, 2) + pow(enemy->position.y - p->position.y, 2));
			positions[i].x = d;
			positions[i].y = i;
		}
	}
	orderlist();
}

void ModuleParticles::orderlist() {
	int i, j, k;
	for (i = 0; i < MAX_ENEMIES - 1; i++)
	{
		for (k = i, j = i + 1; j < MAX_ENEMIES; j++)
			if (positions[j].x < positions[k].x && positions[j].x != 0 && positions[j].y != 0)
				k = j;
		if (k != i)
			swap(positions, i, k);
	}
}

void ModuleParticles::MissilleMovement(Particle *p) {

	if (p->target != nullptr) {
 		if (p->target->position.x < 0) {
  			p->target = nullptr;
			p->speed.x = 4;
			p->speed.y = 0;
			p->angle = 0.0f;
			EnemyPositions(p);
		}
	}

	Enemy* enemy = p->target;

	if (enemy == nullptr) {
		EnemyPositions(p);
		for (int i = 0; i < MAX_ENEMIES; ++i) {
			enemy = App->enemies->enemies[i];
			if (enemy != nullptr) {
				p->target = enemy;
				break;
			}
		}
	}
	if (enemy != nullptr) {
		double angle = atan2(enemy->position.y - p->position.y, enemy->position.x - p->position.x);
		p->angle = angle * 180 / PI;
		double dx = (double)(5 * cos(angle));
		double dy = (double)(5 * sin(angle));
		p->speed.x = dx;
		p->speed.y = dy;
	}
	else {
		p->speed.x = 4;
		p->speed.y = 0;
		p->angle = 0.0f;
	}
	
}


void ModuleParticles::swap(iPoint * positions, int i, int j)
{
	iPoint tmp = positions[i];
	positions[i] = positions[j];
	positions[j] = tmp;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, fPoint direction_speed, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->direction_speed = direction_speed;
			if (collider_type != COLLIDER_NONE) {
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			}
			active[i] = p;
			break;
			
		}
	}
}


void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	Particle *p;
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			p = active[i];
			switch (active[i]->type) {

			case BASIC_SHOOT:
				if (c2->type == COLLIDER_WALL)
					App->audio->PlaySound(p->hit_fx);
				p = &explosion_bullet;
				break;

			case TENTACLE_SHOOT:
				p = &explosion_tentacle_bullet;
				break;
			case BOMB_SHOOT:
				if (c2->type == COLLIDER_WALL)
					App->audio->PlaySound(p->hit_fx);
				p = &explosion_bomb;
				break;
			case MISSILE_SHOOT:
				if (c2->type == COLLIDER_WALL)
					App->audio->PlaySound(p->hit_fx);
				p = &explosion_missile;
				active_missiles--;
				break;
			default:
				p = nullptr;
			}
			if (p != nullptr) {
				p->speed.x = 1;
				AddParticle(*p, c1->rect.x, c1->rect.y);
			}
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
	fx(p.fx), born(p.born), life(p.life), type(p.type), hit_fx(p.hit_fx)
{}

Particle::~Particle()
{
	App->audio->UnloadS(fx);
	App->audio->UnloadS(hit_fx);
	if (collider != nullptr)
		collider->to_delete = true;

}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life) {
			ret = false;
			if (type == MISSILE_SHOOT)
				App->particles->active_missiles--;
		}
	}
	else
		if (anim.Finished() && type != PLAYER_EXPLOSION)
			ret = false;

	switch (type) {
	case BASIC_SHOOT:
	case TENTACLE_SHOOT:
	case MISSILE_SHOOT:
		position.x += speed.x;
		position.y += speed.y;
		break;
	case BOMB_SHOOT:
		if (speed.x > 2.0f) speed.x -= 0.055f;
		if (speed.y < 3.0f) speed.y += 0.25f;
		position.x += speed.x;
		position.y += speed.y;
		break;
	case SHRIMP_SHOOT:
		position.x += speed.x;
		position.y += speed.y;
		break;
	case STAGE4BOSS_SHOOTN:
		position.x += speed.x;
		position.y += speed.y;
		break;
	}

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}