/* pgm_tools.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgm_tools.h"


/* TODO: Update these function prototypes to use your PGMImage structure */
/* Function prototypes */
PGMImage_t allocateImage(int width, int height);
void freeImage(PGMImage_t* image);
PGMImage_t readPGMimage(const char* filePath);
void printImageInfo(const char* filePath, PGMImage_t* image);
void printImageValues(PGMImage_t* image);
void invertImageColours(PGMImage_t* original, PGMImage_t* modified);
void rotateImage(PGMImage_t* original, PGMImage_t* modified, int degrees);
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
    
    /* Read the image */
    PGMImage_t image = readPGMimage(argv[1]);
    
    /* Check if image reading was successful */
    if (image.data == NULL) {
        return 1;
    }
    
    /* Display image information */
    printImageInfo(argv[1], &image);

    int choice = -1;
    char outputFilepath[100];
    int rotationDeg;
    PGMImage_t processedImage = image; //Direct copy of original until modified.

    /* Main program loop */
    do {
        choice = -1;
        displayMenu();
        while (choice < 1)
            choice = getUserMenuChoice("Enter choice");

        switch (choice) {
        case 1: /* View image */
            printImageValues(&image);
            break;
            
        case 2: /* Invert image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Inverting image colours...\n");
            invertImageColours(&image, &processedImage);
            
            printf("Enter output filePath: ");
            scanf("%99s", outputFilepath);
            getchar(); /* Consume newline */
            
            if (savePGMimage(outputFilepath, &processedImage)) {
                printf("Inverted image saved to %s\n", outputFilepath);
            } else {
                printf("Failed to save inverted image\n");
            }
            break;
            
        case 3: /* Rotate image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Enter rotation in degrees (90, 180, or 270): ");
            scanf("%d", &rotationDeg);
            getchar(); /* Consume newline */
            
            /* Validate rotation degrees */
            if ((rotationDeg != 90) && (rotationDeg != 180) && (rotationDeg != 270)) {
                printf("Invalid rotation angle. Please use 90, 180, or 270 degrees.\n");
                break;
            }
            
            printf("Rotating image by %d degrees...\n", rotationDeg);
            rotateImage(&image, &processedImage, rotationDeg);
            
            printf("Enter output filePath: ");
            scanf("%99s", outputFilepath);
            getchar(); /* Consume newline */
            
            /* For 90 and 270 degree rotations, height and width are swapped */
            if (rotationDeg == 90 || rotationDeg == 270) {
                if (savePGMimage(outputFilepath, &processedImage)) {
                    printf("Rotated image saved to %s\n", outputFilepath);
                } else {
                    printf("Failed to save rotated image\n");
                }
            } else { /* 180 degrees */
                if (savePGMimage(outputFilepath, &processedImage)) {
                    printf("Rotated image saved to %s\n", outputFilepath);
                } else {
                    printf("Failed to save rotated image\n");
                }
            }
            break;
            
        case 4: /* Quit */
            printf("Exiting program...\n");
            /* Free the original image memory before exiting */
            freeImage(&image);
            freeImage(&processedImage);
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

//Generic exit condition for the functions to return an "Invalid" image.
#define EXIT_BAD_IMG img.data=NULL; img.width=0.0f; img.height=0.0f; img.maxGrey=0.0f; return img;

PGMImage_t allocateImage(int width, int height) {
    PGMImage_t img;
    img.width = width;
    img.height = height;

    img.data = calloc(height, sizeof(uchar*));
    if (img.data == NULL) {
        printf("Error: Memory allocation failed for image array\n");
        EXIT_BAD_IMG;
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
            EXIT_BAD_IMG;
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
    img = allocateImage(img.height, img.width);
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
                freeImage(&img);
                fclose(file);
                EXIT_BAD_IMG;
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
void invertImageColours(PGMImage_t* originalImage, PGMImage_t* modified) {    
    /* Invert each pixel (maxGrey - value) */
    for (uint i=0u; i<originalImage->height; i++) {
        for (uint j=0u; j<originalImage->width; j++) {
            modified->data[i][j] = originalImage->maxGrey - originalImage->data[i][j];
        }
    }
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
#define WIDTH original->width
#define HEIGHT original->height
void rotateImage(PGMImage_t* original, PGMImage_t* modified, int degrees) {
    switch (degrees) {
        case 90:
            /* For 90 degrees, width and height are swapped */
            *modified = allocateImage(WIDTH, HEIGHT);
            if (modified->data == NULL) {return;}
            
            /* 90 degree rotation algorithm */
            for (uint i=0; i<HEIGHT; i++) {
                for (uint j=0u; j<WIDTH; j++) {
                    modified->data[j][HEIGHT-1-i] = original->data[i][j];
                }
            }
            break;
            
        case 180:            
            /* 180 degree rotation algorithm */
            for (uint i=0u; i<HEIGHT; i++) {
                for (uint j=0u; j<WIDTH; j++) {
                    modified->data[HEIGHT-1-i][WIDTH-1-j] = original->data[i][j];
                }
            }
            break;
            
        case 270:
            /* For 270 degrees, width and height are swapped */
            *modified = allocateImage(WIDTH, HEIGHT);
            if (modified->data == NULL) {return;}
            
            /* 270 degree rotation algorithm */
            for (uint i=0u; i<HEIGHT; i++) {
                for (uint j=0u; j<WIDTH; j++) {
                    modified->data[WIDTH-1-j][i] = original->data[i][j];
                }
            }
            break;
            
        default:
            printf("Error: Invalid rotation angle\n");
            return;
    }
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
int savePGMimage(const char* filePath, PGMImage_t* image) {
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
