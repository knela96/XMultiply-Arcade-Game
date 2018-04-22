#ifndef __MODULESCENESTAGE1_H__
#define __MODULESCENESTAGE1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;

struct position {
	int x; int y;
};

class ModuleSceneStage1 : public Module
{
public:
	ModuleSceneStage1();
	~ModuleSceneStage1();

	bool Start();
	bool CleanUp();
	update_status Update();

public:
	int index = 0;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* back = nullptr;
	SDL_Texture* hud = nullptr;
	int font_gameover = -1;
	SDL_Texture* injectiontex = nullptr;
	SDL_Rect ground;
	SDL_Rect entering;
	struct position injectxy;
	Animation injection;
	SDL_Rect background;
	Animation flag;
	SDL_Rect ship;
	Animation people;
	Mix_Music* music;
	Uint32 start_time;
	Uint32 aux_time;
	int timer;
	SDL_Rect screen;
	char _stageendblit[12] = "";
	char _stageend[12] = "stage clear";

	bool down = false;

	bool right = false;

	bool injected = false;

	bool shipdeployed = false;

	void injectpos();

};

#endif // __MODULESCENESTAGE1_H__