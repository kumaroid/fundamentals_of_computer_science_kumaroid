#ifndef __VECTOR_STR_H__
#define __VECTOR_STR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STRSIZE 100
#define KEYSIZE 6

typedef struct _row {
    char key[KEYSIZE];
    char string[STRSIZE];
} Row;

typedef struct _vector {
    Row* value;
    int size;
} Vector;

void vecCreate(Vector* vec, int size);
int vecIsEmpty(Vector* vec);
Row vecGetElem(Vector* vec, int index);
void vecAddElem(Vector* vec, int index, Row value);
void vecResize(Vector* vec, int size);
void vecRemove(Vector* vec);
void vecPrintTable(Vector* vec);
int compareKeys(Row first, Row second);

void mergeSort(Vector* vec);

Row vecBinarySearch(Vector* table, char key[6]);

bool vecCheckSortTable(Vector* table);
bool vecCheckSortTableDescending(Vector* table);
void vecReverse(Vector* vecF, Vector* vecS);

#endif // __VECTOR_STR_H__