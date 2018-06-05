#include "Globals.h"
#include "Application.h"
#include "ModulePowerUp.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_timer.h"

ModulePowerUp::ModulePowerUp() : Module() {

	for (uint i = 0; i < MAX_POWERUP; ++i) {
		active[i] = nullptr;
	}

}

ModulePowerUp::~ModulePowerUp() {}

// Called before render is available
bool ModulePowerUp::Start()
{
	bool ret = true;

	LOG("Loading player textures");

	graphics = App->textures->Load("Assets/Sprites/PowerUp/PowerUp.png");

	bomb_powerup.anim.PushBack({ 101, 56, 21, 16 });
	bomb_powerup.anim.PushBack({ 229, 56, 21, 16 });
	bomb_powerup.anim.loop = true;
	bomb_powerup.anim.speed = 0.2f;
	bomb_powerup.type = BOMB_POWERUP;
	bomb_powerup.enabled = false;


	tentacles_powerup.anim.PushBack({ 69, 57, 18, 15 });
	tentacles_powerup.anim.PushBack({ 197, 58, 18, 15 });
	tentacles_powerup.anim.loop = true;
	tentacles_powerup.anim.speed = 0.2f;
	tentacles_powerup.type = TENTACLES_POWERUP;
	tentacles_powerup.enabled = false;

	speed_powerup.anim.PushBack({68, 74, 24, 13});
	speed_powerup.anim.PushBack({164, 74, 24, 13});
	speed_powerup.anim.loop = true;
	speed_powerup.anim.speed = 0.2f;
	speed_powerup.type = SPEED_POWERUP;
	speed_powerup.enabled = false;


	YellowShells.anim.PushBack({ 0,0,18,15 });
	YellowShells.anim.PushBack({ 0,0,18,15 });
	YellowShells.anim.loop = true;
	YellowShells.anim.speed = 0.2f;
	YellowShells.type = ORB_POWERUP;
	YellowShells.enabled = false;


	return ret;
}

// Unload assets
bool ModulePowerUp::CleanUp()
{
	LOG("Unloading particles");
	
	App->textures->Unload(graphics);
	graphics = nullptr;

	for (uint i = 0; i < MAX_POWERUP; ++i)
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
update_status ModulePowerUp::Update()
{
	for (uint i = 0; i < MAX_POWERUP; ++i)
	{
		PowerUp* p = active[i];

		if (p == nullptr)
			continue;

		p->Update();

		App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
		
	}

	return UPDATE_CONTINUE;
}


void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_POWERUP; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1 && active[i]->enabled)
		{
			active[i]->PU_Effect();

			delete active[i];

			active[i] = nullptr;

			break;
		}

	}
}

PowerUp* ModulePowerUp::AddPowerUp(const PowerUp & powerup, int x, int y, COLLIDER_TYPE collider_type)
{
	for (uint i = 0; i < MAX_POWERUP; ++i)
	{
		if (active[i] == nullptr)
		{
			PowerUp* p = new PowerUp(powerup);
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			return p;
			break;
		}
	}
}


PowerUp::PowerUp()
{
}

PowerUp::PowerUp(const PowerUp& p) :
	anim(p.anim), position(p.position), type(p.type), enabled(p.enabled)
{}

PowerUp::~PowerUp()
{
	if (collider != nullptr)
		collider->to_delete = true;
}


bool PowerUp::Update()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (!enabled)
	{
		position.x--;
	}

	return true;
}

void PowerUp::PU_Effect()
{
	switch (type)
	{
	case TENTACLES_POWERUP:
		App->player->AddTentacles();
		break;
	case BOMB_POWERUP:
		App->player->powerup[BOMB_SHOOT] = true;
		break;
	case SPEED_POWERUP:
		App->player->speed += 1;
		App->player->nitroanim = true;
		break;
	case ORB_POWERUP:
		App->player->powerup[ORB] = true;
	}
}