/* pgm_image.h */
#ifndef PGM_IMAGE_H
#define PGM_IMAGE_H

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct {
    uint width, height;
    uchar maxGrey;
    uchar** data;
} PGMImage_t;


//Generic exit condition for the functions to return an "Invalid" image.
#define EXIT_BAD_IMG img.data=NULL; img.width=0.0f; img.height=0.0f; img.maxGrey=0.0f; return img;


//PGM image
PGMImage_t pgm_allocateImage(int width, int height);
void pgm_freeImage(PGMImage_t* image);


#endif