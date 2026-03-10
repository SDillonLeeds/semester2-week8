
#include <stdio.h>

#include "structure.h"
#include "student.h"

int main( void ) {
    // Create and initialise a student variable
    Student student = {
        .name = "John Smith",
        .id = 12345,
        .marks = {75.0, 68.5, 81.0}
    };
    
    // Display original student information
    printf("Original student record:\n");
    display_student(student);
    
    // Calculate and display the average mark
    float average = calculate_average(student);
    printf("\nThe average mark is: %.1f\n", average);
    
    // Update the student's name and third module mark
    update_name(&student, "Jane Smith");
    update_mark(&student, 2, 92.5); // Update the third module (index 2)
    
    // Display the updated student information
    printf("\nAfter updates:\n");
    display_student(student);
    
    return 0;
}
