/*
* OOP-C attributions
* Author: Justin Wu
* Description: Shape example of base class in C.
* Source Credit: https://www.codementor.io/@michaelsafyan/object-oriented-programming-in-c-du1081gw2
*/
#pragma once

typedef struct Shape Shape;
typedef struct ShapeType ShapeType;

// ======================================================
// Base class + type specifier
// ======================================================

// extra representation of the type of shape.
// this performs dynamic dispatch (resolving virtual functions)
ShapeType* ShapeType__create(
	int buffer_size, // allocates additional space for derived type buffer
	
	const char* (*name) (Shape*), // name() function pointer
	int (*sides) (Shape*), // sides() function pointer
	void (*destroy) (Shape*) // destroy() function pointer??
);

Shape* Shape__create(ShapeType* type);
ShapeType* Shape__type(Shape* shape);
void* Shape__buffer(Shape* self);
int Shape__sides(Shape* self);
char* Shape__name(Shape* self);
void Shape__destroy(Shape* shape);
