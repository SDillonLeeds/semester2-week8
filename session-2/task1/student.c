/* student.c */

#include <stdio.h>
#include <string.h>

#include "structure.h"


float s_calculateAverage(student_t student_t) {
    float sum = 0.0;
    
    // Sum up all the module marks
    for (int i=0; i<NUM_MODULES; i++) {
        sum += student_t.marks[i];
    }
    
    // Return the average
    return sum / NUM_MODULES;
}


void s_displayStudent(student_t student) {
    float average = s_calculateAverage(student);
    
    printf("Student Information:\n");
    printf("Name: %s\n", student.name);
    printf("ID: %d\n", student.id);
    printf("Module marks: ");
    
    for (int i=0; i<NUM_MODULES; i++) {
        printf("%.1f", student.marks[i]);
        if (i < NUM_MODULES - 1) {
            printf(", ");
        }
    }
    
    printf("\nAverage mark: %.1f\n", average);
}

void s_updateName(student_t *student, const char *new_name) {
    // Use strncpy to avoid buffer overflow
    strncpy(student->name, new_name, NAME_LENGTH - 1);
    student->name[NAME_LENGTH - 1] = '\0'; // Ensure null termination
}

int s_updateMark(student_t *student, int module_index, float new_mark) {
    // Validate the module index
    if ((module_index < 0) || (module_index >= NUM_MODULES)) {
        return 0; // Invalid module index
    }
    
    // Update the mark
    student->marks[module_index] = new_mark;
    return 1; // Success
}