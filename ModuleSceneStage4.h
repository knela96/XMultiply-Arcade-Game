#ifndef __MODULESCENESTAGE4_H__
#define __MODULESCENESTAGE4_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

class ModuleSceneStage4 : public Module
{
public:
	ModuleSceneStage4();
	~ModuleSceneStage4();
	void resetMap();
	void enter();
	void AddEnemies();
	bool Start();
	bool CleanUp();
	update_status Update();
	void disableModules();
	void enableModules();
	void moveTop(bool up, int i);
	void moveBot(bool up, int i);
	

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
	SDL_Rect lifes;
	SDL_Rect background;

	bool resetmap = false;
	bool entering = false;
	bool cleaned = false;
	bool show = false;
	bool loose = false;
	bool shipdone;
	bool moveT;
	bool moveB;
	bool up;
	int position;

	Animation flag;
	Animation people;
	Mix_Music* music;
	Mix_Music* clear_stage;
	Uint32 start_time = -1;
	Uint32 aux_time = -1;
	bool boss_phase2 = false;
	bool move_head = false;
	int current_frame = 0;
	int rgb = 255;
	int lifes_Boss = 40;

	SDL_Rect screen;

	char _stageendblit[12] = "";

	char _stageend[12] = "stage clear";

	char _stageend2[18] = "stage bonus 10000";

	char _stageendblit2[18] = "";

	bool right = false;

	int ground_top_y;
	int ground_bottom_y;
	Uint32 boss_time;
	Uint32 fight_time;
	Collider* CollidersTop1;
	Collider* CollidersTop2;
	Collider* CollidersTop3;
	Collider* CollidersTop4;
	Collider* CollidersTop5;
	Collider* CollidersTop6;
	Collider* CollidersTop7;
	Collider* CollidersTop8;
	Collider* CollidersTop9;
	Collider* CollidersTop10;
	Collider* CollidersTop11;
	Collider* CollidersTop12;
	Collider* CollidersTop13;
	Collider* CollidersTop14;
	Collider* CollidersTop15;
	Collider* CollidersTop16;
	Collider* CollidersTop17;
	Collider* CollidersTop18;
	Collider* CollidersTop19;
	Collider* CollidersTop20;
	Collider* CollidersTop21;
	Collider* CollidersTop22;

	Collider* BigColliderBot;
	Collider* ColliderBot1;
	Collider* ColliderBot2;
	Collider* ColliderBot3;
	Collider* ColliderBot4;
	Collider* ColliderBot5;
	Collider* ColliderBot6;
	Collider* ColliderBot7;
	Collider* ColliderBot8;
	Collider* ColliderBot9;
	Collider* ColliderBot10;
	Collider* ColliderBot11;
	Collider* ColliderBot12;
	Collider* ColliderBot13;
	Collider* ColliderBot14;
	Collider* ColliderBot15;
	Collider* ColliderBot16;
	Collider* ColliderBot17;
	Collider* ColliderBot18;
	Collider* ColliderBot19;
	Collider* ColliderBot20;
	Collider* ColliderBot21;
	Collider* ColliderBot22;

private:
	bool clearstage_fx;
};

#endif // __MODULESCENESTAGE4_H__
