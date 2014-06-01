#include "LineCollider.h"
#include "CircleCollider.h"
#include <iostream>
double Dot(Point& a, Point& b)                        { return (a.x()*b.x()) + (a.y()*b.y()); }
double PerpDot(Point& a, Point& b)                    { return (a.y()*b.x()) - (a.x()*b.y()); }

bool LineCollider::getCollision(Collider2D& col, Vector3f& result)
{
	switch (col.getType())
	{
	case Collider2D::Circle_t:
		return getCircleCollision(col, result);
		break;
	case Collider2D::Line_t:
		return getLineCollision(col, result);
		break;
	}
}

bool LineCollider::getLineCollision(Collider2D& col, Vector3f& result){
	Point A1(getA().x, getA().z);
	Point A2(getB().x, getB().z);
	Point B1(col.getA().x, col.getA().z);
	Point B2(col.getB().x, col.getB().z);

	Point a(A2 - A1);
	Point b(B2 - B1);

	double f = PerpDot(a, b);
	if (!f) return false; // lines are parallel

	Point c(B2 - A2);
	double aa = PerpDot(a, c);
	double bb = PerpDot(b, c);

	if (f < 0)
	{
		if (aa > 0)     return false;
		if (bb > 0)     return false;
		if (aa < f)     return false;
		if (bb < f)     return false;
	}
	else
	{
		if (aa < 0)     return false;
		if (bb < 0)     return false;
		if (aa > f)     return false;
		if (bb > f)     return false;
	}

	double out = 1.0 - (aa / f);
		
	result = Vector3f((B2.x() - B1.x())*out + B1.x(), result.y, (B2.y() - B1.y())*out + B1.y());
	//std::cout << "ColPos = (" << (B2.x() - B1.x())*out + B1.x() << ", " << result.y << ", " << (B2.y() - B1.y())*out + B1.y() << ")\n";
	//std::cout << "B = (" << B1.x() << ", " << 0 << ", " << B1.y() << ") - (" << B2.x() << ", " << 0 << ", " << B2.y() << ")\n";
	//system("pause");
	return true;
};

bool LineCollider::getCircleCollision(Collider2D& col, Vector3f& result)
{
	CircleCollider* cir_col = static_cast<CircleCollider*>(&col);

	//std::cout << "Checking collision between line from (" << getA().x << ", " << getA().y << ", " << getA().z << ") to (" << getB().x << ", " << getB().y << ", " << getB().z << ") with circle of radius " << cir_col->getRadius() << " at point (" << cir_col->getCenter().x << ", " << cir_col->getCenter().y << ", " << cir_col->getCenter().z << ")\n";

	// Declarations
	float radius = cir_col->getRadius();
	Vector3f cirPos = cir_col->getCenter();
	Vector3f p1 = getA();
	Vector3f p2 = getB();

	// Get line
	Vector3f seg_v = p2 - p1;
	Vector3f pt_v = cirPos - p1;

	// Get projection (scalar) of circle onto line
	float proj_s = dot(pt_v, (seg_v / magnitude(seg_v)));
	
	// If the projection is < 0 or > magnitude(seg_v), then there is no collision
	if (proj_s < 0 || proj_s > magnitude(seg_v)){
		return false;
	}
	// else the circle is within the bounds of the line

	// Calculate actual project vector
	Vector3f proj_v = (seg_v / magnitude(seg_v)) * proj_s;
	
	// convert it to world coordinates
	Vector3f closest = p1 + proj_v;
	// Closest is now the closest point on the line to the circle's position

	// Calc vector from closest to the circle
	Vector3f dist_v = cirPos - closest;

	// If the distance to the line is less than the radius, they are colliding
	if (magnitude(dist_v) < radius){
		result = closest;
		return true;
	}
	// Else they aren't
	else{
		return false;
	}
}