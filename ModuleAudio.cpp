#include "Application.h"
#include "ModuleAudio.h"

#ifdef _WIN32
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
#else
#include "SDL.h"
#include "SDL_mixer.h"
#endif

ModuleAudio::ModuleAudio()
{
	for (uint i = 0; i < MAX_FX; ++i)
		fx[i] = nullptr;
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Init()
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// load support for the OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	for (uint i = 0; i < MAX_FX; ++i)
		if (fx[i] != nullptr)
			Mix_FreeChunk(fx[i]);

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

// Play a music file
bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
uint ModuleAudio::LoadFx(const char* path)
{
	uint ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx[last_fx] = chunk;
		ret = last_fx++;
	}

	return ret;
}

// UnLoad WAV
bool ModuleAudio::UnLoadFx(uint id)
{
	bool ret = false;

	if (fx[id] != nullptr)
	{
		Mix_FreeChunk(fx[id]);
		fx[id] = nullptr;
		ret = true;
	}

	return ret;
}

// Play WAV
bool ModuleAudio::PlayFx(uint id, int repeat)
{
	bool ret = false;

	if (fx[id] != nullptr)
	{
		Mix_PlayChannel(-1, fx[id], repeat);
		ret = true;
	}

	return ret;
}


/*

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

		//int init = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096); // frequency, Uint16 format, channel, chunksize
		int init = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024); //Reduces buffer and lag of the sound_fx
		if (init == -1)
		{
			LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
			ret = false;
		}


	}
	return ret;
}

Mix_Music* const ModuleAudio::LoadM(const char* path)
{
	Mix_Music* music = nullptr;
	music = Mix_LoadMUS(path);
	return music;
}
bool ModuleAudio::UnloadM(Mix_Music * music) 
{
	if (music != nullptr)
		Mix_FreeMusic(music);
	return true;
}
Mix_Chunk *const ModuleAudio::LoadS(const char* path)
{
	Mix_Chunk* wave = nullptr;
	wave = Mix_LoadWAV(path);
	return wave;
}
bool ModuleAudio::UnloadS(Mix_Chunk * sound)
{
	if (sound != nullptr)
		//Mix_FreeChunk(sound);
	return true;
}

bool ModuleAudio::PlayMusic(Mix_Music* music)
{

	Mix_FadeInMusic(music, -1, 2000); //pointer to where the music is (already loaded), 0 don't play music and -1 to loop 
									  //forever the music, milisecond in which the fade in enters
	return true;
}

bool ModuleAudio::PlaySound(Mix_Chunk* wave)
{
	Mix_PlayChannel(-1, wave, 0);
	return true;
}

bool ModuleAudio::CleanUp() {

	Mix_CloseAudio();

	return true;
}*/