/* student.h */
#ifndef STUDENT_H
#define STUDENT_H

#include "structure.h"

float s_calculateAverage(student_t student_t);
void s_displayStudent(student_t student);
void s_updateName(student_t *student, const char *new_name);
int s_updateMark(student_t *student, int module_index, float new_mark);

#endif