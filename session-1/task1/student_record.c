/* student_record.c */

#include <stdio.h>
#include <string.h>

#include "student_record.h"


float calculateAverageMark(studentRecord_t* student) {
    float sum = 0.0f;
    for (unsigned int idx=0u; idx<NUM_MODULES; idx++) {
        sum += student->marks[idx];
    }
    
    return sum / NUM_MODULES;
}
void displayStudent(studentRecord_t* student) {
    printf("Student {\n    Name: %s\n    ID: %u\n    Marks: {\n", student->name, student->ID);
    for (unsigned int idx=0u; idx<NUM_MODULES; idx++) {
        printf("        %.0f,\n", student->marks[idx]);
    }
    printf("    }\n    Average Mark: %.0f\n}\n", calculateAverageMark(student));
}

/*
 * main
 */
int main( void ) {    
    studentRecord_t student = {
        "John Smith", 12345, {75.0f, 68.5f, 81.0f}
    };
    
    displayStudent(&student);
    
    return 0;
}