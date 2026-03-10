# PGM Tools Modularisation Guide

This guide provides a visual walkthrough of how to modularise the PGM tools program from last week's session. 

## Original Single-File Structure

The original `pgm_tools.c` program had the following components all in a single file:

```
┌─────────────────────────────────────────────┐
│              pgm_tools.c                    │
├─────────────────────────────────────────────┤
│ #include <stdio.h>                          │
│ #include <stdlib.h>                         │
│ #include <string.h>                         │
├─────────────────────────────────────────────┤
│ typedef struct {                            │
│     int width;                              │
│     int height;                             │
│     int max_gray;                           │
│     unsigned char **pixels;                 │
│ } PGMImage;                                 │
├─────────────────────────────────────────────┤
│ PGMImage *create_empty_pgm_image()          │
│ void free_pgm_image()                       │
├─────────────────────────────────────────────┤
│ PGMImage *read_pgm_image()                  │
│ int save_pgm_image()                        │
├─────────────────────────────────────────────┤
│ void print_image_info()                     │
│ void print_image_values()                   │
│ void display_menu()                         │
│ int get_user_menu_choice()                  │
├─────────────────────────────────────────────┤
│ PGMImage *invert_image_colors()             │
│ PGMImage *rotate_image()                    │
├─────────────────────────────────────────────┤
│ int main()                                  │
└─────────────────────────────────────────────┘
```

## Modular Structure

The modularised version separates these components into logical modules:

```
┌────────────────────────┐
│   pgm_image.h          │
├────────────────────────┤
│ typedef struct {       │
│   int width;           │
│   int height;          │
│   int max_gray;        │
│   unsigned char **...  │
│ } PGMImage;            │
│                        │
│ Function declarations: │
│ - pgm_create_image()   │
│ - pgm_free_image()     │
└────────────────────────┘
          ↑
          │ includes
          │
┌────────────────────────┐
│   pgm_io.h             │
├────────────────────────┤
│ #include "pgm_image.h" │
│                        │
│ Function declarations: │
│ - pgm_read_image()     │
│ - pgm_save_image()     │
└────────────────────────┘
          ↑
          │ includes
          │
┌────────────────────────┐
│   pgm_process.h        │
├────────────────────────┤
│ #include "pgm_image.h" │
│                        │
│ Function declarations: │
│ - pgm_invert_colors()  │
│ - pgm_rotate_image()   │
└────────────────────────┘
          ↑
          │ includes
          │
┌────────────────────────┐
│   pgm_display.h        │
├────────────────────────┤
│ #include "pgm_image.h" │
│                        │
│ Function declarations: │
│ - pgm_print_info()     │
│ - pgm_print_pixels()   │
│ - pgm_display_menu()   │
│ - pgm_get_user_choice()│
└────────────────────────┘
          ↑
          │ includes
          │
┌────────────────────────┐
│   main.c               │
├────────────────────────┤
│ #include "pgm_image.h" │
│ #include "pgm_io.h"    │
│ #include "pgm_process.h"│
│ #include "pgm_display.h"│
│                        │
│ int main() {           │
│   // Program logic     │
│ }                      │
└────────────────────────┘
```

Each header file has a corresponding implementation file (.c) that provides the actual code:

```
┌────────────────────────┐
│   pgm_image.c          │
├────────────────────────┤
│ #include "pgm_image.h" │
│                        │
│ Implementation of:     │
│ - pgm_create_image()   │
│ - pgm_free_image()     │
└────────────────────────┘

┌────────────────────────┐
│   pgm_io.c             │
├────────────────────────┤
│ #include "pgm_io.h"    │
│                        │
│ Implementation of:     │
│ - pgm_read_image()     │
│ - pgm_save_image()     │
└────────────────────────┘

┌────────────────────────┐
│   pgm_process.c        │
├────────────────────────┤
│ #include "pgm_process.h"│
│                        │
│ Implementation of:     │
│ - pgm_invert_colors()  │
│ - pgm_rotate_image()   │
└────────────────────────┘

┌────────────────────────┐
│   pgm_display.c        │
├────────────────────────┤
│ #include "pgm_display.h"│
│                        │
│ Implementation of:     │
│ - pgm_print_info()     │
│ - pgm_print_pixels()   │
│ - pgm_display_menu()   │
│ - pgm_get_user_choice()│
└────────────────────────┘
```

## Dependency Structure

The key to good modularisation is understanding the dependencies between modules:

```
pgm_image.h  ← (no dependencies on other modules)
    ↑
    │
pgm_io.h     ← depends on pgm_image.h
    ↑
    │
pgm_process.h ← depends on pgm_image.h
    ↑
    │
pgm_display.h ← depends on pgm_image.h
    ↑
    │
main.c       ← depends on all modules
```

This structure forms a hierarchical dependency graph, where higher-level modules depend on lower-level ones, but not vice versa. This is a key principle of good modular design.

## Naming Conventions

Note the consistent naming conventions:

1. **Module prefixes**: All functions in a module have a consistent prefix (e.g., `pgm_` followed by the module name), making it clear which module they belong to.

2. **File names**: Files are named after the module they implement.

3. **Include guards**: Include guards use the uppercase file name with underscores (e.g., `PGM_IMAGE_H`).

## Directory Structure

A typical directory structure for the modularised PGM tools would be:

```
pgm_tools/
├── include/
│   ├── pgm_image.h
│   ├── pgm_io.h
│   ├── pgm_process.h
│   └── pgm_display.h
├── src/
│   ├── pgm_image.c
│   ├── pgm_io.c
│   ├── pgm_process.c
│   ├── pgm_display.c
│   └── main.c
├── obj/
└── Makefile
```

This structure separates interfaces (headers) from implementations (source files) and provides a directory for intermediate build products (object files).

## Makefile Example

Here's a sample makefile for the modularised PGM tools:

```make
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./include

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Target executable
TARGET = pgm_tools

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Default target
all: $(TARGET)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Link object files to create executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
```

## Benefits of Modularisation for PGM Tools

Modularising the PGM tools program provides several key benefits:

1. **Improved maintainability**: Each module has a clear responsibility, making it easier to understand and modify.

2. **Better code organisation**: The structure clearly separates different aspects of the program (image representation, I/O, processing, display).

3. **Reusability**: The PGM image module could be used in other programs that need to work with PGM images.

4. **Easier collaboration**: Different team members could work on different modules without conflicts.

5. **Selective compilation**: Only modified modules need to be recompiled, saving time during development.

6. **Testability**: Each module can be tested independently, making it easier to verify correctness.

## Why This Modularisation Approach Works

The modularisation approach used here follows several important principles:

### 1. Separation of Concerns
Each module has a single, well-defined responsibility:
- `pgm_image`: Core data structure
- `pgm_io`: File operations
- `pgm_process`: Image processing algorithms
- `pgm_display`: User interface elements

### 2. Information Hiding
Each module exposes only what's necessary through its header file and hides implementation details in its .c file. For example:
- The implementation of how pixels are stored is hidden within the image module
- The details of file format parsing are hidden within the I/O module
- The algorithms for image processing are hidden within the process module

### 3. Clear Dependencies
The dependency structure is clear and hierarchical, avoiding circular dependencies:
- All modules depend on `pgm_image.h`
- No higher-level module is used by a lower-level module

### 4. Consistent Interfaces
The function interfaces are consistent across modules:
- All functions that create a new image return a pointer to the image or NULL if the operation fails
- All functions that could fail return an integer status code (1 for success, 0 for failure)
- All functions follow a consistent naming convention

## Example: Adding a New Feature

To demonstrate the power of this modular structure, let's consider how you would add a new feature: image blurring.

1. **Identify the appropriate module**: Since blurring is an image processing operation, it belongs in the `pgm_process` module.

2. **Update the header file** (`pgm_process.h`):
```c
/**
 * @brief Applies a blur effect to the image
 * 
 * @param image Pointer to the original image
 * @param radius Blur radius (higher values create more blur)
 * @return PGMImage* Pointer to the new blurred image, or NULL if operation fails
 */
PGMImage *pgm_blur_image(const PGMImage *image, int radius);
```

3. **Implement the function** in `pgm_process.c`:
```c
PGMImage *pgm_blur_image(const PGMImage *image, int radius) {
    // Implementation of blur algorithm
    // ...
}
```

4. **Update the main program** (`main.c`) to add a new menu option:
```c
case 5: /* Blur image */
    printf("Enter blur radius: ");
    scanf("%d", &blur_radius);
    getchar(); /* Consume newline */
    
    printf("Blurring image...\n");
    processed_image = pgm_blur_image(image, blur_radius);
    
    // Rest of the code similar to other operations
    // ...
    break;
```

Notice how the modular structure makes it easy to add new functionality without modifying existing code (except for the main program that needs a new menu option). This is the power of well-designed modular code.