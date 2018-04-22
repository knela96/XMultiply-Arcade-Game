#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"



class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack();
	~ModuleFadeToBlack();

	bool Start();
	update_status Update();
	bool FadeToBlack(Module* module_off, Module* module_on, float time = 2.0f);
	bool FadeToBlack(float time = 2.0f);
	bool FadeonlyBlack(float time = 2.0f);
	void resetStep();
	bool isBlack = false;
	bool isfadding = false;

private:
	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black,
		fade_only_black
	}current_step;
	Uint32 start_time = 0; 
	Uint32 total_time = 0;
	SDL_Rect screen;
	Module* module_off;
	Module* module_on;
	bool switch_scene = false;
};

#endif //__MODULEFADETOBLACK_H__