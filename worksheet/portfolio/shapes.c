
#include <stdbool.h>
#include <math.h>

#include "shapes.h"

Point makePoint( float x, float y ) {
    return (Point){.x=x, .y=y};
}

// complete other functions below
// - start with stubs as above
// - compile regularly to test syntax
// - test functions by calling them from main()

Line makeLine( Point p1, Point p2 ) {
    return (Line){.p={p1, p2}};
}
Triangle makeTriangle( Point p1, Point p2, Point p3 ) {
    return (Triangle){.p={p1, p2, p3}};
}

/*
  Structure calculation functions (requires <math.h>)
*/

float lineLength( Line l ) {
    Point start = l.p[0];
    Point end   = l.p[1];

    float deltaX = end.x - start.x;
    float deltaY = end.y - start.y;

    return sqrt((deltaX*deltaX) + (deltaY*deltaY));
}

#define VERTEX t.p /* Looks slightly nicer. */
float triangleArea( Triangle t ) {
    /*
    Uses this formula;
    A = ½ × |x1(y2-y3) + x2(y3-y1) + x3(y1-y2)|
    */

    float det1 = VERTEX[0].x * (VERTEX[1].y - VERTEX[2].y);
    float det2 = VERTEX[1].x * (VERTEX[2].y - VERTEX[0].y);
    float det3 = VERTEX[2].x * (VERTEX[0].y - VERTEX[1].y);

    return 0.5f * fabs(det1 + det2 + det3);
}

/*
  Structure comparison functions (requires <stdbool.h>)

  Note: 
  * to compare 2 points you should not test float values for equality
  * test if they are "close enough"
  * eg. float values are accurate to 8 d.p.
  * abs(lineLength(p1,p2))<1.0e-6 would be sufficient to say p1 and p2 are the same point 
*/

#define EPSILON 1e-6f /* Very small epsilon value. */
bool samePoint( Point p1, Point p2 ) {
    //True if its the same coordinates point. Has some tolerance for floating-point values.
    return (
        (fabs(p1.x - p2.x) < EPSILON) &&
        (fabs(p1.y - p2.y) < EPSILON)
    );
}
bool pointInLine( Point p, Line l) {
    //True if its an endpoint of the line.
    return (
        samePoint(p, l.p[0]) || //Check start
        samePoint(p, l.p[1])    //Check end
    );
}
bool pointInTriangle( Point p, Triangle t ) {
    //True if its a vertex of the triangle.
    return (
        samePoint(p, t.p[0]) || //Check v0
        samePoint(p, t.p[1]) || //Check v1
        samePoint(p, t.p[2])    //Check v2
    );
}
