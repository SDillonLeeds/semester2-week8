# Activity 3: Modularising PGM Tools

## Learning Objectives
By the end of this activity, you should be able to:
- Identify logical components for modularisation in a larger program
- Design appropriate module boundaries and interfaces
- Create a multi-module C project with clear separation of concerns
- Implement a professional project directory structure
- Create a makefile for a multi-file project
- Apply modularisation principles to a real-world example

## Background
In this activity, you'll refactor the PGM image tools program from last week's structures session into a properly modularised structure. The PGM tools program allows people to read, display, invert, and rotate PGM (Portable Gray Map) images.

This is a more substantial exercise that will likely extend beyond the lab session. You should aim to complete the analysis, planning, and header file creation during the session, and finish the implementation and testing as independent study.

## Starting Point
You'll begin with the original, single-file PGM tools program which you worked with in the previous session. If you don't have your own version, a reference implementation is available in the course materials.

## Step 1: Analyse the Program Structure
Carefully examine the PGM tools program to identify distinct components that could be separated into modules. Consider the following questions:

1. What are the main functional areas of the program?
2. Which functions are related and could be grouped together?
3. What data structures are used, and which functions operate on them?
4. What naming conventions would provide clarity and consistency?
5. What are the dependencies between different parts of the program?

**Deliverable**: Create a brief modularisation plan document (1-2 paragraphs) explaining your approach to breaking down the program. Identify 3-5 logical modules and justify their boundaries.

## Step 2: Create Project Directory Structure
Create a directory structure for your modularised project. A typical structure might include:

```
pgm_tools/
├── include/       (Header files)
├── src/           (Source files)
├── obj/           (Object files - will be created during compilation)
└── Makefile
```

You can create this structure with the following terminal commands:

```bash
mkdir -p pgm_tools/include pgm_tools/src pgm_tools/obj
cd pgm_tools
touch Makefile
```

## Step 3: Define Module Interfaces
Based on your analysis, create header files for each module you've identified. Focus on defining clear interfaces that hide implementation details.

For each module:
1. Decide what functionality belongs in that module
2. Determine what functions should be exposed in the interface
3. Create a header file with appropriate include guards
4. Define necessary structures and function prototypes
5. Document the purpose of each function with comments

Here's an example skeleton for a module header file:

```c
/**
 * @file pgm_image.h
 * @brief Structure definition and basic operations for PGM images
 */

#ifndef PGM_IMAGE_H
#define PGM_IMAGE_H

/* TODO: Define your image structure here */

/* TODO: Declare functions for creating, freeing, and manipulating images */

#endif /* PGM_IMAGE_H */
```

**Deliverable**: Create header files for each module you identified in Step 1.

## Step 4: Implement Module Functions
Create implementation files (.c files) for each module:

1. Include the module's own header file first
2. Include any other necessary headers
3. Implement all functions declared in the header
4. Follow consistent error handling and memory management patterns

When implementing the modules:
- Ensure each function does exactly what its header documentation promises
- Provide appropriate error checking and handling
- Follow consistent naming conventions
- Consider edge cases and handle them gracefully

**Deliverable**: Create implementation files for each module.

## Step 5: Implement Main Program
Create a main.c file that uses your modules to implement the functionality of the original program:

1. Include all necessary module headers
2. Implement the main function using your modularised functions
3. Focus on program flow rather than implementation details
4. Ensure the behaviour matches the original program

## Step 6: Create a Makefile
Create a makefile to compile your modularised program. Your makefile should:

1. Define variables for compiler, compiler flags, and directories
2. Include rules for building the final executable
3. Include rules for building each object file
4. Include a clean target to remove generated files
5. Use appropriate dependencies to trigger recompilation when needed

Here's a starter makefile you can adapt:

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

# Default target
all: $(TARGET)

# You need to add rules for:
# 1. Creating the executable from object files
# 2. Compiling source files into object files
# 3. Cleaning generated files
# 4. Handling dependencies

# Phony targets
.PHONY: all clean
```

**Remember**: Commands in makefiles must be indented with tabs, not spaces.

## Step 7: Test Your Modularised Program
Compile and test your program to ensure it works correctly:

1. Run your makefile to build the program
2. Test the program with sample PGM images
3. Verify that all functionality works as expected
4. Test error handling by providing invalid inputs

## Design Considerations

As you work on modularising the PGM tools program, consider these design questions:

1. **Module Boundaries**: What logical groupings make the most sense for this application? How would you determine what belongs in each module?

2. **Naming Conventions**: What prefix or naming pattern will you use for functions within each module?

3. **Data Structures**: Should the image structure be visible to all modules, or should some modules only interact with it through function calls?

4. **Error Handling**: What consistent approach to error reporting will you use across modules?

5. **Memory Management**: Which module should be responsible for allocating and freeing memory?

## Modularisation Principles to Follow

Throughout this activity, keep these principles in mind:

1. **Single Responsibility**: Each module should have a clear, focused purpose
2. **Information Hiding**: Only expose what's necessary in the interface
3. **Low Coupling**: Minimise dependencies between modules
4. **High Cohesion**: Related functionality should be grouped together
5. **Consistent Interfaces**: Use consistent naming and parameter patterns
6. **Clear Documentation**: Document all public functions thoroughly

## Suggested Module Breakdown

While you should develop your own modularisation plan, here's one possible approach to consider:

1. **Image Module**: Core structure definition and memory management
2. **I/O Module**: File reading and writing operations
3. **Processing Module**: Image manipulation algorithms
4. **Display Module**: Interface and image display functions
5. **Main Program**: Program flow and interaction

## Reflection Questions

After completing the activity, consider the following questions:

1. How did you decide on the boundaries between modules? What criteria did you use?
2. What challenges did you encounter during the modularisation process?
3. How does your modularised version improve upon the original single-file implementation?
4. If you were to add a new feature (e.g., image blurring), how would your modular structure accommodate this?
5. How might you further improve the modular design of this program?

## Extension Tasks

If you complete the main activity, try these extensions:

1. Add a new image processing function (e.g., blur, threshold, edge detection)
2. Implement automated testing for your modules
3. Enhance error handling with a dedicated error reporting module
4. Modify the image structure to use opaque types for better information hiding
5. Add support for another image format (e.g., PPM)
