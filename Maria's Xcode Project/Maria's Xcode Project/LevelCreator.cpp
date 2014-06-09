#include "LevelCreator.h"
#include <iostream>



Course LevelCreator::createCourse(TokenList tokenList)
{
    auto curToken = tokenList.begin();
    int numLevels = 0; //still not sure if we want this
    std::string cName;
	Course* course = new Course();

    
    while(curToken != tokenList.end()){
        //std::cout << "Examining curToken1: " << (*curToken).data << "\n";
        if (curToken->data.compare("course")==0){
            course->courseName = std::string((*std::next(curToken, 1)).data);
			numLevels = std::stoi((*std::next(curToken, 2)).data);
			curToken += 3;
        }
        
        else if (curToken->data.compare("end_hole")==0){
            curToken ++;
        }
        
        /*
            If we find a "begin_hole" token, 
            we enter a new loop in which 
            we create a new level and set it up
            the same way createLevel works (+ name + par)
         */
        else if (curToken->data.compare("begin_hole")==0) {
            //std::cout << "-----------------BEGIN HOLE-----------------------" << "\n";
            std::string lName = "";
            int tileID = 0;
            int numSides = 0;
            Vector3f teeVect;
            Vector3f cupVect;
            int teeTileID = 0, cupTileID = 0;
            std::vector<Vector3f> vertList;
            std::vector<int> neighbors;
            Level* level = new Level();
            curToken ++;
            while (true){
                    //std::cout << "Examining curToken: " << (*curToken).data << "\n";
                    if (curToken->data.compare("tile") == 0) {
                        //std::cout << "     curToken is 'tile'\n";
                        tileID = std::stoi((*std::next(curToken, 1)).data);
                        numSides = std::stoi((*std::next(curToken, 2)).data);
                        curToken += 3;
                        for (int i = 0; i < 3 * numSides; i += 3) {
                            //std::cout << "curToken as a float is currently " << std::stof((std::next(curToken, i))->data) << "\n";
                            Vector3f vert(std::stof((std::next(curToken, i))->data), std::stof((std::next(curToken, i + 1))->data), std::stof((std::next(curToken, i + 2))->data));
                            vertList.push_back(vert);
                        }
                        
                        // Add the bottom layer of verts to the vert list
                        for (int i = 0; i < numSides; i++) {
                            Vector3f vert(vertList[i].x, vertList[i].y - .1f, vertList[i].z);
                            vertList.push_back(vert);
                        }
                        
                        curToken += 3 * numSides;
                        
                        //std::cout << "     (After verts) curToken is now " << (*curToken).data << "\n";
                        
                        for (int i = 0; i < numSides; i++) {
                            neighbors.push_back(std::stof((std::next(curToken, i))->data));
                        }
                        curToken += numSides;
                        
                        //std::cout << "     (After neighbors) curToken is now " << (*curToken).data << "\n";
                        
                        level->addChild(new Tile(tileID, numSides, vertList, neighbors));
                    }
                    else if (curToken->data.compare("tee") == 0) {
                        //std::cout << "     curToken is 'tee'\n";
                        teeVect.x = std::stof((*std::next(curToken, 2)).data);
                        teeVect.y = std::stof((*std::next(curToken, 3)).data);
                        teeVect.z = std::stof((*std::next(curToken, 4)).data);
                        teeTileID = std::stof((*std::next(curToken, 1)).data);			// TileID
                        curToken += 5;
                    }
                    else if (curToken->data.compare("cup") == 0) {
                        //std::cout << "     curToken is 'cup'\n";
                        cupVect.x = std::stof((*std::next(curToken, 2)).data);
                        cupVect.y = std::stof((*std::next(curToken, 3)).data);
                        cupVect.z = std::stof((*std::next(curToken, 4)).data);
                        cupTileID = std::stof((*std::next(curToken, 1)).data);			// TileID
                        curToken += 5;
                    }
                    
                    /*
                     When dealing with names, 
                     we try to see if the last character of the token is a quote.
                     In that case, we remove the quotes and store the string.
                     If not, we keep appending them until we find a word whose last char is a string.
                     (This should be implemented recursively)
                     */
                    else if (curToken->data.compare("name")==0){
                        //std::cout << "-----------------NAME PROCESSING-----------------------" << "\n";
                        std::string token = std::string(std::next(curToken, 1)->data);
                        if (strcmp(&token.at(token.length()-1),"\"") == 0){
                            //Still needs to take the quotes off
                            lName = std::string((*std::next(curToken, 1)).data);
                            curToken += 2;
                        } else {
                            curToken++;
                            std::string token = std::string(curToken->data);
                            //std::cout << token << "\n";
                            while(true){
                                lName.append(std::string(curToken->data));
                                lName.append(" ");
                                curToken++;
                                std::string token = std::string(curToken->data);
                                if (strncmp(&token.at(token.length()-1),"\"",1) == 0){
                                    lName.append(std::string(curToken->data));
                                    break;
                                }
                            }
                        }
                    }
                    
                    else if(curToken->data.compare("par")==0){
                        //std::cout << "-----------------BEGIN PAR-----------------------" << "\n";
                        curToken++;
                        level->par = std::stoi(curToken->data);
                        //std::cout << "Level par: " << par << "\n";
                        //std::cout << curToken->data << "\n";
                    }
                
                    else if (curToken->data.compare("end_hole")==0) {
                        //std::cout << "-----------------END HOLE-----------------------" << "\n";
                        break;
                    }
                    else {
                        // Something wrong happened somewhere
                        curToken++;
                    }
                    
                    vertList.clear();
                    neighbors.clear();
                }
                
                std::vector<SceneNode*> children = level->getChildren();
                for (int i = 0; i < children.size(); i++) {
                    Tile* t = static_cast<Tile*> (children[i]);
                    if (teeTileID == (*t).getTileID()) {
                        Ball* b = new Ball(teeTileID, teeVect);
                        level->setBall(b);
                        //(*t).addChild(new Tee(teeTileID, teeVect));
                        (*t).addChild(static_cast<SceneNode*>(level->getBall()));
                    }
                    if (cupTileID == (*t).getTileID()) {
                        (*t).addChild(new Cup(cupTileID, cupVect));
                    }
                }
                std::cout << "---------------------" << "\n";
                std::cout << "Level name is " << lName << "\n";
                std::cout << "Par is " << level->par << "\n";
                level->levelName = lName;
                course->levels.push_back(*level);
            }
        }
    return *course;
}

Level LevelCreator::createLevel(TokenList tokenList)
{
	auto curToken = tokenList.begin();
	int tileID = 0;
	int numSides = 0;
	Vector3f teeVect;
	Vector3f cupVect;
	int teeTileID = 0, cupTileID = 0;
	std::vector<Vector3f> vertList;
	std::vector<int> neighbors;
	Level* level = new Level();

	while (curToken != tokenList.end()) {
		//std::cout << "Examining curToken: " << (*curToken).data << "\n";
		if (curToken->data.compare("tile") == 0) {
			//std::cout << "     curToken is 'tile'\n";
			tileID = std::stoi((*std::next(curToken, 1)).data);
			numSides = std::stoi((*std::next(curToken, 2)).data);
			curToken += 3;

			//std::cout << "     (After tileID/numSides) curToken is now " << (*curToken).data << "\n";

			for (int i = 0; i < 3 * numSides; i += 3) {
				//std::cout << "curToken as a float is currently " << std::stof((std::next(curToken, i))->data) << "\n";
				Vector3f vert(std::stof((std::next(curToken, i))->data), std::stof((std::next(curToken, i + 1))->data), std::stof((std::next(curToken, i + 2))->data));
				vertList.push_back(vert);
			}

			// Add the bottom layer of verts to the vert list
			for (int i = 0; i < numSides; i++) {
				Vector3f vert(vertList[i].x, vertList[i].y - .1f, vertList[i].z);
				vertList.push_back(vert);
			}

			curToken += 3 * numSides;

			//std::cout << "     (After verts) curToken is now " << (*curToken).data << "\n";

			for (int i = 0; i < numSides; i++) {
				neighbors.push_back(std::stof((std::next(curToken, i))->data));
			}
			curToken += numSides;

			//std::cout << "     (After neighbors) curToken is now " << (*curToken).data << "\n";

			level->addChild(new Tile(tileID, numSides, vertList, neighbors));
		}
		else if (curToken->data.compare("tee") == 0) {
			//std::cout << "     curToken is 'tee'\n";
			teeVect.x = std::stof((*std::next(curToken, 2)).data);
			teeVect.y = std::stof((*std::next(curToken, 3)).data);
			teeVect.z = std::stof((*std::next(curToken, 4)).data);
			teeTileID = std::stof((*std::next(curToken, 1)).data);			// TileID
			curToken += 5;
		}
		else if (curToken->data.compare("cup") == 0) {
			//std::cout << "     curToken is 'cup'\n";
			cupVect.x = std::stof((*std::next(curToken, 2)).data);
			cupVect.y = std::stof((*std::next(curToken, 3)).data);
			cupVect.z = std::stof((*std::next(curToken, 4)).data);
			cupTileID = std::stof((*std::next(curToken, 1)).data);			// TileID
			curToken += 5;
		}
		else {
			// Something wrong happened somewhere
			curToken++;
		}

		vertList.clear();
		neighbors.clear();
	}

	std::vector<SceneNode*> children = level->getChildren();
	for (int i = 0; i < children.size(); i++) {
		Tile* t = static_cast<Tile*> (children[i]);
		if (teeTileID == (*t).getTileID()) {
            Ball* b = new Ball(teeTileID, teeVect);
            level->setBall(b);
			//(*t).addChild(new Tee(teeTileID, teeVect));
			(*t).addChild(static_cast<SceneNode*>(level->getBall()));
		}
		if (cupTileID == (*t).getTileID()) {
			(*t).addChild(new Cup(cupTileID, cupVect));
		}
	}

	return *level;
}



