#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;


class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* collider1, Collider* collider2);

public:

	SDL_Texture * graphics = nullptr;
	int font_score = -1;
	int font_gameover = -1;
	char score_text[10];
	uint score = 0;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation upward;
	Animation downward;
	Animation upwardreturn;
	Animation downwardreturn;
	Animation* current_animation;
	iPoint position;
	Uint32 start_time; 
	Collider* collider;
	bool powerup[20];
	bool dead = false;
	bool life[3];
};

#endif