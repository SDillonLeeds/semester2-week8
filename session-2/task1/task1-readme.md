# Task 1: Simple Modularisation

## Code
In this activity, you'll take the Student Record Management program from last week's Structure activity and refactor it into a properly modularised structure. This involves separating the program into four files:

1. **structure.h** - Header file containing structure definition
1. **student.h** - Header file containing function declarations
3. **student.c** - Implementation file containing function definitions
4. **main.c** - Main program file that contains `main()` and uses the student.c functions

## Starting Code
The original, single-file student record program, is provided in the repository: `student_record_orig.c`


## Step 1: Create the data structure Header File (structure.h)
Create a new file named `structure.h` that contains:
- Structure definition

## Step 2: Create the data structure Header File (student.h)
Create a new file named `student.h` that contains:
- Function definitions
- `#define` statements that specify global values

The header files provide the **interface** to your student record source code without implementation details.


## Step 3: Create the source code file (student.c)
Create a new file (or adapt the existing one) named `student.c` that contains:
- Necessary includes - library header files as well as your header files
- Function implementations

This implementation file provides the actual code for the functions, but doesn't include `main()`.

## Step 4: Create the main source code file (main.c)
Create a new file named `main.c` that contains:
- Necessary includes - library header files as well as your header files
- Implementation of your `main()` function

## Step 5: Compile and Test
Compile your modularised program with the following commands:

```bash
# Compilation
gcc student.c main.c -o student

# Run the program
./student
```

The output should be identical to the original single-file program.

## Common Issues

- **"undefined reference"** errors typically indicate you've declared a function in the header but not implemented it in the .c file
- **"multiple definition"** errors often mean missing include guards
- **"implicit declaration"** errors usually mean you forgot to include the header file
- If your program behavior differs from the original, check that all functions are implemented correctly

## Reflection Questions
1. How does separating the program into multiple files improve its organisation?
2. What is the purpose of include guards, and what problems do they prevent?
3. Why do we include the header file in both the implementation file and the main program file?
4. How would you extend this modular structure if you wanted to add more functionality, such as reading/writing student records to a file?

## Extension Tasks
If you finish early, try these extension tasks:

1. Add appropriate documentation and comments to all files
2. Update the program to handle multiple students
3. Create a new module for file operations (e.g., saving and loading student records)

## Learning Objectives
By the end of this activity, you should be able to:
- Separate a C program into header and implementation files
- Implement proper include guards
- Understand the relationship between interface and implementation
- Compile a multi-file C program

