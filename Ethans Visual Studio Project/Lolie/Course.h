#include <iostream>
#include "Level.h"

class Course
{
public:
    Course();
    ~Course() {};
    
    std::vector<Level> levels;
    std::string courseName;
};
