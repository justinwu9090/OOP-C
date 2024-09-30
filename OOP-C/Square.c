#include "Shape.h"
#include "Square.h"

// ======================================================
// derived class's members
// ======================================================
struct Square {
	int x;
	int y;
	int width;
	int height;
};

// ======================================================
// virtual function overrides
// ======================================================
const char* Square__name_override(Shape* self) {
	return "Square";
}

int Square__sides_override(Shape* self)
{
	return 4;
}

void Square__destroy_override(Shape* square)
{
	free(square);
}

// ======================================================
// static single instance of ShapeType for square;
// ======================================================
static ShapeType* square_type = 0;

// below doesn't work because in C, function call not allowed in constant expression. allowed in C++
//static ShapeType* square_type =
//ShapeType__create(
//	sizeof(SquareData),
//	&Square__name_override,
//	&Square__sides_override,
//	&Square__destroy_override); 


// ======================================================
// casting + buffer fetching
// ======================================================

Shape* Square__to_shape(Square* square) {
	return ((Shape*)square);
}

Square* Square__from_shape(Shape* shape) {
	// check against null pointer
	if (!shape) {
		return ((Square*)0);
	}
	// check against shape type
	ShapeType* type = Shape__type(shape);
	if (type != square_type) {
		return ((Square*)0);
	}
	return ((Square*)shape);
}

Square* Square__square_data(Square* self) {
	//Shape* shape = (Shape*)self;
	Shape* shape = Square__to_shape(self);
	return (Square*)Shape__buffer(shape); // start of square's members
}

// ======================================================
// constructor/destructors
// ======================================================
Square* Square__create(int x, int y, int width, int height)
{
	// workaround for function call in constant expression
	if (!square_type)
	{
		square_type = ShapeType__create(
			sizeof(Square),
			&Square__name_override,
			&Square__sides_override,
			&Square__destroy_override);
	}
	// call to base class allocator/constructor, then same for derived class
	Square* result = (Square*)Shape__create(square_type);
	Square* square = Square__square_data(result);
	// initialize members
	square->x = x;
	square->y = y;
	square->width = width;
	square->height = height;

	return result;
}

void Square__destroy(Square* square) {
	Shape__destroy(Square__to_shape(square)); // Square__destroy is called from Shape__type
}

// ======================================================
// interfaces, access access to members in Square__square_data() go to Shape__buffer()
// ======================================================
int Square__x(Square* self)
{
	return Square__square_data(self)->x;
}

int Square__y(Square* self)
{
	return Square__square_data(self)->y;
}

int Square__width(Square* self)
{
	return Square__square_data(self)->width;
}

int Square__height(Square* self)
{
	return Square__square_data(self)->height;
}
