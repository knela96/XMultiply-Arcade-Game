#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

#pragma comment (lib, "SDL_mixer/libx86/SDL2_mixer.lib")
#define MUS_PATH "Assets/Audio Files/Music in OGG/01_X-Multiply_Title_.ogg"

ModuleAudio::ModuleAudio() : Module()
{}

// Destructor
ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init()
{
	LOG("Init Audio SDL and library");

	bool ret = true;

	if (SDL_Init(SDL_INIT_AUDIO) < 0) 
	{
		LOG("SDL_AUDIO could not initialize! SDL_Error:\n");

		LOG(SDL_GetError());

		ret = false;
	}

	else {

		int init = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096); // frequency, Uint16 format, channel, chunksize

		if (init == -1)
		{
			LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
			ret = false;
		}

		//Load music and sound if everything initialized correctly

		music = Mix_LoadMUS(MUS_PATH);

		wave = Mix_LoadWAV("Assets/shoot.wav");

		if(wave==nullptr)
			LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		
		Mix_FadeInMusic(music, -1, 2000); //pointer to where the music is (already loaded), 0 don't play music and -1 to loop 
											//forever the music, milisecond in which the fade in enters
		
	}
	return ret;
}

void ModuleAudio::PlayShoot() {
	Mix_PlayChannel(-1, App->audio->wave, 0);
}

bool ModuleAudio::CleanUp() {

	Mix_FreeChunk(wave);

	Mix_FreeMusic(music);

	Mix_CloseAudio();

	return true;
}