#include <stdlib.h>
#include <stdio.h>
#include "Point.h"


struct Point {
	int x;
	int y;
};

// ======================================================
// constructor/destructor + allocation/deallocation
// ======================================================

// constructor without allocation
void Point__init(Point* self, int x, int y) {
	self->x = x;
	self->y = y;
}

// equivalent to new Point(x,y);. is Allocation + calling constructor
Point* Point_create(int x, int y) {
	Point* result = (Point*)malloc(sizeof(Point));
	Point__init(result, x, y);
	return result;

}

// Destructor without deallocation
void Point__reset(Point* self)
{
}

// Destructor + deallocation , = delete Point();
void Point__destroy(Point* self) {
	if (self)
	{
		Point__reset(self);
		free(self);
	}
}

// interface point::x()
int Point__x(Point* self)
{
	return self->x;
}

// interface point::y()
int Point__y(Point* self)
{
	return self->y;
}
