#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

#ifdef _WIN32
#include "SDL_mixer/include/SDL_mixer.h"
#else
#include "SDL_mixer.h"
#endif

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 200

//struct Mix_Chunk;

//typedef struct _Mix_Music Mix_Music;


class ModuleAudio : public Module 
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

//	bool PlayMusic(Mix_Music* music);
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	
	//bool PlaySound(Mix_Chunk * wave);

	// Load a WAV in memory
	uint LoadFx(const char* path);
	bool UnLoadFx(uint id);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

public:

	Mix_Music * music = nullptr;
	Mix_Chunk*	fx[MAX_FX];
	uint			last_fx = 1;

/*	Mix_Music * const LoadM(const char* path);
	bool UnloadM(Mix_Music * music);

	Mix_Chunk * const LoadS(const char * path);
	bool UnloadS(Mix_Chunk * sound);
	*/
};



#endif //_ModuleAudio_H__
