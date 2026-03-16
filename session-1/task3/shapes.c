/* shapes.c */

#include <stdio.h>
#include "shapes.h"


#define PT(X, Y) (point_t){.x=X, .y=Y}
#define RECT(C, W, H) (rectangle_t){.centre=C, .width=W, .height=H};


void displayArr(point_t* arr) {
    printf("Array {\n");
    for (unsigned int idx=0u; idx<4; idx++) {
        point_t* ptr = arr+idx;
        printf("    (%f, %f),\n", ptr->x, ptr->y);
    }
    printf("}\n");
}


int main(void) {
    rectangle_t rect = makeRect(
        PT(5, 7), 10.0f, 20.0f
    );

    displayRect(rect);

    point_t preCorners[4];
    getRectCorners(rect, preCorners);
    displayArr(preCorners);


    shiftRect(&rect, PT(10, 10)); //Translate by (+10, +10)
    scaleRect(&rect, 0.5f); //Half scale
    displayRect(rect);

    point_t postCorners[4];
    getRectCorners(rect, postCorners);
    displayArr(postCorners);
    
    return 0;
}

void displayRect(rectangle_t rect) {
    printf("Rectangle {\n    Centre: {\n");
    printf("        X: %f, Y: %f\n", rect.centre.x, rect.centre.y);
    printf("    }\n    Dimensions: {\n");
    printf("        W: %f, H: %f\n", rect.width, rect.height);
    printf("    }\n    Area: %f\n}\n", getArea(rect));
}

rectangle_t makeRect(point_t centre, float width, float height){
    return RECT(centre, width, height);
}

float getArea(rectangle_t rect) {
    return rect.width * rect.height;
}

void shiftRect(rectangle_t* rect, point_t delta) {
    rect->centre = PT(
        rect->centre.x+delta.x,
        rect->centre.y+delta.y
    );
}

void scaleRect(rectangle_t* rect, float scale) {
    rect->width *= scale;
    rect->height *= scale;
}

void getRectCorners(rectangle_t rect, point_t* corners) {
    float hWidth = rect.width / 2;
    float hHeight = rect.height / 2;

    point_t mini = PT(
        rect.centre.x-hWidth,
        rect.centre.y-hHeight
    );
    point_t maxi = PT(
        rect.centre.x+hWidth,
        rect.centre.y+hHeight
    );

    corners[0] = PT(mini.x, mini.y);
    corners[1] = PT(mini.x, maxi.y);
    corners[2] = PT(maxi.x, maxi.y);
    corners[3] = PT(maxi.x, mini.y);
}

rectangle_t rotateRect90Deg(rectangle_t rect) {
    return RECT(
        rect.centre, rect.height, rect.width //Rotate w/h
    );
}