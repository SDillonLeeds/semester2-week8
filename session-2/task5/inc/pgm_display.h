/* pgm_display.h */
#ifndef PGM_DISPLAY_H
#define PGM_DISPLAY_H

#include "pgm_image.h"

//Display
void d_printImageInfo(const char* filePath, PGMImage_t* image);
void d_printImageValues(PGMImage_t* image);

//Menu
int m_getUserMenuChoice(const char* message);
void m_displayMenu(void);

#endif