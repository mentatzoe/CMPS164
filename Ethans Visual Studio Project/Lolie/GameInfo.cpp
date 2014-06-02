#include "GameInfo.h"

int GameInfo::currLevel = 0;
int GameInfo::cameraProfile = 0;

void GameInfo::nextLevel(){
	currLevel++;
}

void GameInfo::setFreeLook(){
	cameraProfile = 0;
}

void GameInfo::setTopDown(){
	cameraProfile = 1;
}