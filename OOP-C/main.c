#include <stdio.h>
#include "Square.h"

void main()
{
	// construction
	Square* square = Square__create(0, 1, 1, 2);
	
	// subclass overriden functions
	printf("shape name: %s\n", Shape__name(square));
	printf("shape sides: %d\n", Shape__sides(square));
	// derived class member interface
	printf("square x: %d\n", Square__x(square));
	printf("square y: %d\n", Square__y(square));
	printf("square width: %d\n", Square__width(square));
	printf("square height: %d\n", Square__height(square));

	// destruction
	Square__destroy(square);

}
