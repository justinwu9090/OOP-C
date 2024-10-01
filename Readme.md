# OOP-C

This is a practice of applying OOP concepts in C via Michael Safyan's article:
https://www.codementor.io/@michaelsafyan/object-oriented-programming-in-c-du1081gw2

The original article is structured well and a great launch point into OOP in classic C. However, in implementing I discovered that there were errors, omitted details and reorganization that helped my understanding. This is my documentation of my process in understanding Michael's article.
## Interface Syntax
This is what the usage will look like:
```c
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
```

## Basic concepts:
1. A class is defined by a struct type and functions that operate on that struct. This version is non-polymorphic (no virtual functions)
    ```c
    typedef struct Point Point;
    Point* Point_create(int x, int y);
    void Point__destroy(Point* self);
    int Point__x(Point* self); // point->x();
    int Point__y(Point* self); // point->y();
    ```
2. Moving on to polymorphic types: a Base class defines a Type which defines the virtual functions to be overriden. It also maintains a buffer that will store the sub class's additional members.
   ```c
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
   ```
3. Thus, a derived class defines its local members separately and override functions. 
    ```c
    struct Square {
        int x;
        int y;
        int width;
        int height;
    };
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
    ```
4. Most of the magic happens in the derived-class constructor + base class constructors. Here the allocation + initialization of members is done
    ```c
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

    Shape* Shape__create(ShapeType* type)
    {
        int size = sizeof(Shape) + type->buffer_size; // allocation for type + extra buffer size from derived type
        Shape* result = (Shape*)malloc(size);
        result->type = type;
        return result;
    }
    ```
5. And acces to the derived class's buffer is done like this:
   ```c
   Square* Square__square_data(Square* self) {
        Shape* shape = Square__to_shape(self);
        return (Square*)Shape__buffer(shape); // start of square's members
    }
    // pointer to the shape's buffer
    void* Shape__buffer(Shape* self)
    {
        return (void*)&(self->buffer_start);
    }
   ```


## Helpful Hints
- the article defines the struct in C++ style, but requires a typedef to simplify the struct referencing in C.
    ```c
    typedef struct Point Point; // typedef .h file
    
    // defined in .c file
    struct Point {
    int x;
    int y;
    };
    ```

- Similarly, in C++ constant expressions can call a function, but in C this is not possible.
    ```cpp
    // outside of any function call, this is only possible in C++
    static ShapeType* square_type =
    ShapeType__create(
        sizeof(SquareData),
        &Square__name_override,
        &Square__sides_override,
        &Square__destroy_override); 

    // instead, in C make the static variable and check/initialize in class constructor
    static ShapeType* square_type = 0;

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
        // ...
    }

    ```