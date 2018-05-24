#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define PI 3.14159265359

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum ENEMY_TYPES
{
	NO_TYPE,
	POWERUPSHIP,
	BROWN_WORM,
	LITTLE_SHRIMP,
	NEMONA_TENTACLE,
	BIG_EYE,
	BIG_SHRIMP,
	BLUE_MOUTH,
	YELLOW_BALL,
	BOUNCER,
	BLUE_SENTINEL,
	BOSS1,
	BOSSARM,
	BOSSTENT,
	BOSSDISP,
	BOSSFACE,
	BOSSHEART
};

// Useful typedefs ---------
typedef unsigned int uint;

// Configuration -----------
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 256
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 1
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define REN_VSYNC 1

#endif // __GLOBALS_H__
