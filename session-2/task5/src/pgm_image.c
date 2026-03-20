/* pgm_image.c */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/pgm_image.h"



//PGM Image
PGMImage_t pgm_allocateImage(int width, int height) {
    PGMImage_t img;
    img.width = width;
    img.height = height;

    img.data = calloc(height, sizeof(uchar*));
    if (img.data == NULL) {
        printf("Error: Memory allocation failed for image array\n");
        EXIT_BAD_IMG;
    }
    
    for (uint i=0u; i<(uint)(height); i++) {
        img.data[i] = calloc(width, sizeof(uchar));
        if (img.data[i] == NULL) {
            /* Free previously allocated memory if this allocation fails */
            for (uint j=0u; j<i; j++) {
                free(img.data[j]);
            }
            free(img.data);
            printf("Error: Memory allocation failed for image row %d\n", i);
            EXIT_BAD_IMG;
        }
    }

    return img;
}

void pgm_freeImage(PGMImage_t* img) {
    if (img->data == NULL) return;
    
    for (uint i=0u; i<img->height; i++) {
        free(img->data[i]);
    }
    free(img->data);
}
