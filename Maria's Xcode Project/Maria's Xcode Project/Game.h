//
//  Game.h
//  Copyright (c) 2014 CMPS 164 Game Engines. All rights reserved.
//

#ifndef __Maria_s_Xcode_Project__Game__
#define __Maria_s_Xcode_Project__Game__

#include <iostream>
#include "RenderManager.h"
#include "Level.h"

#endif

class Game {
    RenderManager _renderManager;
    Level _level;
    //StateManager _stateManager;
    std::string _levelPath;
    
public:
    void readLevel();
    void update();
    void generateVBO();
    /*http://en.wikipedia.org/wiki/Vertex_Buffer_Object
     Not completely sure of what kind of data type it returns or operates with, that's why I'm keeping it void for now.
     */
    void renderLevel(); //Call to generateVBO and renderManager.draw() or whatever
    //Missing constructor with filename
};
