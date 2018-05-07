#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_events.h"

typedef unsigned char Uint8;

#define MAX_KEYS 300

#define MAX_BUTTONS 12

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum CONTROLLER_BUTTONS {
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
	START,
	BACK,
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	STICK_X,
	STICK_Y
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	SDL_GameController* gGameController = NULL;
	bool controller_state[MAX_BUTTONS];
	KEY_STATE controller[MAX_BUTTONS];
	SDL_Event Events;
};

#endif // __ModuleInput_H__