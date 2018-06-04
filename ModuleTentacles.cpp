#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleTentacles.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"


#include "SDL/include/SDL.h"
#include <stdio.h>
#include <windows.h>
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

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
	graphics = nullptr;

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
		}
		else {
			setPosition(App->player->position.x, App->player->position.y);
			p->collider->SetPos(p->first_point.x, p->first_point.y);
		}
	}
	return UPDATE_CONTINUE;
}

void ModuleTentacles::AddTentacle(const Tentacle& tentacle, int x, int y, float max_angle, bool flip, bool anchor)
{
	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		if (tentacles[i] == nullptr)
		{
			Tentacle* p = new Tentacle(tentacle);
			p->radian = PI/2;
			p->max_angle = max_angle;
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

void ModuleTentacles::RemoveTentacle(){
	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		if (tentacles[i] != nullptr)
		{
			delete tentacles[i]->collider;
			tentacles[i]->collider = nullptr;
			delete tentacles[i];
			tentacles[i] = nullptr;
		}
	}
}

/*void ModuleTentacles::setPosition(int x, int y) {
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
}*/

void ModuleTentacles::setPosition(int x, int y) {
	//SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	//SDL_RenderClear(App->render->renderer);
	//SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	int invert = 1;
	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		if (tentacles[i] != nullptr)
		{
			Tentacle* p = tentacles[i];
			if (i >= MAX_TENTACLES / 2) {
				invert = 1;
			}
			else {
				invert = -1;
			}
			LOG("%f", cos(p->radian));
			
			if (App->input->keyboard[SDL_SCANCODE_D]){
				if (p->radian < p->max_angle) {
					if (p->radian > 2 * PI)
						p->radian = 0;
					p->radian += 0.01f;
				}
			}
			else if(App->input->keyboard[SDL_SCANCODE_A]){
				if (p->radian > PI / 2 - (p->max_angle - PI / 2))
					p->radian -= 0.01f;
			}
			else {
				if (p->radian > PI / 2)
					p->radian -= 0.005f;
				else if (p->radian < PI / 2)
					p->radian += 0.005f;
			}
			
			if (i != 0 && i != MAX_TENTACLES / 2) {
				if (!p->anchor) {//Is last Node?
					p->first_point.x = tentacles[i - 1]->second_point.x;
					p->first_point.y = tentacles[i - 1]->second_point.y;
					p->second_point.x = p->first_point.x + int(cos(p->radian) * 10);
					p->second_point.y = p->first_point.y + int(sin(p->radian) * 10 * invert);
				}
				else {
					p->first_point.x = tentacles[i - 1]->second_point.x;
					p->first_point.y = tentacles[i - 1]->second_point.y;
					p->second_point.x = p->first_point.x;
					p->second_point.y = p->first_point.y;
				}
			}
			else if (i == 0 || i == MAX_TENTACLES / 2) {
				if (!p->flip) {
					p->first_point.y = y + (8 - p->anim.frames->h);
				}
				else {
					p->first_point.y = y + (20 - p->anim.frames->h);
				}
				p->first_point.x = x + 16;
				p->second_point.x = p->first_point.x + int(cos(p->radian) * 11);
				p->second_point.y = p->first_point.y + int(sin(p->radian) * 11 * invert);
			}
			//SDL_RenderDrawLine(App->render->renderer, p->first_point.x, p->first_point.y, p->second_point.x, p->second_point.y);

			tentacles[i] = p;
		}
	}
}

void ModuleTentacles::BlitTentacles() {
	for (uint i = 0; i < MAX_TENTACLES; ++i)
	{
		Tentacle* p = tentacles[i];
		if (p->anchor) {
			App->render->Blit(graphics, p->first_point.x, p->first_point.y, &p->anim.GetCurrentFrame(), 1.0f, 0.0f);
		}
		else if (p->flip) {
			App->render->Blit(graphics, p->first_point.x, p->first_point.y, &p->anim.GetCurrentFrame(), 1.0f, 90 + (180 * p->radian) / PI, true, true);
			LOG("%f", tentacles[0]->radian * 180 / PI);
		}
		else {
			App->render->Blit(graphics, p->first_point.x, p->first_point.y, &p->anim.GetCurrentFrame(), 1.0f, 90 + (180 * p->radian) / PI * -1);
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
