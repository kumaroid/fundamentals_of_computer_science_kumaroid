# Отчёт по заданию №9 по курсовому проекту по циклу дисциплин «Информатика»

<b>Студент группы:</b> <ins>М80-108Б-22 Иванов Андрей Кириллович, № по списку: 9</ins>

<b>Контакты e-mail:</b> <ins>andr-ushka2@ya.ru</ins>

<b>Работа выполнена:</b> «28» <ins>марта</ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> </ins>

<b>Отчет сдан</b> «28» <ins>марта</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> </ins>

<b>Подпись преподавателя:</b> ___________

## 1. Тема
Сортировка и поиск

## 2. Цель работы
Составить программу на языке Си с использованием процедур и функций для сортировки таблицы заданным методом
и двоичного поиска по ключу в таблице.

## 3. Задание
Программа должна вводить значения элементов неупорядоченной таблицы и проверять работу процедуры
сортировки в трех случаях: (1) элементы таблицы с самого начала упорядочены; (2) элементы таблицы расставлены в
обратном порядке; (3) элементы таблицы не упорядочены.

После выполнения сортировки программа должна вводить ключи и для каждого из них выполнять поиск в
упорядоченной таблице с помощью процедуры двоичного поиска и печатать найденные элементы, если они присутствуют в
таблице.

Метод сортировки: Естественное слияние.

Структура таблицы: тип ключа - строковый (5 байт), хранение ключа и данных - раздельно, минимальное число элементов
таблицы - 15.

## 4. Оборудование:
<b>Процессор:</b> 11th Gen intel(R) Core(TM) i5-11400H @ 2.70GHz<br/>
<b>ОП:</b> 16 ГБ<br/>
<b>SSD:</b> 512 ГБ<br/>
<b>Адрес:</b> 192.168.56.1 <br/>
<b>Монитор:</b> 1920x1080<br/>
<b>Графика:</b> Nvidia GeForce RTX 3050 Ti Laptop GPU <br/>

## 5. Программное обеспечение:

<b>Операционная система семейства:</b> linux(ubuntu) версии 5.15.0-47-generic<br/>
<b>Интерпретатор команд:</b> bash версия 5.1.16<br/>
<b>Система программирования:</b> не использовалась версия —<br/>
<b>Редактор текстов:</b> emacs версия 25.2.2<br/>
<b>Утилиты операционной системы:</b> nano, ls, cd, touch, gcc <br/>
<b>Прикладные системы и программы:</b> GNU C compiler <br/>

## 6. Идея, метод, алгоритм решения:
Таблица хранится в текстовом файле, разделитель - ":". Таблица хранится в виде вектора пар ключ-значение.
Алгоритм сортировки естественным слиянием работает следующим образом: исходная последовательность разбивается на минимальное количество неубывающих отрезков. Далее каждая четная и
нечетная серии сливаются друг с другом, засчет чего формируется новая последовательность, минимальное количество неубывающих отрезков в которой стало вдвое меньше. Алгоритм
повторяется до тех пор, пока количество отрезков не станет равно единице. Для хранения разбиения последовательности на отрезки я использовал вектор указателей на таблицы.

## 7. Сценарий выполнения работы:

Makefile:
```
CC = gcc
CFLAGS ?= -g -Wall -Wextra -std=c99 -w -lm

all:
	$(CC) $(CFLAGS)  vector_str.c main.c -o main

main: main.o  vector_str.o 
	${CC} -o main main.o  vector_str.o 

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: vector_str.c vector_str.o  
	${CC} ${CFLAGS} -c  vector_str.c 

clean: 
	rm -rf *.o main

```

main.c:
```src:main.c
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
```

vector_str.h:
```src:vector_str.h
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
```

vector_str.c:
```src:vector_str.c
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

```

key.txt:
```src:key.txt
aaaaa
aaaab
aaaac
aaaad
aaaae
aaaaf
aaaag
aaaah
```

key_reverse.txt:
```src:key_reverse.txt
aaaah
aaaag
aaaaf
aaaae
aaaad
aaaac
aaaab
aaaaa

```

key_sort.txt
```
Я вас любил: любовь еще, быть может,
В душе моей угасла не совсем;
Но пусть она вас больше не тревожит;
Я не хочу печалить вас ничем.
Я вас любил безмолвно, безнадежно,
То робостью, то ревностью томим;
Я вас любил так искренно, так нежно,
Как дай вам бог любимой быть другим.
```

poem.txt
```
Я вас любил: любовь еще, быть может,
В душе моей угасла не совсем;
Но пусть она вас больше не тревожит;
Я не хочу печалить вас ничем.
Я вас любил безмолвно, безнадежно,
То робостью, то ревностью томим;
Я вас любил так искренно, так нежно,
Как дай вам бог любимой быть другим.
```

poem_sort.txt
```
aaaaa
aaaab
aaaac
aaaad
aaaae
aaaaf
aaaag
aaaah
```

poem_reverse.txt
```
Как дай вам бог любимой быть другим.
Я вас любил так искренно, так нежно,
То робостью, то ревностью томим;
Я вас любил безмолвно, безнадежно,
Я не хочу печалить вас ничем.
Но пусть она вас больше не тревожит;
В душе моей угасла не совсем;
Я вас любил: любовь еще, быть может,
```

## 8. Распечатка протокола

```

```

## 9. Замечания автора по существу работы

Замечаний нет.

## 10.Вывод работы:
Были получены базовые представления о внутренней работе баз данных и таблиц с информацией. Были изучены новый метод сортировки, алгоритм бинарного поиска. Получено более глубокое понимание механизмов выделения памяти в C.

<b>Подпись студента:</b> ________________

![til](https://github.com/kumaroid/fundamentals_of_computer_science_kumaroid/blob/main/CourseProjects/CP9/Dobra_i_pozitiva.gif)
