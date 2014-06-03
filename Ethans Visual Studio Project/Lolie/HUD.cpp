#include "HUD.h"

void HUD::drawTitle(std::string s, int posX, int posY, float r, float g, float b){
    glColor3f(r, g, b); // Green
    glRasterPos2i(posX, posY);
    
    void * font = GLUT_BITMAP_HELVETICA_18;
    
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
        
    }
}


void HUD::drawSomeText(std::string s, int posX, int posY, float r, float g, float b){
    glColor3f(r, g, b); // Green
    glRasterPos2i(posX, posY);
    
    void * font = GLUT_BITMAP_HELVETICA_12;
    
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
        
    }
}