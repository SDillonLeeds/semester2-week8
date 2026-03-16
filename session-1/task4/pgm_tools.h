/* pgm_tools.h */
#ifndef PGM_TOOLS_H
#define PGM_TOOLS_H


/* TODO: Define a PGMImage structure that encapsulates:
   - width and height
   - max_gray value
   - 2D array of pixel values (pixels)
*/

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct {
    float width, height;
    uchar maxGrey;
    uchar** data;
} PGMImage_t;



PGMImage_t allocateImage(int width, int height);
void freeImage(PGMImage_t* image);
PGMImage_t readPGMimage(const char* filePath);
void printImageInfo(const char* filePath, PGMImage_t* img);
void printImageValues(PGMImage_t* image);
PGMImage_t invertImageColours(PGMImage_t* original);
PGMImage_t rotateImage(PGMImage_t* original, int degrees);
int savePGMimage(const char* filePath, PGMImage_t* image);
int getUserMenuChoice(const char* message);
void displayMenu(void);


#endif