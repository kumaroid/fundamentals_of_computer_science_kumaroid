#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"
#include "sparce_matrix.h"

// m - КОЛИЧЕСТВО СТРОК, n - КОЛИЧЕСТВО СТОЛБЦОВ!!!
void AddedElementVectorA(VecA* va, FILE* file) {
    int m, n;
    fscanf(file, "%d", &m); // Строка
    fscanf(file, "%d", &n); // Столбец

    for (int i = 0; i < m; i++) {
        int nonzeroCount = 0; // Счетчик ненулевых элементов в текущей строке
        int lastInsertedIndex = -1; // Индекс последнего вставленного элемента

        for (int j = 0; j < n; j++) {
            Item num;
            fscanf(file, "%f", &num);

            if (num != 0) {
                int column = j;
                Item value = num;
                int index = -1;
                insertValueVecA(va, column, value, index);
                nonzeroCount++;

                if (lastInsertedIndex != -1) {
                    va->begin[lastInsertedIndex].indexNext = va->size - 1;
                }
                lastInsertedIndex = va->size - 1;
            }
        }

        if (nonzeroCount == 0 && lastInsertedIndex != -1) {
            va->begin[lastInsertedIndex].indexNext = -1;
        }
    }
    rewind(file); // Перемещение указателя чтения в начало файла
}

void AddedElementVectorM(VecM* vm, VecA* va, FILE* file) {
    int m, n;
    fscanf(file, "%d", &m); // Строка
    fscanf(file, "%d", &n); // Столбец
    VecA copyVa = copyFrom(va);
    for (int i = 0; i < m; i++) {
        int check = 0; // Сбросить check в ноль перед каждой строкой

        Item tmpNum = 0;
        for (int j = 0; j < n; j++) {
            Item num;
            fscanf(file, "%f", &num);
            if (num != 0 && check == 0) { // Добавить условие, чтобы сохранять только первый ненулевой элемент
                tmpNum = num;
                check = 1;
            }
        }

        if (check == 0) {
            insertValueVecM(vm, -1);
        } else {
            int foundIndex = -1;
            for (int k = 0; k < copyVa.size; k++) {
                if (tmpNum == copyVa.begin[k].value && copyVa.begin[k].column != -1) {
                    foundIndex = k;
                    copyVa.begin[k].column = -1;
                    break; // Добавить прерывание цикла, чтобы сохранять только первое совпадение
                }
            }
            if (foundIndex != -1) {
                insertValueVecM(vm, foundIndex);
            }
        }
    }
    rewind(file);
    deleteVA(&copyVa);
}

void printSparceMatrix(VecA* va, VecM* vm, FILE* fileIn) {
    int m, n;
    fscanf(fileIn, "%d", &m); // Строка
    fscanf(fileIn, "%d", &n); // Столбец
    FILE* fileOut = fopen("out.txt", "a");

    for (int i = 0; i < m; i++) {
        bool checkIndexM = false;
        int IndexM = -1;
        if (vm->begin[i] != -1) {
            checkIndexM = true;
            IndexM = vm->begin[i];
        }
        int count = 0;
        for (int k = IndexM; k != -1; k = va->begin[k].indexNext) {
            count++;
        }
        int nextIndex = IndexM;
        for (int j = 0; j < n; j++) {
            if (nextIndex != -1 && va->begin[nextIndex].column == j) {
                fprintf(fileOut, "%.1f ", va->begin[nextIndex].value);
                nextIndex = va->begin[nextIndex].indexNext;
            } else {
                fprintf(fileOut, "0.0 ");
            }
        }
        fprintf(fileOut, "\n");
    }
    fclose(fileOut);
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        printf("Usage:\n\t%s  FILE_FROM\n", argv[0]);
        exit(0);
    } else { 
        FILE* file = fopen(argv[1], "r");

        FILE* tmpFile = fopen(argv[1], "r");
        int firstChar = fgetc(tmpFile);
        if (firstChar == EOF) {
            printf("Check:\n\t%s  this file is empty\n", argv[1]); 
            fclose(tmpFile);
            fclose(file);
            return 0; 
        }

        VecA vectorA;
        VecM vectorM;

        createVA(&vectorA);
        createVM(&vectorM);

        AddedElementVectorA(&vectorA, file);
        AddedElementVectorM(&vectorM, &vectorA, file);
        
        printVA(&vectorA);
        printVM(&vectorM);

        Item findElem = findMaxElementSparceMatrix(&vectorA);
        divideSparceMatrixElem(&vectorA, findElem);
        printSparceMatrix(&vectorA,&vectorM, file);

        deleteVA(&vectorA);
        deleteVM(&vectorM);
        fclose(file);
        fclose(tmpFile);
    }

    return 0;
}