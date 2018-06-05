#ifndef __MODULESCENESCORE_H__
#define __MODULESCENESCORE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

struct PlayerScore {
	int score;
	char* name;
};

class ModuleSceneScore : public Module
{
public:
	ModuleSceneScore();
	~ModuleSceneScore();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int rgb;
	bool color = true;
	SDL_Texture* graphics = nullptr;
	SDL_Rect background; 
	Uint32 start_time = 0;
	Uint32 text_delay = 0;
	PlayerScore * ranking[5];
	PlayerScore * ranking_names[4];
	int font_gameover2 = -1;
	int font_gameover1 = -2;
	char _stageendblit[5][12];
	char _stagenamesblit[5][12];
	int i = 0, j = 0, index_player = 5;
};

#endif // __MODULESCENECHOOSEPLAYER_H__