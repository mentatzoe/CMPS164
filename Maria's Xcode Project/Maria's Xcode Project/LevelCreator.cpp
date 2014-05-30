#include "LevelCreator.h"
#include <iostream>



Course LevelCreator::createCourse(TokenList tokenList)
{
    auto curToken = tokenList.begin();
    int numLevels = 0; //still not sure if we want this
    std::string cName;
	Course* course = new Course();
    std::string lName;
    int par;

    
    while(curToken != tokenList.end()){
        std::cout << "Examining curToken1: " << (*curToken).data << "\n";
        if (curToken->data.compare("course")==0){
            course->courseName = std::string((*std::next(curToken, 1)).data);
			numLevels = std::stoi((*std::next(curToken, 2)).data);
			curToken += 3;
            std::cout << "Token at1: " << (*curToken).data << "\n";
            std::cout << "Title is: " << course->courseName << "\n";
            std::cout << "Levels are: " << numLevels << "\n";
        }
        
        else if (curToken->data.compare("end_hole")==0) {
            curToken++;
        }
        
        else if (curToken->data.compare("begin_hole")==0) {
            curToken++;
            int tileID = 0;
            int numSides = 0;
            Vector3f teeVect;
            Vector3f cupVect;
            int teeTileID = 0, cupTileID = 0;
            std::vector<Vector3f> vertList;
            std::vector<int> neighbors;
            Level* level = new Level();
            curToken ++;
            while (curToken->data.compare("end_hole")!=0){
                std::cout << "Examining curToken1: " << (*curToken).data << "\n";
                while (curToken->data.compare("end_hole")!=0) {
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
                    else if(curToken->data.compare("name")==0){ //Needs refactor to get actual strings
                        std::cout << "Examining curToken2: " << (*curToken).data << "\n";
                        lName = std::string((*std::next(curToken, 1)).data);
                        std::cout << "Creating level: " << lName << "\n";
                        curToken += 2;
                        std::cout << "Token at2: " << (*curToken).data << "\n";
                    }
                    
                    else if(curToken->data.compare("par")==0){
                        std::cout << "Examining curToken3: " << (*curToken).data << "\n";
                        int par = std::stoi((*std::next(curToken, 1)).data);
                        std::cout << "Level par: " << par << "\n";
                        curToken += 2;
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
                
                level->levelName = lName;
                level->par = par;
                course->levels.push_back(*level);
            }
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

	/*// Print everything
	std::cout << "Printing Level Status:\n";
	for (auto itr = tileList.begin(); itr != tileList.end(); itr++){
		std::cout << "     Tile with ID = " << (*itr).getTileID() << " and numSides = " << (*itr).getNumSides() << "\n";
		std::vector<Vector3f> verts = (*itr).getVerts();
		for (int i = 0; i < verts.size(); i++) {
			std::cout << "          Vertex " << i << ": [" << verts[i].x << ", " << verts[i].y << ", " << verts[i].z << "]\n";
		}
		std::vector<int> neighbors = (*itr).getNeighbors();
		std::cout << "          Neighbors list: ";
		for (int i = 0; i < neighbors.size(); i++){
			std::cout << neighbors[i] << ", ";
		}
		std::cout << "\n";
		std::vector<Vector3f> normals = (*itr).getNormals();

		for (int i = 0; i < normals.size(); i++) {
			std::cout << "          Normal " << i << ": [" << normals[i].x << ", " << normals[i].y << ", " << normals[i].z << "]\n";
		}
		std::cout << "\n";
	}

	std::cout << "     Tee: [" << teeVect.x << ", " << teeVect.y << ", " << teeVect.z << "] on tile " << teeTileID << "\n";
	std::cout << "     Cup: [" << cupVect.x << ", " << cupVect.y << ", " << cupVect.z << "] on tile " << cupTileID << "\n";*/

	return *level;
}

/*
 This function would work if found a way of sending the current token (the iterator)
 */
Level LevelCreator::createLevelInsideCourse(TokenList tokenList, std::__wrap_iter<Token*> curToken){
    //    auto curToken = tokenList.begin();
	int tileID = 0;
	int numSides = 0;
	Vector3f teeVect;
	Vector3f cupVect;
	int teeTileID = 0, cupTileID = 0;
	std::vector<Vector3f> vertList;
	std::vector<int> neighbors;
	Level* level = new Level();
    
	while (curToken->data.compare("end_hole") != 0) {
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
    
	/*// Print everything
     std::cout << "Printing Level Status:\n";
     for (auto itr = tileList.begin(); itr != tileList.end(); itr++){
     std::cout << "     Tile with ID = " << (*itr).getTileID() << " and numSides = " << (*itr).getNumSides() << "\n";
     std::vector<Vector3f> verts = (*itr).getVerts();
     for (int i = 0; i < verts.size(); i++) {
     std::cout << "          Vertex " << i << ": [" << verts[i].x << ", " << verts[i].y << ", " << verts[i].z << "]\n";
     }
     std::vector<int> neighbors = (*itr).getNeighbors();
     std::cout << "          Neighbors list: ";
     for (int i = 0; i < neighbors.size(); i++){
     std::cout << neighbors[i] << ", ";
     }
     std::cout << "\n";
     std::vector<Vector3f> normals = (*itr).getNormals();
     
     for (int i = 0; i < normals.size(); i++) {
     std::cout << "          Normal " << i << ": [" << normals[i].x << ", " << normals[i].y << ", " << normals[i].z << "]\n";
     }
     std::cout << "\n";
     }
     
     std::cout << "     Tee: [" << teeVect.x << ", " << teeVect.y << ", " << teeVect.z << "] on tile " << teeTileID << "\n";
     std::cout << "     Cup: [" << cupVect.x << ", " << cupVect.y << ", " << cupVect.z << "] on tile " << cupTileID << "\n";*/
    
    
    return *level;
}



