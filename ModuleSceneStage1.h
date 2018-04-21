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
<<<<<<< HEAD
	//Mix_Music * music = nullptr;
	int font_gameover = -1;
=======
	SDL_Texture* injectiontex = nullptr;
	//Mix_Music * music = nullptr;;
>>>>>>> c3369ed3c412af67132479a9a5ba0ca01e2551f9
	SDL_Rect ground;
	SDL_Rect entering;

	struct position injectxy;

	Animation injection;
	SDL_Rect background;
<<<<<<< HEAD
	Animation flag;
	SDL_Rect ship;
	Animation people;
	Uint32 start_time;
=======

	bool down = false;

	bool right = false;

	bool injected = false;

	bool shipdeployed = false;

	void injectpos();
>>>>>>> c3369ed3c412af67132479a9a5ba0ca01e2551f9
};

#endif // __MODULESCENESTAGE1_H__