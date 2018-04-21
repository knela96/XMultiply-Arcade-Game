#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleTentacles.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

ModuleTentacles::ModuleTentacles()
{}

ModuleTentacles::~ModuleTentacles()
{}

bool ModuleTentacles::Start() {

	LOG("Loading tentacle textures");

	graphics = App->textures->Load("Assets/Player.png");
	tentacle.anim.PushBack({ 6,	19, 4, 11 });
	tentacle.anim.loop = false;
	tentacle.anim.speed = 0.0f;

	anchor_bottom.anim.PushBack({ 10, 32, 19, 14 });
	anchor_bottom.anim.PushBack({ 218, 16, 19, 14 });
	anchor_bottom.anim.PushBack({ 186, 16, 19, 14 });
	anchor_bottom.anim.PushBack({ 154, 16, 19, 14 });
	anchor_bottom.anim.PushBack({ 122, 16, 19, 14 });
	anchor_bottom.anim.PushBack({ 90, 16, 19, 14 });
	anchor_bottom.anim.loop = true;
	anchor_bottom.anim.speed = 0.2f;

	anchor_top.anim.PushBack({ 90, 16, 19, 14 });
	anchor_top.anim.PushBack({ 122, 16, 19, 14 });
	anchor_top.anim.PushBack({ 154, 16, 19, 14 });
	anchor_top.anim.PushBack({ 186, 16, 19, 14 });
	anchor_top.anim.PushBack({ 218, 16, 19, 14 });
	anchor_top.anim.PushBack({ 10, 32, 19, 14 });
	anchor_top.anim.loop = true;
	anchor_top.anim.speed = 0.2f;

	return true;
}

bool ModuleTentacles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		if (tentacles[i] != nullptr)
		{
			delete tentacles[i];
			tentacles[i] = nullptr;
		}
	}

	return true;
}

void ModuleTentacles::removeCollider() {
	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		Tentacle* p = tentacles[i];
		if (p->collider!= nullptr)
		{
			p->collider->to_delete = true;
		}
	}

}

update_status ModuleTentacles::Update() {
	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		Tentacle* p = tentacles[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			tentacles[i] = nullptr;
		}else{
			setPosition(App->player->position.x, App->player->position.y);
			p->collider->SetPos(p->first_point.x, p->first_point.y);
			if(p->flip)
				App->render->Blit(graphics, p->first_point.x, p->first_point.y, &p->anim.GetCurrentFrame(),1.0f, 180.0f,true,true);
			else
				App->render->Blit(graphics, p->first_point.x, p->first_point.y, &p->anim.GetCurrentFrame(), 1.0f, 0.0f);

		}
	}
	return UPDATE_CONTINUE;
}

void ModuleTentacles::AddTentacle(const Tentacle& tentacle, int x, int y, bool flip, bool anchor)
{
	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		if (tentacles[i] == nullptr)
		{
			Tentacle* p = new Tentacle(tentacle);
			
			p->flip = flip;
			p->anchor = anchor;
			p->first_point.x = x;
			p->first_point.y = y;
			p->collider = App->collision->AddCollider({ p->first_point.x, p->first_point.y,p->anim.frames->w, p->anim.frames->h }, COLLIDER_PLAYER, this);
			tentacles[i] = p;
			break;
		}
	}
}

void ModuleTentacles::setPosition(int x, int y) {
	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		if (tentacles[i] != nullptr)
		{
			int invert = 0;
			Tentacle* p = tentacles[i];
			if (i >= MAX_TENTACLES/2)
				invert = -1;
			else
				invert = 1;

			if (i != 0 && i != MAX_TENTACLES/2) {
				if (!p->anchor) {
					p->first_point.x = tentacles[i - 1]->second_point.x;
					p->first_point.y = tentacles[i - 1]->second_point.y;
					p->second_point.x = p->first_point.x;
					p->second_point.y = p->first_point.y - p->anim.frames->h * invert;
				}
				else {
					p->first_point.x = tentacles[i - 1]->second_point.x - 12;
					p->first_point.y = tentacles[i - 1]->second_point.y + (p->anim.frames->h/2 * invert);
				}
			}
			else if(i==0 || i == MAX_TENTACLES/2){
				if (!tentacles[i]->flip) {
					p->first_point.y = y + (6 - p->anim.frames->h);
				}
				else {
					p->first_point.y = y + (21 - p->anim.frames->h);
				}
				p->first_point.x = x + 21;
				p->second_point.x = p->first_point.x;
				p->second_point.y = p->first_point.y - p->anim.frames->h * invert;
			}

			tentacles[i] = p;
		}
	}
}

void ModuleTentacles::ShootLaser() {
	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		if (tentacles[i] != nullptr)
		{
			Tentacle* p = tentacles[i];
			if (p->anchor) {
				App->particles->AddParticle(App->particles->tentacle_shoot, p->first_point.x, p->first_point.y - 5, COLLIDER_PLAYER_SHOT);
			}
		}
	}
}


//--------------------------------------------
//--------------------------------------------

Tentacle::Tentacle()
{
	first_point.SetToZero();
}

Tentacle::Tentacle(const Tentacle& p) :
	first_point(p.first_point), second_point(p.second_point), 
	anchor(p.anchor), anim(p.anim)
{}

bool Tentacle::Update()
{
	bool ret = true;


	return ret;
}
