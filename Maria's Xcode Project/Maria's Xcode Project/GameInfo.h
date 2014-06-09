#ifndef GAMEINFO_H
#define GAMEINFO_H

class GameInfo {
public:
	// Member Variables
	static int currLevel;
	static int cameraProfile;
    static int strokes;

	// Functions
	static void nextLevel();
	static void setFreeLook();
	static void setTopDown();
};

#endif /* GAMEINFO_H */
