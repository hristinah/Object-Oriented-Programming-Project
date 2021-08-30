#include "Point.h"

#include "Circle.h"
#include "Rectangle.h"

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

void Point::Translate(int horizontal, int vertical) {
    x += horizontal;
    y += vertical;
}

bool Point::IsInCircle(Circle circle_area) {
    if ((x - circle_area.center_x)*(x - circle_area.center_x) +
        (y - circle_area.center_y)*(y - circle_area.center_y) <= circle_area.radius*circle_area.radius)
        return true;
    else
        return false;
}

bool Point::IsInRectangle(Rectangle rect_area) {
    if ((x >= rect_area.top_left_x) && (x <= (rect_area.top_left_x + rect_area.width)) &&
        (y >= rect_area.top_left_y) && (y <= (rect_area.top_left_y + rect_area.height)))
        return true;
    else
        return false;
}
