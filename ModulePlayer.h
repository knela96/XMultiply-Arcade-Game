#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
typedef unsigned int Uint32;
class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation upward;
	Animation downward;
	Animation upwardreturn;
	Animation downwardreturn;
	Animation* current_animation;
	SDL_Rect r;
	iPoint position;

};

#endif