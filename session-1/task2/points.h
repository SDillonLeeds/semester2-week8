/* points.h*/
#ifndef POINTS_H
#define POINTS_H

typedef struct {
    float x, y;
} point_t;

// state function headers here

float distance(point_t p, point_t q);
point_t reflect(point_t p);
point_t shift(point_t p, point_t dq);

#endif