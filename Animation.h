#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

private:
	float current_frame;
	int last_frame = 0;
	int loops = 0;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= last_frame)
			current_frame = 0;

		return frames[(int)current_frame];
	}

	SDL_Rect& GetCurrentFrameNotCycling(int lastframe)
	{
		if (current_frame < lastframe) {
			current_frame += speed;
		}
		return frames[(int)current_frame];
	}

	void reset_currentFrame() {
		current_frame = 0;
		frames[0];
	}

	bool islastframe() {
		if (current_frame >= last_frame) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Finished() const
	{
		return loops > 0;
	}





};

#endif