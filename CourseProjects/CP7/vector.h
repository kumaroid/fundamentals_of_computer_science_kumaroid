#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "sparce_matrix.h"

typedef struct _vector {
    int* begin;
    int size;
    int allocated;
} Vector;

void createV(Vector* v); // Создание вектора
void deleteV(Vector* v);
void pushBackV(Vector* v, int value);
void printV(Vector* v);
#endif // __VECTOR_H__