#ifndef __MODULESCENESCENETEST_H__
#define __MODULESCENESCENETEST_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;

class ModuleSceneTest : public Module
{
public:
	ModuleSceneTest();
	~ModuleSceneTest();

	bool Start();
	update_status Update();
	bool CleanUp();
};

#endif // __MODULESCENEMAINMENU_H__