#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;
typedef struct _Mix_Music Mix_Music;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* collider1, Collider* collider2);
	void resetPlayer();

public:
	bool enable_movement = false;
	bool nitroanim = false;
	int counter = 0;
	int speed = 2;
	SDL_Texture * graphics = nullptr;
	int font_score = -1;
	int font_gameover = -1;
	char score_text[10];
	uint score = 100;
	Mix_Chunk* death_fx;
	Mix_Music* music;
	Animation idle;
	Animation forward;
	Animation nitro;
	Animation backward;
	Animation upward;
	Animation downward;
	Animation upwardreturn;
	Animation downwardreturn;
	Animation* current_animation;
	iPoint position;
	iPoint camera_offset;
	Uint32 start_time;
	Uint32 aux_time;
	Collider* collider;
	bool powerup[20];
	bool dead = false;
	bool godmode = false;
	int text_delay;
	bool AddTentacles();
	uint life = 3;
	char _godmode[8] = "godmode";
};

#endif