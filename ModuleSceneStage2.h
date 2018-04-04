#ifndef __MODULESCENESTAGE2_H__
#define __MODULESCENESTAGE2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneStage2 : public Module
{
public:
	ModuleSceneStage2();
	~ModuleSceneStage2();

	bool Start();
	bool CleanUp();
	update_status Update();

public:

	SDL_Texture * graphics = nullptr;
	SDL_Texture* back = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	Animation flag;
	SDL_Rect ship;
	Animation people;
	int ScrollingOffset = 0;

};

#endif // __MODULESCENESTAGE1_H__
