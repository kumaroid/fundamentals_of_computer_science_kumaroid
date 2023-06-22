#ifndef __SPARCE_MATRIX__
#define __SPARCE_MATRIX__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"

typedef float Item;

typedef struct _vector_m {
    int* begin;
    int size;
    int allocated;
} VecM;

typedef struct _element_a { // _vector_a
    int column;
    Item value;
    int indexNext;
} ElementA;

typedef struct _vector_a {
    ElementA* begin;
    int size;
    int allocated;
} VecA;

void createVA(VecA* va); // Создание вектора А
void createVM(VecM* vm); // Создание вектора M

void deleteVA(VecA* va);
void deleteVM(VecM* vm);

void insertValueVecA(VecA* va, int column, Item value, int index);
void insertValueVecM(VecM* vm, int value);

void printVA(VecA* va);
void printVM(VecM* vm);

VecA copyFrom(VecA* va);

float findMaxElementSparceMatrix(VecA* va);
void divideSparceMatrixElem(VecA* va, Item maxElem);
#endif // __SPARCE_MATRIX__