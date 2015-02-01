#include "GameInfo.h"

// Initialize static variables
int GameInfo::currLevel = 0;
int GameInfo::cameraProfile = 0;
int GameInfo::strokes = 0;

void GameInfo::nextLevel(){
	currLevel++;
}

void GameInfo::setFreeLook(){
	cameraProfile = 0;
}

void GameInfo::setTopDown(){
	cameraProfile = 1;
}