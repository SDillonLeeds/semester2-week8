/* structure.h */
#ifndef STRUCTURE_H
#define STRUCTURE_H


//// STRUCT CONSTANTS ////
#define NAME_LENGTH 50
#define NUM_MODULES 3
//// STRUCT CONSTANTS ////


typedef struct {
    char name[NAME_LENGTH];  // Student's name
    int id;                  // Student's ID number
    float marks[NUM_MODULES]; // Marks for three modules
} student_t;

#endif