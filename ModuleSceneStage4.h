#ifndef __MODULESCENESTAGE4_H__
#define __MODULESCENESTAGE4_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

class ModuleSceneStage4 : public Module
{
public:
	ModuleSceneStage4();
	~ModuleSceneStage4();
	void resetMap();
	void AddEnemies();
	bool Start();
	bool CleanUp();
	update_status Update();
	void disableModules();
	void enableModules();

public:
	uint index1 = 0;
	uint index2 = 0;

	SDL_Texture* graphics = nullptr;
	SDL_Texture* back = nullptr;
	SDL_Texture* hud = nullptr;
	int font_gameover = -1;
	SDL_Rect ground_top;
	SDL_Rect ground_bottom;
	SDL_Rect ship;
	SDL_Rect background;

	bool resetmap = false;
	bool cleaned = false;
	bool show = false;

	Animation flag;
	Animation people;
	Mix_Music* music;
	Mix_Music* clear_stage;
	Uint32 start_time;
	Uint32 aux_time;
	int rgb = 255;

	SDL_Rect screen;

	char _stageendblit[12] = "";

	char _stageend[12] = "stage clear";

	char _stageend2[18] = "stage bonus 10000";

	char _stageendblit2[18] = "";

	bool right = false;

private:
	bool clearstage_fx;
};

#endif // __MODULESCENESTAGE4_H__
