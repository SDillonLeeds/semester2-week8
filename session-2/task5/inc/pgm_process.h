/* pgm_process.h */
#ifndef PGM_PROCESS_H
#define PGM_PROCESS_H

#include "pgm_image.h"

//Process
void p_invertImageColours(PGMImage_t* original, PGMImage_t* modified);
void p_rotateImage(PGMImage_t* original, PGMImage_t* modified, int degrees);


#endif