# Отчёт по лабораторным работам №25-26 по курсу “Языки и методы программирования”

<b>Студент группы:</b> <ins>М80-108Б-22 Иванов Андрей Кириллович, № по списку: 9</ins>

<b>Контакты e-mail:</b> <ins>andr-ushka2@ya.ru</ins>

<b>Работа выполнена:</b> «28» <ins>марта</ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> </ins>

<b>Отчет сдан</b> «28» <ins>марта</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> </ins>

<b>Подпись преподавателя:</b> ___________


## 1. Тема
Автоматизация сборки программ модульной структуры на языке Си с использованием утилиты make. Абстрактные типы данных. Рекурсия. Модульное программирование на языке Си.
## 2. Цель работы
Составить и отладить модуль определений и модуль реализации по заданной схее модуля определений для абстрактного (пользовательского) типа данных (стека, очереди, списка или дека, в зависимости от варианта задания). Составить программный модуль, сортирующий экземляр указанного абстрактного типа данных заданным методом, используя только операции, импортированные из модуля UUDT. Использовать утилиту make.
## 3. Задание (вариант № 15)
Тип данных: дек

Процедура: слияние двух деков, отсортированных по возрастанию, с сохранением порядка.

Метод: сортировка слиянием.

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

Сначала был реализована структура данных дек, описан базовый интерфейс взаимодействия со структурой. Дек был реализован над динамическим массивом.
Далее были написаны вспомогательные функции, например, для разворота дека.
Далее в отдельном файле были реализованы особая процедура, которая была дана в условии, и сортировка данным в условии методом.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию].

Makefile
```
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
OBJS = main.o deque.o

all: deque_merge_sort

deque_merge_sort: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o deque_merge_sort

main.o: main.c deque.h
	$(CC) $(CFLAGS) -c main.c

deque.o: deque.c deque.h
	$(CC) $(CFLAGS) -c deque.c

clean:
	rm -f deque_merge_sort $(OBJS)

```

main.c
```src:main.c
#include "deque.h"

int main() {
    Deque *deque = dequeCreate();
    dequePushBack(deque, 3);
    dequePushFront(deque, 7);
    dequePushBack(deque, 12);
    dequePushBack(deque, -11);
    dequePushBack(deque, 34);
    dequePushBack(deque, 5);
    dequePrint(deque);
    deque = dequeSort(deque);
    dequePrint(deque);
    dequeDestroy(deque);
}
```

deque.h
```src:deque.h
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size, capacity;
} Deque;

Deque *dequeCreate();
void dequeDestroy(Deque *deque);
void dequeResize(Deque *deque, size_t size);
size_t dequeSize(Deque *deque);

void dequePushBack(Deque *deque, int value);
int dequePopBack(Deque *deque);
void dequePushFront(Deque *deque, int value);
int dequePopFront(Deque *deque);
int dequeTop(Deque *deque);
int dequeFront(Deque *deque);
void dequePrint(Deque *deque);

// Освобождает указатель deque. Возвращает указатель на созданный новый дек.
Deque *dequeReverse(Deque *deque);
// Освобождает указатели deque1 и deque2. Оба дека должны быть отсортированы. 
// Возвращает указатель на созданный новый дек, содержащий результат слияния.
Deque *dequeMerge(Deque *deque1, Deque *deque2);
Deque *dequeSort(Deque *deque);

```

deque.c
```src:deque.c
#include "deque.h"
#include "assert.h"

Deque *dequeCreate() {
    Deque *deque = malloc(sizeof(Deque));
    deque->size = 0;
    deque->capacity = 1;
    deque->data = malloc(sizeof(int));
    return deque;
}

void dequeDestroy(Deque *deque) {
    if (deque != NULL) {
        free(deque->data);
        free(deque);
    }
}

void dequeResize(Deque *deque, size_t size) {
    assert(deque != NULL);
    size_t newCapacity = deque->capacity;
    while (newCapacity < size) {
        newCapacity *= 2;
    }
    deque->size = size;
    if (newCapacity != deque->capacity) {
        deque->capacity = newCapacity;
        deque->data = realloc(deque->data, sizeof(int) * deque->capacity);
    }
}

size_t dequeSize(Deque *deque) {
    assert(deque != NULL);
    return deque->size;
}

void dequePushBack(Deque *deque, int value) {
    assert(deque != NULL);
    dequeResize(deque, deque->size + 1);
    deque->data[deque->size - 1] = value;
}

int dequePopBack(Deque *deque) {
    assert(deque != NULL && deque->size != 0);
    dequeResize(deque, deque->size - 1);
    return deque->data[deque->size];
}

void dequePushFront(Deque *deque, int value) {
    assert(deque != NULL);
    dequeResize(deque, deque->size + 1);
    for (size_t i = deque->size; i > 0; i--) {
        deque->data[i] = deque->data[i - 1];
    }
    deque->data[0] = value;
}

int dequePopFront(Deque *deque) {
    assert(deque != NULL && deque->size != 0);
    dequeResize(deque, deque->size - 1);
    for (size_t i = 0; i < deque->size; i++) {
        deque->data[i] = deque->data[i + 1];
    }
}

int dequeTop(Deque *deque) {
    assert(deque != NULL && deque->size != 0);
    return deque->data[deque->size - 1];
}

int dequeFront(Deque *deque) {
    assert(deque != NULL && deque->size != 0);
    return deque->data[0];
}

void dequePrint(Deque *deque) {
    assert(deque != NULL);
    for (size_t i = 0; i < deque->size; i++) {
        printf("%d ", deque->data[i]);
    }
    putchar('\n');
}

Deque *dequeReverse(Deque *deque) {
    Deque *result = dequeCreate();
    while (dequeSize(deque) != 0) {
        dequePushBack(result, dequePopBack(deque));
    }
    dequeDestroy(deque);
    return result;
}

Deque *dequeMerge(Deque *deque1, Deque *deque2) {
    Deque *result = dequeCreate();
    while (dequeSize(deque1) != 0 || dequeSize(deque2) != 0) {
        if (dequeSize(deque1) == 0) {
            dequePushBack(result, dequePopBack(deque2));
        } else if (dequeSize(deque2) == 0) {
            dequePushBack(result, dequePopBack(deque1));
        } else {
            if (dequeTop(deque1) > dequeTop(deque2)) {
                dequePushBack(result, dequePopBack(deque1));
            } else {
                dequePushBack(result, dequePopBack(deque2));
            }
        }
    }
    dequeDestroy(deque1);
    dequeDestroy(deque2);
    return dequeReverse(result);
}

Deque *dequeSort(Deque *deque) {
    assert(deque != NULL);
    if (dequeSize(deque) <= 1) {
        return deque;
    }
    Deque *deque1 = dequeCreate(), *deque2 = dequeCreate();
    size_t startSize = dequeSize(deque);
    for (size_t i = 0; i < startSize / 2; i++) {
        dequePushBack(deque1, dequePopBack(deque));
    }
    while (dequeSize(deque) != 0) {
        dequePushBack(deque2, dequePopBack(deque));
    }
    deque1 = dequeSort(dequeReverse(deque1));
    deque2 = dequeSort(dequeReverse(deque2));
    return dequeMerge(deque1, deque2);
}


```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.
<b>Подпись преподавателя:</b> _____________________

## 8. Распечатка протокола

```
aleksandr@aanedosekin:~/andrew$ ls
deque.c  deque.h  main.c  Makefile
aleksandr@aanedosekin:~/andrew$ make
gcc -Wall -Wextra -Wpedantic -c main.c
gcc -Wall -Wextra -Wpedantic -c deque.c
gcc -Wall -Wextra -Wpedantic main.o deque.o -o deque_merge_sort
aleksandr@aanedosekin:~/andrew$ ls
deque.c  deque.h  deque_merge_sort  deque.o  main.c  main.o  Makefile
aleksandr@aanedosekin:~/andrew$ ./deque_merge_sort 
7 3 12 -11 34 5 
-11 3 5 7 12 34 
aleksandr@aanedosekin:~/andrew$
aleksandr@aanedosekin:~/andrew$ valgrind ./deque_merge_sort 
==11745== Memcheck, a memory error detector
==11745== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==11745== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==11745== Command: ./deque_merge_sort
==11745== 
==11745==ASan runtime does not come first in initial library list; you should either link runtime to your application or manually preload it with LD_PRELOAD.
==11745== 
==11745== Process terminating with default action of signal 11 (SIGSEGV)
==11745==  General Protection Fault
==11745==    at 0x52EFF42: __pthread_once_slow (pthread_once.c:114)
==11745==    by 0x53BEA52: __rpc_thread_variables (rpc_thread.c:59)
==11745==    by 0x5411D8C: free_mem (in /usr/lib/x86_64-linux-gnu/libc.so.6)
==11745==    by 0x54118C1: __libc_freeres (in /usr/lib/x86_64-linux-gnu/libc.so.6)
==11745==    by 0x483F1B2: _vgnU_freeres (in /usr/libexec/valgrind/vgpreload_core-amd64-linux.so)
==11745==    by 0x4A553DF: ???
==11745==    by 0x494B2B6: __sanitizer::Die() (sanitizer_termination.cpp:59)
==11745==    by 0x4921398: __asan::AsanCheckDynamicRTPrereqs() (asan_linux.cpp:181)
==11745==    by 0x492D544: __asan::AsanInitInternal() [clone .part.0] (asan_rtl.cpp:420)
==11745==    by 0x40065BD: _dl_init (dl-init.c:102)
==11745==    by 0x40202E9: ??? (in /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2)
==11745== 
==11745== HEAP SUMMARY:
==11745==     in use at exit: 0 bytes in 0 blocks
==11745==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==11745== 
==11745== All heap blocks were freed -- no leaks are possible
==11745== 
==11745== For lists of detected and suppressed errors, rerun with: -s
==11745== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 15.06.23 | 18:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы

[def(Zaschita)](https://codeforces.com/contest/1843/submission/210436475)

## 11. Выводы
Были изучены различные абстрактные типы данных. Был составлен программный модуль, сортирующий экземпляр указанного типа данных заданным методом на языке Си. Также была изучена утилита make. В результате выполнения работы, были приобретены навыки, которые будут полезны для выполнения других лабораторных работ и курсовых проектов.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> _________________
