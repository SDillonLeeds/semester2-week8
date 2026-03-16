/* shapes.h */
#ifndef SHAPES_H
#define SHAPES_H

//////// STRUCTS ////////
typedef struct {
    float x;
    float y;
} point_t;

typedef struct {
    point_t centre;
    float width, height;
} rectangle_t;
//////// STRUCTS ////////


void displayRect(rectangle_t rect);
rectangle_t makeRect(point_t centre, float width, float height);
float getArea(rectangle_t rect);
void shiftRect(rectangle_t* rect, point_t delta);
void scaleRect(rectangle_t* rect, float scale);

void getRectCorners(rectangle_t rect, point_t* corners);
rectangle_t rotateRect90Deg(rectangle_t rect);

#endif