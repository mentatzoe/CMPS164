#ifndef BALL_H
#define BALL_H

#include "Sphere.h"
#include "utility.h"
#include "Libraries.h"

class Ball : Drawable {
public:
	Ball(float x, float y, float z) { location.x = x; location.y = y; location.z = z; };
	~Ball();

	void draw();
	void update();

private:
	int curTileID;
	Sphere sphere;
	Vector3f location;
};

#endif /* BALL_H */