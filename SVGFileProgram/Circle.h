#ifndef CIRCLE_H_
#define CIRCLE_H_

struct Circle {
	int center_x;
	int center_y;
	int radius;

	bool operator == (const  Circle& other) const
	{ 
		return (center_x == other.center_x &&
			center_y == other.center_y &&
			radius == other.radius);
	}
};

#endif

