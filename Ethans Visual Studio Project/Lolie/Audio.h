#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>



class Audio {
public:
	static enum Sound{
		Hit,
		Wall,
		Cup,
		Cheer,
		Music,
	};
	void static playSound(Sound type);
	bool static loadMedia();

	//The sound effects that will be used
	static Mix_Chunk *gHit;
	static Mix_Chunk *gWall;
	static Mix_Chunk *gCup;
	static Mix_Chunk *gCheer;
	static Mix_Music *gMusic;
};

#endif /* AUDIO_H */