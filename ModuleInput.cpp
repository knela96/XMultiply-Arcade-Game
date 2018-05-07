#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;

	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		ret = false;
	}

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_NumJoysticks() < 1)
	{
		LOG("Warning: No joysticks connected!\n");
	}
	else
	{
		//Load joystick
		gGameController = SDL_GameControllerOpen(0);
		if (gGameController == NULL)
		{
			LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	controller_state[UP] = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_DPAD_UP);
	controller_state[DOWN] = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	controller_state[LEFT] = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	controller_state[RIGHT] = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	controller_state[BUTTON_A] = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_A);
	controller_state[BUTTON_B] = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_B);
	controller_state[BUTTON_X] = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_X);
	controller_state[BUTTON_Y] = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_Y);
	controller_state[START] = SDL_GameControllerGetButton(gGameController, SDL_CONTROLLER_BUTTON_START);

	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (controller_state[i] == 1) {
			if (controller[i] == KEY_IDLE)
				controller[i] = KEY_DOWN;
			else
				controller[i] = KEY_REPEAT;
		}
		else
		{
			if (controller[i] == KEY_REPEAT || controller[i] == KEY_DOWN)
				controller[i] = KEY_UP;
			else
				controller[i] = KEY_IDLE;
		}
	}

	if(keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	SDL_PumpEvents();
	while (SDL_PollEvent(&Events))
	{
		if (Events.type == SDL_QUIT) {
			return update_status::UPDATE_STOP;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	SDL_GameControllerClose(gGameController);
	gGameController = NULL;


	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}