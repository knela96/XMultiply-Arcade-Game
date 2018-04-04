#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"

struct Mix_Chunk;

typedef struct _Mix_Music Mix_Music;


class ModuleAudio : public Module 
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	bool PlayMusic(Mix_Music* music);
	bool PlaySound(Mix_Chunk * wave);

public:

	Mix_Music * const LoadM(const char* path);
	bool UnloadM(Mix_Music * music);

	Mix_Chunk * const LoadS(const char * path);
	bool UnloadS(Mix_Chunk * sound);

};



#endif //_ModuleAudio_H__