# Отчёт по курсовой работе №7 по курсу “Языки и методы программирования”

<b>Студент группы:</b> <ins>М80-108Б-22 Иванов Андрей Кириллович, № по списку: 9</ins>

<b>Контакты e-mail:</b> <ins>andr-ushka2@ya.ru</ins>

<b>Работа выполнена:</b> «28» <ins>марта</ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> </ins>

<b>Отчет сдан</b> «28» <ins>марта</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> </ins>

<b>Подпись преподавателя:</b> ___________


## 1. Тема
Разреженные матрицы
## 2. Цель работы
Составить и отладить программу на языке Си для обработки разреженных матриц с элементами целого типа.
## 3. Задание
- Вариант схемы размещения матрицы: 3 вектора
- Вариант физического представления: отображение на массив
- Вариант преобразования: Умножить разреженную матрицу на вектор-столбец и вычислить количество ненулевых элементов результата.

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

## 6. Идея, метод, алгоритм решения задачи (в формах: словесной, псевдокода, графической [блок-схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями)

Разреженная матрица была реализована согласно схеме представления. Была реализована структура вектора над динамическим массивом. Далее была реализована структура матрицы, хранящая в себе свои размеры и указатели на три вектора, согласно схеме представления.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию].

Makefile:
```
CC = gcc
CFLAGS ?= -g -Wall -Wextra -std=c99 -w -lm

all:
	$(CC) $(CFLAGS) sparce_matrix.c vector.c main.c -o main

main: main.o  vector.o sparce_matrix.o
	${CC} -o main main.o  vector.o sparce_matrix.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: vector.c vector.o sparce_matrix.c sparce_matrix.o
	${CC} ${CFLAGS} -c  vector.c sparce_matrix.c

clean: 
	rm -rf *.o main
```

main.c:
```src:main.c
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
```

vector.h
```src:vector.h
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

```

vector.c
```src:vector.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"
#include "sparce_matrix.h"

void createV(Vector* v) {
    v->allocated = 1;
    v->size = 0;
    v->begin = malloc(v->allocated * sizeof(int));
}

void deleteV(Vector *v) {
    free(v->begin);
    v->allocated = 0;
    v->size = 0;
    v->begin = NULL;
}

void pushBackV(Vector* v, int value) {
    if (v->size + 1 >= v->allocated) { // Проверка на необходимость выделения еще памяти
        v->allocated *= 2;
        v->begin = realloc(v->begin, sizeof(int) * v->allocated);
    }
    v->begin[v->size++] = value;
}

void printV(Vector* v) {
    for (int i = 0; i < v->size; i++) {
        printf("%d ", v->begin[i]);
    }
    printf("\n");
}  

```

sparce_matrix.h
```src:sparce_matrix.h
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

```

sparce_matrix.c
```src:sparce_matrix.c
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
```

in.txt
```src:in.txt
5 4
0.0 0.0 0.0 0.0 1.0
0.0 0.0 0.0 0.0 0.0
0.0 0.0 7.0 0.0 0.0
0.0 0.0 0.0 0.0 -9.0
-9.123 0.0 0.0 -9.13 0.0

```

out.txt
```src:out.txt
0.0 0.0 0.0 0.0 
0.1 0.0 0.0 0.0 
0.0 0.0 0.0 0.0 
0.8 0.0 0.0 0.0 
0.0 0.0 0.0 -1.0 
```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.
<b>Подпись преподавателя:</b> _____________________

## 8. Распечатка протокола

```
valgrind ./main in.txt
==20185== Memcheck, a memory error detector
==20185== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==20185== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==20185== Command: ./main in.txt
==20185== 
Vector A = (0;1.0;-1) (0;7.0;-1) (3;-9.0;-1) 
Vector M = ( -1 0 -1 1 2 )
==20185== 
==20185== HEAP SUMMARY:
==20185==     in use at exit: 0 bytes in 0 blocks
==20185==   total heap usage: 17 allocs, 17 frees, 14,956 bytes allocated
==20185== 
==20185== All heap blocks were freed -- no leaks are possible
==20185== 
==20185== Use --track-origins=yes to see where uninitialised values come from
==20185== For lists of detected and suppressed errors, rerun with: -s
==20185== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
aleksandr@aanedosekin:~/andrew/KP7$ cat out.txt 
0.0 0.0 0.0 0.0 
0.1 0.0 0.0 0.0 
0.0 0.0 0.0 0.0 
0.8 0.0 0.0 0.0 
0.0 0.0 0.0 -1.0
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 15.06.23 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы

[Zaschita](https://codeforces.com/contest/1842/submission/211138688)



## 11. Выводы
Были получены навыки написания эффективных программ для обработки разреженных матриц. Были отработаны навыки работы с файлами, динамическими структурами и указателями в Си. Были получены навыки устранения утечек памяти с помощью Valgrind.

<b>Подпись студента:</b> _________________
