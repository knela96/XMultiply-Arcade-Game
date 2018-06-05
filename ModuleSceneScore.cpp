#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneScore.h"
#include "ModuleSceneMainMenu.h"
#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL_render.h"
#include "ModuleFonts.h"
#include <string.h>
#include <iostream>
#include "ModulePlayer.h"


ModuleSceneScore::ModuleSceneScore()
{
	// Background / sky
	background = { 0, 0, 384, 256 };
}

ModuleSceneScore::~ModuleSceneScore()
{}

// Load assets
bool ModuleSceneScore::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	rgb = 255;
	graphics = App->textures->Load("Assets/Sprites/UI/Score_Background.png");
	font_gameover1 = App->font->Load("Assets/Sprites/UI/fonts.1.png", "0123456789·' ºººººººººººººabcdefghijklmnopqrstuvwxyz", 2);
	font_gameover2 = App->font->Load("Assets/Sprites/UI/fonts.2.png", "0123456789·' ºººººººººººººabcdefghijklmnopqrstuvwxyz", 2);

	/*ranking[0] = ranking_names[0];
	ranking[1] = ranking_names[1];
	ranking[2] = ranking_names[2];
	ranking[3] = ranking_names[3];
	ranking[4]->score = 50000;

	for (i = 0; i < 5 - 1; i++)
	{
		for (j = i + 1; j < 5; j++) {
			if (ranking[j]->score < ranking[i]->score) {
				PlayerScore* tmp = ranking[i];
				ranking[i] = ranking[j];
				ranking[j] = tmp;
			}
		}
	}

	for (int i = 1; i < 5; i++) {
		if (ranking[i]->score > ranking_names[i - 1]->score) {
			PlayerScore* aux = ranking_names[i - 1];
			ranking_names[i - 1] = ranking[i];
			ranking[i] = aux;
		}
		else
			ranking[i] = ranking_names[i];
	}
	*/
	for (int i = 0; i < 5; i++) {
		std::string str;
		str += i;
		switch (i) {
		case 0:
			str += "st";
			break;
		case 1:
			str += "nd";
			break;
		case 2:
			str += "rd";
			break;
		case 3:
		case 4:
			str += "th";
			break;
		}
		str += ranking[i]->name;
		str += " baa  ";
		str += ranking[i]->score;
		strcpy_s(_stagenamesblit[i], str.c_str());
	}

	return ret;
}

// Load assets
bool ModuleSceneScore::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading ChoosePlayer stage");
	App->textures->Unload(graphics);
	graphics = nullptr;
	App->font->UnLoad(font_gameover2);
	font_gameover2 = -1;
	App->font->UnLoad(font_gameover1);
	font_gameover1 = -1;

	App->font->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneScore::Update()
{
	if (SDL_GetTicks() - start_time >= 1500) {
		if (rgb < 255 && !color) {
			rgb += 2;
		}
		else if (rgb > 0 && color) {
			rgb -= 2;
		}
		if (rgb <= 160) {
			color = false;
			start_time = SDL_GetTicks();
		}
		else if (rgb >= 255) {
			color = true;
			start_time = SDL_GetTicks();
		}
		SDL_SetTextureColorMod(graphics, 255, 255, rgb);
	}

	if (SDL_GetTicks() - text_delay >= 50) {
		start_time = SDL_GetTicks();
		char* letter = &_stagenamesblit[i][j];
		if (_stricmp(letter,"\0") != 0) {
			_stageendblit[i][j] = _stagenamesblit[i][j];
			j++;
		}
		else {
			j = 0;
			i++;
		}
	}


	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, &background, 1.0f);

	for (int index = 0; index < 5; ++index) {
		if (i != index_player - 1) {
			App->font->BlitText(100, 20 + (index * 40), font_gameover1, _stageendblit[index]);
		}
		else {
			App->font->BlitText(100, 20 + (index * 40), font_gameover2, _stageendblit[index]);
		}
	}




	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1 || App->input->controller[START] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_score, App->scene_MainMenu, 1);
	}
	return UPDATE_CONTINUE;
}