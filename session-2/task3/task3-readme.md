# Task 3: Creating a Makefile



## Makefile Basics
A makefile consists of a set of rules, each with the following format:

```
target: dependencies
<tab>commands
```

- **target**: What we're trying to build (executable, object file, etc.)
- **dependencies**: Files that the target depends on
- **commands**: Shell commands to build the target (must be indented with a tab, not spaces)

**IMPORTANT**: Commands must be indented with an actual tab character, not spaces. This is a common source of errors in makefiles!

## Step 1: Create a Basic Makefile
Create a file named `Makefile` (note: no file extension) with a basic rule to build your student program:

```make
student_program: main.c student.c student.h
	gcc main.c student.c -o student_program
```

This tells make: "To build student_program, you need main.c, student.c, and student.h, 
and the command to build it is gcc main.c student.c -o student_program."

Test this makefile by running:
```bash
make
```

## Step 2: Add Variables
Makefiles become more maintainable when you use variables. Add variables for the compiler, compiler flags, and target:

```make
# Variables
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = student_program

# Default target
$(TARGET): main.c student.c student.h
	$(CC) $(CFLAGS) main.c student.c -o $(TARGET)
```

Test this version:
```bash
make
```

## Step 3: Add Object Files and Separate Compilation
For larger projects, it's more efficient to compile source files into object files separately, then link them together:

```make
# Variables
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = student_program
OBJS = main.o student.o

# Default target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Object files
main.o: main.c student.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c
```

This approach compiles each source file into an object file, then links them together. Make will only recompile files that have changed.

Test this version:
```bash
make
```

Notice that make determines which files need to be recompiled based on their modification times. 
If a source file is newer than its corresponding object file, or if a header file included by a source file has changed, 
make will recompile that source file.

Try changing one of your source files and running make again. Notice that only the changed file is recompiled.

## Step 4: Add a Clean Target
It's common to include a "clean" target that removes all generated files:

```make
# Variables
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = student_program
OBJS = main.o student.o

# Default target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Object files
main.o: main.c student.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)
```

Test the clean target:
```bash
make clean
```

This should remove all .o files and the executable.

## Step 5: Add an "all" Target and Phony Targets
It's a common convention to include an "all" target that builds everything. 
We'll also mark targets that don't represent actual files as "phony":

```make
# Variables
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = student_program
OBJS = main.o student.o

# Phony targets (not actual files)
.PHONY: all clean

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Object files
main.o: main.c student.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h
	$(CC) $(CFLAGS) -c student.c

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)
```

Now you can run:
```bash
make all
```

Which is equivalent to just running `make` since "all" is the first target.

## Step 6: Use Pattern Rules (Optional)
For larger projects with many similar files, you can use pattern rules to simplify your makefile:

```make
# Variables
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = student_program
OBJS = main.o student.o

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Pattern rule for object files
%.o: %.c student.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)
```

This uses a pattern rule with automatic variables:
- `$<` represents the first dependency (the .c file)
- `$@` represents the target (the .o file)

## Common Issues with Makefiles

1. **Spaces vs. Tabs**: Commands in makefiles must be indented with tabs, not spaces. This is the most common source of errors.
   - Error message: `Makefile:4: *** missing separator. Stop.`
   - Solution: Ensure your editor uses tabs for indentation in makefiles.
   - Check with: `cat -e Makefile` (tabs will appear as `^I`)

2. **Missing Dependencies**: If you forget to include a dependency, make won't know when to rebuild a target.
   - Symptom: Changes to files don't trigger rebuilds when they should
   - Solution: Ensure all dependencies are listed for each target

3. **Circular Dependencies**: When two targets directly or indirectly depend on each other.
   - Error message: `Circular target1 <- target2 <- target1 dependency dropped.`
   - Solution: Redesign your makefile to remove the circular dependency

4. **Phony Targets**: Targets like "clean" don't create files named "clean". Without .PHONY, if a file named "clean" exists, the target may not run.
   - Solution: Use `.PHONY: clean all` for targets that don't produce files

## Testing Your Makefile

To fully test your makefile:

1. Run `make clean` to start fresh
2. Run `make` to build everything
3. Run `make` again - nothing should rebuild unless you've made changes
4. Modify student.c and run `make` - only student.c should recompile
5. Modify student.h and run `make` - both student.c and main.c should recompile
6. Run `make clean` and verify all generated files are removed

## Reflection Questions

1. How does using a makefile improve the development process compared to manual compilation?
2. Why is it better to compile to object files first rather than directly to an executable?
3. Why is it important to list header files as dependencies for object files?
4. How would you modify the makefile to add a new source file (e.g., utils.c and utils.h)?
5. What is the purpose of the PHONY target, and why is it used for targets like "clean"?

## Extension Tasks

1. Add a "debug" target that compiles the program with debugging symbols (-g flag)
2. Create a directory structure with src/, include/, and obj/ folders and update the makefile to handle this structure
3. Add automatic dependency generation using gcc's -MMD and -MP flags
4. Add a "run" target that builds and then executes the program
5. Add a "release" target that builds with optimisation flags (-O2 or -O3)

## Makefile Best Practices

- Use variables for compiler, flags, file lists, and directories
- Include header files as dependencies for object files
- Use pattern rules for similar tasks
- Mark non-file targets as .PHONY
- Include both "all" and "clean" targets
- Use descriptive variable names
- Add comments explaining complex parts
- Keep rules organised by their purpose
- Test your makefile thoroughly with different scenarios

## Learning Objectives
By the end of this activity, you should be able to:
- Create a basic makefile for a multi-file C project
- Understand makefile syntax and structure
- Define dependencies correctly
- Use variables in makefiles
- Create both build and utility targets (e.g., clean)

## Background
In the previous activity, we modularised the student record management program into separate header and implementation files. 
Now, we'll create a makefile to automate the build process for this project. 
This will allow us to compile our program with a simple `make` command, and only recompile the necessary files when changes are made.