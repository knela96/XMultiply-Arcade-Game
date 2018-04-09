#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 14

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModuleEnemy;
class ModuleAudio;
class ModuleParticles;
class ModuleFadeToBlack;
class ModuleSceneMainMenu;
class ModuleSceneChoosePlayer;
class ModuleSceneStage1;
class ModuleSceneStage2;
class ModuleSceneCongrats;

class Application
{
public:

	Module * modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModulePlayer* player = nullptr;
	ModuleEnemy* enemy = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleSceneMainMenu* scene_MainMenu;
	ModuleSceneChoosePlayer* scene_choosePlayer = nullptr;
	ModuleSceneStage1* scene_stage1 = nullptr;
	ModuleSceneStage2* scene_stage2 = nullptr;
	ModuleSceneCongrats* scene_congrats = nullptr;

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