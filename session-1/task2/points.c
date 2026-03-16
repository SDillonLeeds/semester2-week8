/* points.c */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "points.h"


int main( void ) {
    point_t p1 = { .x=1, .y=2 };
    point_t p2 = { .x=-2, .y=4 };
    
    printf(" Distance between (%.1f,%.1f) and (%.1f,%.1f) is %f\n", 
             p1.x,p1.y,p2.x,p2.y,distance(p1,p2));
    return 0;
}

float distance(point_t p, point_t q) {
    //Distance between 2 points
    point_t delta = {
        .x=q.x-p.x,
        .y=q.y-p.y
    };
    return sqrt(
        (delta.x*delta.x) + (delta.y*delta.y)
    );
}

point_t reflect(point_t p) {
    return (point_t){.x=p.x, .y=-p.y};
}

point_t shift(point_t p, point_t dq) {
    return (point_t){
        .x=p.x+dq.x,
        .y=p.y+dq.y
    };
}