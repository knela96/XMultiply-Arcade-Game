#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 12

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModuleEnemy;
class ModuleAudio;
class ModuleBackground;
class ModuleSceneKen;
class ModuleSceneHonda;
class ModuleProjectile;
class Module;
class ModuleFadeToBlack;

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
	ModuleSceneHonda* scene_honda;
	ModulePlayer* player = nullptr;
	ModuleEnemy* enemy = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleProjectile* projectile = nullptr;
	ModuleFadeToBlack* fade = nullptr;

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