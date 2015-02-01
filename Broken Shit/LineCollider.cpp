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

	std::cout << "Checking collision between line from (" << getA().x << ", " << getA().y << ", " << getA().z << ") to (" << getB().x << ", " << getB().y << ", " << getB().z << ") with circle of radius " << cir_col->getRadius() << " at point (" << cir_col->getCenter().x << ", " << cir_col->getCenter().y << ", " << cir_col->getCenter().z << ")\n";

	Vector3f LocalP1 = getA() - cir_col->getCenter();
	Vector3f LocalP2 = getB() - cir_col->getCenter();

	// Precalculate this value. We use it often
	Vector3f P2MinusP1 = LocalP2 - LocalP1;

	float a = (P2MinusP1.x) * (P2MinusP1.x) + (P2MinusP1.z) * (P2MinusP1.z);
	float b = 2 * ((P2MinusP1.x * LocalP1.x) + (P2MinusP1.z * LocalP1.z));
	float c = (LocalP1.x * LocalP1.x) + (LocalP1.z * LocalP1.z) - (cir_col->getRadius() * cir_col->getRadius());
	float delta = (b * b) - (4 * a * c);
	std::cout << "     delta = " << delta << ", a = " << a << " , b = " << b << ", c = " << c << "\n";
	if (delta < 0) // No intersection
		return false;
	else if (delta == 0) // One intersection
		return true;
	else if (delta > 0) // Two intersections
		return true;
}