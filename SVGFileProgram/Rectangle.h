#ifndef RECTANGLE_H_
#define RECTANGLE_H_

struct Rectangle {
	int top_left_x;
	int top_left_y;
	int width;
	int height;

	bool operator == (const  Rectangle& other) const
	{
		return (top_left_x == other.top_left_x &&
			top_left_y == other.top_left_y &&
			width == other.width && height == other.height);
	}
};

#endif

