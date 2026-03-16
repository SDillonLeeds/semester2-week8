/* student_record.h */

#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

#define NAME_LENGTH 50
#define NUM_MODULES 3

typedef unsigned int uint;
typedef struct {
    char name[NAME_LENGTH];  // Student's name
    uint ID;                  // Student's ID number
    float marks[NUM_MODULES]; // Marks for three modules
} studentRecord_t;

/*
 * function headers
 */
float calculateAverageMark(studentRecord_t* student);
void displayStudent(studentRecord_t* student);

#endif