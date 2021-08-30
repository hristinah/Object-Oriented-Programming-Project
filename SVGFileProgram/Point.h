#ifndef POINT_H_
#define POINT_H_

#include "Circle.h"
#include "Rectangle.h"

class Point {
public:
	Point(int x=0, int y=0);
	~Point() {}

	bool operator == (const  Point& other) const
	{
		return (x == other.x && y == other.y);
	}
	
	void Translate(int horizontal, int vertical);
	bool IsInCircle(Circle circle_area);
	bool IsInRectangle(Rectangle rect_area);

	int x;
	int y;
};

#endif

