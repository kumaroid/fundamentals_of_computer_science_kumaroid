#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"

int isEmpty(VecA *va) {
    return va->size == 0;
}

void createVA(VecA* va) {
    va->allocated = 1;
    va->size = 0;
    va->begin = malloc(va->allocated * sizeof(ElementA));
}

void createVM(VecM* vm) {
    vm->allocated = 1;
    vm->size = 0;
    vm->begin = malloc(vm->allocated * sizeof(int));
}

void deleteVA(VecA* va) { // !!!ЗДЕСЬ ВОЗМОЖНА УТЕЧКА ПАМЯТИ!!!
    free(va->begin);
    va->allocated = 0;
    va->size = 0;
    va->begin = NULL;
}

void deleteVM(VecM* vm) {
    free(vm->begin);
    vm->allocated  = 0;
    vm->size = 0;
    vm->begin = NULL;
}

void insertValueVecA(VecA* va, int column, Item value, int index) {
    if (va->size + 1 >= va->allocated) {
        va->allocated *= 2;
        va->begin = realloc(va->begin, sizeof(ElementA) * va->allocated);
    }
    va->begin[va->size].column = column;
    va->begin[va->size].value = value;
    va->begin[va->size].indexNext = index;
    ++va->size;
}

void insertValueVecM(VecM* vm, int value) {
    if (vm->size + 1 >= vm->allocated) { // Проверка на необходимость выделения еще памяти
        vm->allocated *= 2;
        vm->begin = realloc(vm->begin, sizeof(int) * vm->allocated);
    }
    vm->begin[vm->size++] = value;
}

void printVA(VecA* va) {
    if (!isEmpty(&va)) {
        printf("Vector A = ");
        for (int i = 0; i < va->size; i++) {
            printf("(%d;", va->begin[i].column);
            printf("%.1f;", va->begin[i].value);
            printf("%d) ", va->begin[i].indexNext);
        }
        printf("\n");
    }
}

void printVM(VecM* vm) {
    printf("Vector M = ( ");
    for (int i = 0; i < vm->size; i++) {
        printf("%d ", vm->begin[i]);
    }
    printf(")\n");
}

VecA copyFrom(VecA* va) {
    VecA copyVa;
    createVA(&copyVa);
    for (int i = 0; i < va->size; i++) {
        insertValueVecA(&copyVa, va->begin[i].column, va->begin[i].value, va->begin[i].indexNext);
    }
    return copyVa;
}

Item findMaxElementSparceMatrix(VecA* va) {
    Item maxElem = 0.0; 
    for (int i = 0; i < va->size; i++) {
        if (maxElem < abs(va->begin[i].value)) {
            maxElem = abs(va->begin[i].value);
        }
    }
    return maxElem;
}

void divideSparceMatrixElem(VecA* va, Item maxElem) {
    for (int i = 0; i < va->size; i++) {
        va->begin[i].value /= maxElem;
    }
} 