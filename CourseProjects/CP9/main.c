#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "vector_str.h"

void helpBoard() {
    printf("\tCHOOSE THE COMMAND TO USE PROGRAMM\n");
    printf("exit\texit from the program\n");
    printf("help\tcall helpboard\n");
    printf("sort\tstring merge sort\n");
    printf("findstr\tfind string by key\n");
    printf("print\tprint a table with a poem\n");
    printf("rewrtf\trewrite a file\n");
}

void rewriteFile(const char* filenamePoem, const char* filenameKey, Vector* table) {
    FILE* fileP = fopen(filenamePoem, "w");
    FILE* fileK = fopen(filenameKey, "w");

    if (fileP == NULL || fileK == NULL) {
        printf("Error! File was not open\n");
        return;
    }

    for (int i = 0; i < table->size; i++) {
        Row tmp = vecGetElem(table, i);
        fprintf(fileK, "%s\n", tmp.key);
        fprintf(fileP, "%s\n", tmp.string);
    }
    fclose(fileP);
    fclose(fileK);
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("\tUsage:\n%s FILE_KEY FILE_POEM\n", argv[0]);
        return 1;
    }

    FILE* fileKey = fopen(argv[1], "r");
    FILE* filePoem = fopen(argv[2], "r");

    if (filePoem == NULL && fileKey == NULL) {
        printf("Error! File was not open\n");
        return 1;
    }

    Vector* table = malloc(sizeof(Vector));
    vecCreate(table, 0);

    char strPoem[STRSIZE];
    char strKey[7];
    while (fgets(strPoem, sizeof(strPoem), filePoem) != NULL && fgets(strKey, sizeof(strKey), fileKey) != NULL) {
        char key[6];
        char string[STRSIZE];
        sscanf(strKey, "%5s ", key); // считываем значение ключа из файла strKey
        sscanf(strPoem, "%[^\n]", string);

        Row element;
        strcpy(element.key, key); // добавляем ключ к элементу
        strcpy(element.string, string); // добавляем строку стихотворения к элементу
        vecResize(table, table->size + 1);
        vecAddElem(table, table->size - 1, element); 
    }

    fclose(fileKey);
    fclose(filePoem);
 
    printf("The original table looks like this:\n");
    printf("|--------------------------------------------|\n");
    printf("|   KEY   | STRING                            \n");
    printf("|--------------------------------------------|\n");
    for (int i = 0; i < table->size; i++) {
        Row tmp = vecGetElem(table, i);
        printf("| %6s | %-41s \n", tmp.key, tmp.string);
    }
    printf("|--------------------------------------------|\n");

    char str[9];
    helpBoard();
    char find[6];
    while(1) {
        printf("\n");
        printf("Enter command: ");
        scanf("%8s", str);
        
        if (!strcmp(str, "exit")) {
            vecRemove(table);
            free(table);
            return 0;
        } else if (!strcmp(str, "help")) {
            helpBoard();
        } else if (!strcmp(str, "sort")) {
            mergeSort(table);
            printf("Table as sorted:\n");
            vecPrintTable(table);
        } else if (!strcmp(str, "findstr")) {
            if (vecCheckSortTableDescending(table)) {
                Vector* reverseTable = malloc(sizeof(Vector));
                vecCreate(reverseTable, table->size);
                vecReverse(table, reverseTable);
                printf("Enter key:\n");
                scanf("%5s", find);
                if (strcmp(vecBinarySearch(reverseTable, find).key, "")) {
                    printf("| %6s | %s \n", vecBinarySearch(reverseTable, find).key, vecBinarySearch(reverseTable, find).string);
                } else {
                    printf("Key was not finded\n");    
                }
                vecRemove(reverseTable);
                free(reverseTable);
            } else if (vecCheckSortTable(table) == 0) { // Если таблица не отсортирована
                printf("Sort the table first\n");
            } else {
                printf("Enter key:\n");
                scanf("%5s", find);

                if (strcmp(vecBinarySearch(table, find).key, "")) {
                    printf("| %6s | %s \n", vecBinarySearch(table, find).key, vecBinarySearch(table, find).string);
                } else {
                    printf("Key was not finded\n");
                }
            }
        } else if (!strcmp(str, "print")) {
            vecPrintTable(table);
        } else if (!strcmp(str, "rewrtf")) {
            rewriteFile(argv[1], argv[2], table);
            printf("File was rewrited\n");
        } else {
            printf("Unknown command\n");
        }

    }

    return 0;
}