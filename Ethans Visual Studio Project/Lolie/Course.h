#include <iostream>
#include "Level.h"

class Course
{
public:
	// Constructor
    Course();
    ~Course() {};
    
	// Member variables
    std::vector<Level> levels;
    std::string courseName;
};
