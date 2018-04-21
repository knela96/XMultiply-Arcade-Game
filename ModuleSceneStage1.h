#ifndef __MODULESCENESTAGE1_H__
#define __MODULESCENESTAGE1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

struct position {
	int x; int y;
};
//typedef struct _Mix_Music Mix_Music;

class ModuleSceneStage1 : public Module
{
public:
	ModuleSceneStage1();
	~ModuleSceneStage1();

	bool Start();
	bool CleanUp();
	update_status Update();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Texture* back = nullptr;
	SDL_Texture* hud = nullptr;

	//Mix_Music * music = nullptr;
	int font_gameover = -1;

	SDL_Texture* injectiontex = nullptr;
	//Mix_Music * music = nullptr;;

	SDL_Rect ground;
	SDL_Rect entering;

	struct position injectxy;

	Animation injection;
	SDL_Rect background;

	Animation flag;
	SDL_Rect ship;
	Animation people;
	Uint32 start_time;
	SDL_Rect screen;

	bool down = false;

	bool right = false;

	bool injected = false;

	bool shipdeployed = false;

	void injectpos();

};

#endif // __MODULESCENESTAGE1_H__