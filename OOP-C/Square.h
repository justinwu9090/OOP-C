/*
* OOP-C attributions
* Author: Justin Wu
* Description: Square example of derived class in C.
* Source Credit: https://www.codementor.io/@michaelsafyan/object-oriented-programming-in-c-du1081gw2
*/

#pragma once
#include "Shape.h"
typedef struct Square Square;

// casts/constructors/destructor
Shape* Square__to_shape(Square* square);
Square* Square__from_shape(Shape* shape);
Square* Square__create(int x, int y, int width, int height);
void Square__destroy(Square* square);

// accessors
int Square__x(Square* self);
int Square__y(Square* self);
int Square__width(Square* self);
int Square__height(Square* self);
