/* pgm_tools.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm_tools.h"


/* TODO: Update these function prototypes to use your PGMImage structure */
/* Function prototypes */
PGMImage_t allocateImage(int height);
void freeImage(PGMImage_t* image);
PGMImage_t readPGMimage(const char* filePath);
void printImageInfo(const char* filePath);
void printImageValues(PGMImage_t* image, int height, int width);
PGMImage_t invertImageColours(PGMImage_t* original);
PGMImage_t rotateImage(PGMImage_t* original, int degrees);
int savePGMimage(const char* filePath, PGMImage_t* image);
int getUserMenuChoice(const char* message);
void displayMenu(void);

int main(int argc, char** argv) {
    /* Check command line arguments */
    if (argc != 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    /* TODO: Refactor this section to use your PGMImage structure */
    /* Variables to store image dimensions and max gray value */
    int height, width, maxGrey;
    unsigned char** imagePixels;
    
    /* Read the image */
    imagePixels = readPGMimage(argv[1], &height, &width, &maxGrey);
    
    /* Check if image reading was successful */
    if (imagePixels == NULL) {
        return 1;
    }
    
    /* Display image information */
    printImageInfo(argv[1], height, width, maxGrey);

    int choice = -1;
    char outputFilepath[100];
    int rotationDeg;
    unsigned char** processedImage = NULL;

    /* Main program loop */
    do {
        choice = -1;
        displayMenu();
        while (choice < 1)
            choice = getUserMenuChoice("Enter choice");

        switch (choice) {
        case 1: /* View image */
            printImageValues(imagePixels, height, width);
            break;
            
        case 2: /* Invert image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Inverting image colours...\n");
            processedImage = invertImageColours(imagePixels, height, width, maxGrey);
            
            printf("Enter output filePath: ");
            scanf("%99s", outputFilepath);
            getchar(); /* Consume newline */
            
            if (savePGMimage(outputFilepath, processedImage, height, width, maxGrey)) {
                printf("Inverted image saved to %s\n", outputFilepath);
            } else {
                printf("Failed to save inverted image\n");
            }
            
            /* Free the processed image memory */
            freeImage(processedImage, height);
            break;
            
        case 3: /* Rotate image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Enter rotation in degrees (90, 180, or 270): ");
            scanf("%d", &rotationDeg);
            getchar(); /* Consume newline */
            
            /* Validate rotation degrees */
            if (rotationDeg != 90 && rotationDeg != 180 && rotationDeg != 270) {
                printf("Invalid rotation angle. Please use 90, 180, or 270 degrees.\n");
                break;
            }
            
            printf("Rotating image by %d degrees...\n", rotationDeg);
            processedImage = rotateImage(imagePixels, height, width, rotationDeg);
            
            printf("Enter output filePath: ");
            scanf("%99s", outputFilepath);
            getchar(); /* Consume newline */
            
            /* For 90 and 270 degree rotations, height and width are swapped */
            if (rotationDeg == 90 || rotationDeg == 270) {
                if (savePGMimage(outputFilepath, processedImage, width, height, maxGrey)) {
                    printf("Rotated image saved to %s\n", outputFilepath);
                } else {
                    printf("Failed to save rotated image\n");
                }
                freeImage(processedImage, width);
            } else { /* 180 degrees */
                if (savePGMimage(outputFilepath, processedImage, height, width, maxGrey)) {
                    printf("Rotated image saved to %s\n", outputFilepath);
                } else {
                    printf("Failed to save rotated image\n");
                }
                freeImage(processedImage, height);
            }
            break;
            
        case 4: /* Quit */
            printf("Exiting program...\n");
            /* Free the original image memory before exiting */
            freeImage(imagePixels, height);
            return 0;
            
        default:
            printf("Invalid choice, please try again\n");
            break;
        }
    } while (1);
}

/**
*  @brief Gets user menu choice from standard input
*  
*  @param message The prompt message to display
*  @return int The user's choice, or -1 if invalid input
 */
int getUserMenuChoice(const char* message) {
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

/**
*  @brief Displays the main program menu
 */
void displayMenu(void) {
    printf("\n----- PGM Image Tool Menu -----\n");
    printf("1 - View PGM Image\n");
    printf("2 - Invert Image\n");
    printf("3 - Rotate Image\n");
    printf("4 - Quit\n");
}

/**
*  @brief Allocates a 2D array for storing the image pixels
*  
*  @param width Number of columns in the image
*  @param height Number of rows in the image
*  @return PGMImage_t allocated image.
 */
PGMImage_t allocateImage(int width, int height) {
    PGMImage_t img;
    img.width = width;
    img.height = height;

    img.data = calloc(height, sizeof(uchar*));
    if (img.data == NULL) {
        printf("Error: Memory allocation failed for image array\n");
        return NULL;
    }
    
    for (uint i=0u; i<height; i++) {
        img.data[i] = calloc(width, sizeof(uchar));
        if (img.data[i] == NULL) {
            /* Free previously allocated memory if this allocation fails */
            for (uint j=0u; j<i; j++) {
                free(img.data[j]);
            }
            free(img.data);
            printf("Error: Memory allocation failed for image row %d\n", i);
            return NULL;
        }
    }

    return img;
}

/**
*  @brief Frees memory allocated for a 2D image array
*  
*  @param image The PGM image to free
 */
void freeImage(PGMImage_t* img) {
    if (img->data == NULL) return;
    
    for (uint i=0u; i<img->height; i++) {
        free(img->data[i]);
    }
    free(img->data);
}

/**
*  @brief Reads a PGM image from a file
*  
*  @param filePath Path to the PGM file
*  @param height Pointer to store the image height
*  @param width Pointer to store the image width
*  @param maxGrey Pointer to store the max gray value
*  @return unsigned char** 2D array of image pixels, or NULL if reading fails
 */
PGMImage_t readPGMimage(const char* filePath) {
    int width, height;

    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filePath);
        return NULL;
    }
    
    /* Read PGM header */
    char magicNumber[3];
    if (fscanf(file, "%2s", magicNumber) != 1) {
        printf("Error: Invalid PGM file format\n");
        fclose(file);
        return NULL;
    }
    
    if (strcmp(magicNumber, "P2") != 0) {
        printf("Error: File is not a valid PGM file (P2 format)\n");
        fclose(file);
        return NULL;
    }
    
    if (fscanf(file, "%d %d", &width, &height) != 2) {
        printf("Error: Could not read image dimensions\n");
        fclose(file);
        return NULL;
    }
    
    if (fscanf(file, "%d", maxGrey) != 1) {
        printf("Error: Could not read max gray value\n");
        fclose(file);
        return NULL;
    }
    
    /* Allocate memory for the pixel array */
    PGMImage_t img = allocateImage(height, width);
    if (img.data == NULL) {
        fclose(file);
        return NULL;
    }
    
    /* Read pixel values */
    int pixelValue;
    for (uint i=0u; i<height; i++) {
        for (uint j=0u; j<width; j++) {
            if (fscanf(file, "%d", &pixelValue) != 1) {
                printf("Error: Could not read pixel value at position (%d,%d)\n", j, i);
                freeImage(img);
                fclose(file);
                return NULL;
            }
            img.data[i][j] = (unsigned char)pixelValue;
        }
    }
    
    fclose(file);
    return img;
}

/**
*  @brief Prints information about the PGM image
*  
*  @param filePath Name of the image file
*  @param height Image height
*  @param width Image width
*  @param maxGrey Maximum gray value
 */
void printImageInfo(const char* filePath, PGMImage_t* img) {
    /* TODO: Refactor this to use your PGMImage structure */
    printf("Image: %s\n", filePath);
    printf("Dimensions: %d x %d pixels\n", img->width, img->height);
    printf("Max Gray Value: %d\n", img->maxGrey);
}

/**
*  @brief Prints the pixel values of the image
*  
*  @param pixels The 2D array of image pixels
*  @param height Image height
*  @param width Image width
 */
void printImageValues(PGMImage_t* img) {
    /* TODO: Refactor this to use your PGMImage structure */
    printf("\nImage Pixel Values (%dx%d):\n", img->width, img->height);
    for (uint i=0; i<img->height; i++) {
        for (uint j=0u; j<img->width; j++) {
            printf("%3d ", img->data[i][j]);
        }
        printf("\n");
    }
}

/**
*  @brief Inverts the colours of the image (255-value)
*  
*  @param originalImage Original image pixels
*  @param height Image height
*  @param width Image width
*  @param maxGrey Maximum gray value
*  @return unsigned char** New image with inverted colours
 */
PGMImage_t invertImageColours(PGMImage_t* originalImage) {
    /* TODO: Refactor this to use your PGMImage structure */
    /* Allocate memory for the inverted image */
    PGMImage_t invImage = allocateImage(originalImage->height, originalImage->width);
    if (invImage.data == NULL) {
        return NULL;
    }
    
    /* Invert each pixel (maxGrey - value) */
    for (uint i=0u; i<originalImage->height; i++) {
        for (uint j=0u; j<originalImage->width; j++) {
            invImage.data[i][j] = originalImage->maxGrey - originalImage->data[i][j];
        }
    }
    
    return invImage;
}

/**
*  @brief Rotates the image by the specified angle
*  
*  @param originalImage Original image pixels
*  @param height Image height
*  @param width Image width
*  @param degrees Rotation angle (90, 180, or 270 degrees)
*  @return unsigned char** New rotated image
 */
unsigned char** rotateImage(unsigned char** originalImage, int height, int width, int degrees) {
    /* TODO: Refactor this to use your PGMImage structure */
    unsigned char** rotImage;
    
    switch (degrees) {
        case 90:
            /* For 90 degrees, width and height are swapped */
            rotImage = allocateImage(width, height);
            if (rotImage == NULL) {
                return NULL;
            }
            
            /* 90 degree rotation algorithm */
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    rotImage[j][height-1-i] = originalImage[i][j];
                }
            }
            break;
            
        case 180:
            rotImage = allocateImage(height, width);
            if (rotImage == NULL) {
                return NULL;
            }
            
            /* 180 degree rotation algorithm */
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    rotImage[height-1-i][width-1-j] = originalImage[i][j];
                }
            }
            break;
            
        case 270:
            /* For 270 degrees, width and height are swapped */
            rotImage = allocateImage(width, height);
            if (rotImage == NULL) {
                return NULL;
            }
            
            /* 270 degree rotation algorithm */
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    rotImage[width-1-j][i] = originalImage[i][j];
                }
            }
            break;
            
        default:
            printf("Error: Invalid rotation angle\n");
            return NULL;
    }
    
    return rotImage;
}

/**
*  @brief Saves a PGM image to a file
*  
*  @param filePath Output filePath
*  @param pixels Image pixel array
*  @param height Image height
*  @param width Image width
*  @param maxGrey Maximum gray value
*  @return int 1 if successful, 0 if failed
 */
int savePGMimage(const char* filePath, unsigned char** pixels, int height, int width, int maxGrey) {
    /* TODO: Refactor this to use your PGMImage structure */
    FILE* file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error: Could not create output file %s\n", filePath);
        return 0;
    }
    
    /* Write PGM header */
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "%d\n", maxGrey);
    
    /* Write pixel values */
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(file, "%d ", pixels[i][j]);
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
    return 1;
}
