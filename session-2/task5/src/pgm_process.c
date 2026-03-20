/* pgm_process.c */

#include <stdlib.h>
#include <stdio.h>
#include "../inc/pgm_image.h"


//Process
void p_invertImageColours(PGMImage_t* originalImage, PGMImage_t* modified) {    
    /* Invert each pixel (maxGrey - value) */
    for (uint i=0u; i<originalImage->height; i++) {
        for (uint j=0u; j<originalImage->width; j++) {
            modified->data[i][j] = originalImage->maxGrey - originalImage->data[i][j];
        }
    }
}


#define WIDTH original->width
#define HEIGHT original->height
void p_rotateImage(PGMImage_t* original, PGMImage_t* modified, int degrees) {
    switch (degrees) {
        case 90:
            /* For 90 degrees, width and height are swapped */
            *modified = pgm_allocateImage(WIDTH, HEIGHT);
            if (modified->data == NULL) {return;}
            
            /* 90 degree rotation algorithm */
            for (uint i=0; i<HEIGHT; i++) {
                for (uint j=0u; j<WIDTH; j++) {
                    modified->data[j][HEIGHT-1-i] = original->data[i][j];
                }
            }
            break;
            
        case 180:            
            /* 180 degree rotation algorithm */
            for (uint i=0u; i<HEIGHT; i++) {
                for (uint j=0u; j<WIDTH; j++) {
                    modified->data[HEIGHT-1-i][WIDTH-1-j] = original->data[i][j];
                }
            }
            break;
            
        case 270:
            /* For 270 degrees, width and height are swapped */
            *modified = pgm_allocateImage(WIDTH, HEIGHT);
            if (modified->data == NULL) {return;}
            
            /* 270 degree rotation algorithm */
            for (uint i=0u; i<HEIGHT; i++) {
                for (uint j=0u; j<WIDTH; j++) {
                    modified->data[WIDTH-1-j][i] = original->data[i][j];
                }
            }
            break;
            
        default:
            printf("Error: Invalid rotation angle\n");
            return;
    }
}
