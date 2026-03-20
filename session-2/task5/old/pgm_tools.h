/* pgm_tools.h */
#ifndef PGM_TOOLS_H
#define PGM_TOOLS_H


typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct {
    uint width, height;
    uchar maxGrey;
    uchar** data;
} PGMImage_t;



PGMImage_t allocateImage(int width, int height);
void freeImage(PGMImage_t* image);
PGMImage_t readPGMimage(const char* filePath);
void printImageInfo(const char* filePath, PGMImage_t* img);
void printImageValues(PGMImage_t* image);
void invertImageColours(PGMImage_t* original, PGMImage_t* modified);
void rotateImage(PGMImage_t* original, PGMImage_t* modified, int degrees);
int savePGMimage(const char* filePath, PGMImage_t* image);
int getUserMenuChoice(const char* message);
void displayMenu(void);


#endif