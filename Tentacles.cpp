#include "Application.h"
#include "Enemy.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Tentacles.h"

Tentacles::Tentacles(int x, int y):first_point(x,y)
{}

Tentacles::~Tentacles()
{}

void Tentacles::Draw(SDL_Texture * sprites)
{
	App->render->Blit(sprites, first_point.x, first_point.y, rect);
}
