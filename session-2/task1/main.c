/* main.c */
#include <stdio.h>

#include "structure.h"
#include "student.h"



int main() {
    // Create and initialise a student_t instance
    student_t student = {
        .name = "John Smith",
        .id = 12345,
        .marks = {75.0, 68.5, 81.0}
    };
    
    // Display original student_t information
    printf("Original student record:\n");
    s_displayStudent(student);
    
    // Calculate and display the average mark
    float average = s_calculateAverage(student);
    printf("\nThe average mark is: %.1f\n", average);
    
    // Update the student_t's name and third module mark
    s_updateName(&student, "Jane Smith");
    s_updateMark(&student, 2, 92.5); // Update the third module (index 2)
    
    // Display the updated student_t information
    printf("\nAfter updates:\n");
    s_displayStudent(student);
    
    return 0;
}