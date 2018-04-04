#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	//ground
	ground.x = 0;
	ground.y = 0;
	ground.w = 512;
	ground.h = 512;

	// Background / sky
	background.x = 0;
	background.y = 1;
	background.w = 4961;
	background.h = 513;

	//// flag animation
	//flag.PushBack({848, 208, 40, 40});
	//flag.PushBack({848, 256, 40, 40});
	//flag.PushBack({848, 304, 40, 40});
	//flag.speed = 0.08f;

	////ship

	//ship.x = 0 ;
	//ship.y = 0 ;
	//ship.w = 525;
	//ship.h = 200 ;

	//// girl animation
	//people.PushBack({ 619,16,37,57 });
	//people.PushBack({ 619,80,37,57 });
	//people.PushBack({ 619,144,37,57 });
	//people.PushBack({ 619,80,37,57 });
	//people.speed = 0.1f;

	
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Assets/TileMap.png");
	back = App->textures->Load("Assets/FirstLvlMap3.png");
	
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	--ScrollingOffset;
	if (ScrollingOffset < -512)
	{
		ScrollingOffset = 0;
	}


	App->render->Blit(back, ScrollingOffset, 0, &ground, 0.1f);
	App->render->Blit(back, ScrollingOffset + 512, 0, &ground, 0.1f);


	App->render->Blit(graphics, 0, 0, &background);
	
	
	

	return UPDATE_CONTINUE;
}