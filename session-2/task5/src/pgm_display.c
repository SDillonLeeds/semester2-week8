/* pgm_display.c */

#include <stdio.h>
#include "../inc/pgm_image.h"


//Display
void d_printImageInfo(const char* filePath, PGMImage_t* img) {
    printf("Image: %s\n", filePath);
    printf("Dimensions: %d x %d pixels\n", img->width, img->height);
    printf("Max Gray Value: %d\n", img->maxGrey);
}

void d_printImageValues(PGMImage_t* img) {
    printf("\nImage Pixel Values (%dx%d):\n", img->width, img->height);
    for (uint i=0; i<img->height; i++) {
        for (uint j=0u; j<img->width; j++) {
            printf("%3d ", img->data[i][j]);
        }
        printf("\n");
    }
}




//Menu
int m_getUserMenuChoice(const char* message) {
    char buffer[100];
    int choice;
    printf("%s: ", message);
    fgets(buffer, 100, stdin);
    int check = sscanf(buffer, "%d", &choice);
    if (!check) {
        return -1;
    }
    return choice;
}

void m_displayMenu(void) {
    printf("\n----- PGM Image Tool Menu -----\n");
    printf("1 - View PGM Image\n");
    printf("2 - Invert Image\n");
    printf("3 - Rotate Image\n");
    printf("4 - Quit\n");
}