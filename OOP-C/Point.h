/*
* OOP-C attributions
* Author: Justin Wu
* Description: Point is an example of creating OOP class constructor/destructor/interface in C.
* Source Credit: https://www.codementor.io/@michaelsafyan/object-oriented-programming-in-c-du1081gw2
*/
#pragma once

typedef struct Point Point; // needed in c vs c++ to simplify struct _thingy_struct t; --> thingy t;

// ======================================================
// constructor/destructor/default interfaces
// ======================================================

Point* Point_create(int x, int y);
void Point__destroy(Point* self);
int Point__x(Point* self); // point->x();
int Point__y(Point* self); // point->y();
