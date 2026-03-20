/* main.c */

#include <stdlib.h>
#include <stdio.h>
#include "inc/pgm_image.h"
#include "inc/pgm_display.h"
#include "inc/pgm_io.h"
#include "inc/pgm_process.h"

int main(int argc, char** argv) {
    /* Check command line arguments */
    if (argc != 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    /* TODO: Refactor this section to use your PGMImage structure */
    /* Variables to store image dimensions and max gray value */
    
    /* Read the image */
    PGMImage_t image = io_readPGMimage(argv[1]);
    
    /* Check if image reading was successful */
    if (image.data == NULL) {
        return 1;
    }
    
    /* Display image information */
    d_printImageInfo(argv[1], &image);

    int choice = -1;
    char outputFilepath[100];
    int rotationDeg;
    PGMImage_t processedImage = image; //Direct copy of original until modified.

    /* Main program loop */
    do {
        choice = -1;
        m_displayMenu();
        while (choice < 1)
            choice = m_getUserMenuChoice("Enter choice");

        switch (choice) {
        case 1: /* View image */
            d_printImageValues(&image);
            break;
            
        case 2: /* Invert image */
            /* TODO: Refactor this section to use your PGMImage structure */
            printf("Inverting image colours...\n");
            p_invertImageColours(&image, &processedImage);
            
            printf("Enter output filePath: ");
            scanf("%99s", outputFilepath);
            getchar(); /* Consume newline */
            
            if (io_savePGMimage(outputFilepath, &processedImage)) {
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
            p_rotateImage(&image, &processedImage, rotationDeg);
            
            printf("Enter output filePath: ");
            scanf("%99s", outputFilepath);
            getchar(); /* Consume newline */
            
            /* For 90 and 270 degree rotations, height and width are swapped */
            if (rotationDeg == 90 || rotationDeg == 270) {
                if (io_savePGMimage(outputFilepath, &processedImage)) {
                    printf("Rotated image saved to %s\n", outputFilepath);
                } else {
                    printf("Failed to save rotated image\n");
                }
            } else { /* 180 degrees */
                if (io_savePGMimage(outputFilepath, &processedImage)) {
                    printf("Rotated image saved to %s\n", outputFilepath);
                } else {
                    printf("Failed to save rotated image\n");
                }
            }
            break;
            
        case 4: /* Quit */
            printf("Exiting program...\n");
            /* Free the original image memory before exiting */
            pgm_freeImage(&image);
            pgm_freeImage(&processedImage);
            return 0;
            
        default:
            printf("Invalid choice, please try again\n");
            break;
        }
    } while (1);
}


