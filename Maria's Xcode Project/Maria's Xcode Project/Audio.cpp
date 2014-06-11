#include "Audio.h"
#include <iostream>

Mix_Chunk *Audio::gHit = NULL;
Mix_Chunk *Audio::gWall = NULL;
Mix_Chunk *Audio::gCheer = NULL;
Mix_Chunk *Audio::gCup = NULL;
Mix_Music *Audio::gMusic = NULL;

void Audio::playSound(Sound id)
{
	switch (id){
	case Audio::Hit:
		Mix_PlayChannel(-1, gHit, 0);
		break;
	case Audio::Cup:
		Mix_PlayChannel(-1, gCup, 0);
		break;
	case Audio::Wall:
		Mix_PlayChannel(-1, gWall, 0);
		break;
	case Audio::Cheer:
		Mix_PlayChannel(-1, gCheer, 0);
		break;
	default:
		break;
	}
}

bool Audio::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sound effects
	gHit = Mix_LoadWAV("hitting.wav");
	if (gHit == NULL)
	{
		std::cout << "Failed to load \"Hit\" sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << "\n";
		success = false;
	}

	gWall = Mix_LoadWAV("wall.wav");
	if (gWall == NULL)
	{
		std::cout << "Failed to load \"Wall-hit\" sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << "\n";
		success = false;
	}

	gCup = Mix_LoadWAV("cup.wav");
	if (gCup == NULL)
	{
		std::cout << "Failed to load \"Ball-in-Cup\" sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << "\n";
		success = false;
	}

	gCheer = Mix_LoadWAV("woo.wav");
	if (gCheer == NULL)
	{
		std::cout << "Failed to load \"Cheer\" sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << "\n";
		success = false;
	}

	gMusic = Mix_LoadMUS("Wallpaper.wav");
	if (gMusic == NULL)
	{
		std::cout << "Failed to load \"Music\" sound! SDL_mixer Error: %s\n" << Mix_GetError() << "\n";
		success = false;
	}

	return success;
}