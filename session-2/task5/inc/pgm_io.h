/* pgm_io.h */
#ifndef PGM_IO_H
#define PGM_IO_H

#include "pgm_image.h"

//I/O
PGMImage_t io_readPGMimage(const char* filePath);
int io_savePGMimage(const char* filePath, PGMImage_t* image);

#endif