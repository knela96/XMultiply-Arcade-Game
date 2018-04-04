#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 11

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModuleEnemy;
class ModuleAudio;
class ModuleBackground;
class ModuleProjectile;
class ModuleFadeToBlack;
class ModuleSceneKen;
class ModuleSceneMainMenu;
class ModuleSceneChoosePlayer;

class Application
{
public:

	Module * modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleBackground* background = nullptr;
	ModuleSceneKen* scene_ken;
	ModuleSceneMainMenu* scene_MainMenu;
	ModulePlayer* player = nullptr;
	ModuleEnemy* enemy = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleProjectile* projectile = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleSceneChoosePlayer* scene_choosePlayer = nullptr;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__