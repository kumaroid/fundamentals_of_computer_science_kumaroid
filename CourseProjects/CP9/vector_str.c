#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "vector_str.h"

void vecCreate(Vector* vec, int size) {
    vec->size = size;
    vec->value = malloc(size * sizeof(Row));
    
    for (int i = 0; i < size; i++) {
        strcpy(vec->value[i].key, "");
        strcpy(vec->value[i].string, "");
    }
}

int vecIsEmpty(Vector* vec) {
    return vec->size == 0;
}

Row vecGetElem(Vector* vec, int index) {
    Row emptyRow;
    strcpy(emptyRow.key, "");
    strcpy(emptyRow.string, "");

    if (index >= 0 && index < vec->size) {
        return vec->value[index];
    } else {
        return emptyRow;
    }
}

void vecAddElem(Vector* vec, int index, Row value) {
    if (index >= 0 && index < vec->size) {
        vec->value[index] = value;
    }
}

void vecResize(Vector* vec, int size) {
    Row* newRow = realloc(vec->value, size * sizeof(Row));
    vec->value = newRow;
    vec->size = size;
}

void vecRemove(Vector* vec) {
    vec->size = 0;
    free(vec->value);
    vec->value = NULL;
}

void vecPrintTable(Vector* vec) {
    printf("|--------------------------------------------|\n");
    printf("|   KEY   | STRING                            \n");
    printf("|--------------------------------------------|\n");
    for (int i = 0; i < vec->size; i++) {
        Row tmp = vecGetElem(vec, i);
        printf("| %6s | %-41s \n", tmp.key, tmp.string);
    }
    printf("|--------------------------------------------|\n");    
}

int compareKeys(Row first, Row second) {
    return strcmp(first.key, second.key);
}

void mergeSort(Vector* vec) {
    int size = vec->size;
    Row* arr = vec->value;
    Row* tmp = malloc(size * sizeof(Row));
    int h;

    for (h = 1; h < size; h *= 2) {
        for (int left = 0; left + h < size; left += h * 2) {
            int mid = left + h;
            int right = mid + h;
            if (right > size) right = size;
            int i = left;
            int j = mid;
            int k = left;

            while (i < mid && j < right) {
                if (strcmp(arr[i].key, arr[j].key) <= 0) {
                    memcpy(&tmp[k++], &arr[i++], sizeof(Row));
                } else {
                    memcpy(&tmp[k++], &arr[j++], sizeof(Row));
                }
            }

            while (i < mid) {
                memcpy(&tmp[k++], &arr[i++], sizeof(Row));
            }

            while (j < right) {
                memcpy(&tmp[k++], &arr[j++], sizeof(Row));
            }

            for (int m = left; m < right; m++) {
                memcpy(&arr[m], &tmp[m], sizeof(Row));
            }
        }
    }

    free(tmp);
}

Row vecBinarySearch(Vector* table, char key[6]) { // Сделать 2ой вариант поиска
    int left = 0;
    int right = table->size - 1;
    int middle;
    Row empty = {"", ""};

    while (left <= right) {
        middle = (left + right) / 2;

        if (strcmp(key, table->value[middle].key) < 0) {
            right = middle - 1;
        } else if (strcmp(key, table->value[middle].key) > 0) {
            left = middle + 1;
        } else {
            return table->value[middle];
        }
    }

    return empty;
}

bool vecCheckSortTable(Vector* table) {
    for (int i = 0; i < table->size - 1; i++) {
        Row a = vecGetElem(table, i);
        Row b = vecGetElem(table, i + 1);

        if (compareKeys(a, b) > 0) { // Если нарушен порядок
            return false;
        }
    }

    return true;
}

bool vecCheckSortTableDescending(Vector* table) {
    for (int i = 0; i < table->size - 1; i++) {
        Row a = vecGetElem(table, i);
        Row b = vecGetElem(table, i + 1);

        if (compareKeys(a, b) < 0) {
            return false;
        }
    }
    
    return true;
}

void vecReverse(Vector* vecF, Vector* vecS) {
    int pos = 0;

    for (int i = vecF->size - 1; i >= 0; i--) {
        Row tmp = vecGetElem(vecF, i);
        vecAddElem(vecS, pos, tmp);
        pos++;
    }
}