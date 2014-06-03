#ifndef HUD_H
#define HUD_H

#include "Libraries.h"
#include <iostream>

class HUD
{
public:
    static void drawTitle(std::string s, int posX, int posY, float r, float g, float b);
    static void drawPar(int p);
    static void drawStrokes(int s);
    static void drawPower(int pow);
    static void drawSomeText(std::string s, int posX, int posY, float r, float g, float b);
};
#endif /* HUD_H */

