#include <stdlib.h>
#include "Shape.h"

// ======================================================
// Base class + type specifier
// ======================================================
struct Shape {
	ShapeType* type; //derived type representation object
	char buffer_start; // extra members of the derived type exist here
};

// There will be 1 `ShapeType` per derived type of Shape (square, pentagon...)
struct ShapeType {
	int buffer_size;
	const char* (*name) (Shape*);
	int (*sides) (Shape*);
	void (*destroy) (Shape*);
};

// allocate ShapeType struct
ShapeType* ShapeType__create(
	int buffer_size,
	const char* (*name)(Shape*),
	int (*sides)(Shape*),
	void (*destroy)(Shape*))
{
	ShapeType* result = (ShapeType*)malloc(sizeof(ShapeType));
	result->buffer_size = buffer_size;
	result->name = name;
	result->sides = sides;
	result->destroy = destroy;
	return result;
}

// allocate Shape + ShapeType struct
Shape* Shape__create(ShapeType* type)
{
	int size = sizeof(Shape) + type->buffer_size; // allocation for type + extra buffer size from derived type
	Shape* result = (Shape*)malloc(size);
	result->type = type;
	return result;
}

ShapeType* Shape__type(Shape* shape)
{
	return shape->type;
}

// pointer to the shape's buffer
void* Shape__buffer(Shape* self)
{
	return (void*)&(self->buffer_start);
}

// call derived class sides function 
int Shape__sides(Shape* self)
{
	return self->type->sides(self);
}

// call derived class name function 
char* Shape__name(Shape* self)
{
	return self->type->name(self);
}

void Shape__destroy(Shape* shape)
{
	if (shape)
	{
		shape->type->destroy(shape);
	}
}
