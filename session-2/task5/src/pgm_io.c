/* pgm_io.c */

#include <stdio.h>
#include <string.h>
#include "../inc/pgm_image.h"


//I/O
PGMImage_t io_readPGMimage(const char* filePath) {
    PGMImage_t img;
    uchar maxGrey;

    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filePath);
        EXIT_BAD_IMG;
    }
    
    /* Read PGM header */
    char magicNumber[3];
    if (fscanf(file, "%2s", magicNumber) != 1) {
        printf("Error: Invalid PGM file format\n");
        fclose(file);
        EXIT_BAD_IMG;
    }
    
    if (strcmp(magicNumber, "P2") != 0) {
        printf("Error: File is not a valid PGM file (P2 format)\n");
        fclose(file);
        EXIT_BAD_IMG;
    }
    
    if (fscanf(file, "%u %u", &img.width, &img.height) != 2) {
        printf("Error: Could not read image dimensions\n");
        fclose(file);
        EXIT_BAD_IMG;
    }
    
    if (fscanf(file, "%hhi", &maxGrey) != 1) {
        printf("Error: Could not read max gray value\n");
        fclose(file);
        EXIT_BAD_IMG;
    }
    
    /* Allocate memory for the pixel array */
    img = pgm_allocateImage(img.height, img.width);
    if (img.data == NULL) {
        fclose(file);
        EXIT_BAD_IMG;
    }
    img.maxGrey = maxGrey;
    
    /* Read pixel values */
    int pixelValue;
    for (uint i=0u; i<img.height; i++) {
        for (uint j=0u; j<img.width; j++) {
            if (fscanf(file, "%d", &pixelValue) != 1) {
                printf("Error: Could not read pixel value at position (%d,%d)\n", j, i);
                pgm_freeImage(&img);
                fclose(file);
                EXIT_BAD_IMG;
            }
            img.data[i][j] = (unsigned char)pixelValue;
        }
    }
    
    fclose(file);
    return img;
}



int io_savePGMimage(const char* filePath, PGMImage_t* image) {
    /* TODO: Refactor this to use your PGMImage structure */
    FILE* file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error: Could not create output file %s\n", filePath);
        return 0;
    }
    
    /* Write PGM header */
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%d\n", image->maxGrey);
    
    /* Write pixel values */
    for (uint i=0u; i<image->height; i++) {
        for (uint j=0u; j<image->width; j++) {
            fprintf(file, "%d ", image->data[i][j]);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
    return 1;
}
