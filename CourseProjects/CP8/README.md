# Отчёт по курсовой работе №8 по курсу “Языки и методы программирования”

<b>Студент группы:</b> <ins>М80-108Б-22 Иванов Андрей Кириллович, № по списку: 9</ins>

<b>Контакты e-mail:</b> <ins>andr-ushka2@ya.ru</ins>

<b>Работа выполнена:</b> «28» <ins>марта</ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> </ins>

<b>Отчет сдан</b> «28» <ins>марта</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> </ins>

<b>Подпись преподавателя:</b> ___________


## 1. Тема
Линейные списки
## 2. Цель работы
Составить и отладить программу на языке Си для обработки линейного списа заданной организации с отображением списка на динамические структуры, содержащего узлы типа int. Навигацию по списку следует реализовать с применением итераторов.
## 3. Задание
- Тип элемента спика: целый
- Вид списка: линейный однонаправленный
- Нестандартное действие: удалить из середины списка k элементов

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

Реализуется однонаправленный линейный список с отображением на динамические структуры. Структура узла списка хранит в себе значение в узле и указатель на следующий узел. В структуре списка хранятся указатель на первую вершину и на "последнюю". Во всех списках последняя вершина не является элементов самого списка, а лишь обозначает конец списка. Сделано это для
удобства реализации итераторов. Итераторы реализованы как структура, хранящая в себе указатель на список и вершину списка.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию].

Makefile
```
CC = gcc
CFLAGS ?= -g -Wall -Wextra -std=c99 -w -lm

all:
	$(CC) $(CFLAGS)  list.c main.c -o main

main: main.o  list.o 
	${CC} -o main main.o  list.o 

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: list.c list.o  
	${CC} ${CFLAGS} -c  list.c 

clean: 
	rm -rf *.o main

```

main.c
```src:main.c
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void helpBoard() {
    printf("\tHELP BOARD\n\n");
    printf("\tCommand programms:\n");
    printf("exit \tExit to porgramm\n");
    printf("help \tCall help board\n");
    printf("pushf \tPush front element\n");
    printf("insind \tInsert element by index\n");
    printf("popind \tPop element by index\n");
    printf("print \tPrint all elements in list\n");
    printf("dellist \tDelete all element in list\n");
    printf("vartask \tSearches for the entered element in the list, if the element is found - deletes the list\n");
    printf("\t ENUM COLORS:\n");
    printf("Red\nGreen\nBlue\nYellow\nBlack\n\n");
}


int main() 
{
    List list;
    listInit(&list);
    
    char str[9];
    helpBoard();
    while(1) {
        printf("\n");
        printf("Enter command: ");
        scanf("%8s", str);  
        if (!strcmp(str, "exit")) {
            listRemove(&list);
            exit (1);
        } else if (!strcmp(str, "help")) {
            helpBoard();
        } else if (!strcmp(str, "pushf")) {
            printf("Eneter a color to need push front: ");
            char stringColor[10];
            scanf("%s", stringColor);
            color clr = convertColor(stringColor);
            if (clr != -1) {
                listPushFront(&list, clr);
            }
        } else if (!strcmp(str, "insind")) {
            printf("Enter the index of the element to be added: ");
            int index;
            scanf("%d", &index);
            printf("Enter a color to add to the list: ");
            char stringColor[10];
            scanf("%s", stringColor);
            color clr = convertColor(stringColor);
            if (clr != -1) {
                listInsertIndex(&list, clr, index);
            }
        } else if (!strcmp(str, "popind")) {
            printf("Enter the index of the element to delete: ");
            int index;
            scanf("%d", &index);
            listPopIndex(&list, index);
        } else if (!strcmp(str, "print")) {
            listPrintout(&list);
        } else if (!strcmp(str, "dellist")) {
            listRemove(&list);
        } else if (!strcmp(str, "vartask")) {
            printf("Enter the color to be found: ");
            char colorString[10];
            scanf("%s", colorString);
            color clr = convertColor(colorString);
            listFoundElementDelete(&list, clr);
        } else {
            printf("Unknown command\n");
        }
    }
    return 0;
}
```

list.h
```src:list.h
#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    Red,
    Green,
    Blue,
    Yellow,
    Black
} color;

typedef struct _list_node {
    struct _list_node* next;
    color value;
} List_node;

typedef struct _list {
    List_node* front;
    size_t size;
} List;

void listInit(List* list);
int listIsEmpty(List* list);

color convertColor(char* str);
char* convertEnum(color clr);

void listPushFront(List* list, color clr);
void listInsertIndex(List* list, color clr, int index);
void listPopIndex(List* list, int index);

void listPrintout(List* list);
void listRemove(List* list);

void listFoundElementDelete(List* list, color foundElement);

#endif // __LIST_H__

```

list.c
```src:list.c
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void listInit(List* list) {
    list->front = NULL;
    list->size = 0;
}

int listIsEmpty(List* list) { // Возвращает 1, если пустой
    return list->size == 0;
}

color convertColor(char* str) {
    if ((!strcmp(str, "Red")) || (!strcmp(str, "red"))) {
        return Red;
    } else if ((!strcmp(str, "Green")) || (!strcmp(str, "green"))) {
        return Green;
    } else if ((!strcmp(str, "Blue")) || (!strcmp(str, "blue"))) {
        return Blue;
    } else if ((!strcmp(str, "Yellow")) || (!strcmp(str, "yellow"))) {
        return Yellow;
    } else if ((!strcmp(str, "Black")) || (!strcmp(str, "black"))) {
        return Black;
    } else {
        printf("This color is not in the enum list. Please enter a valid color.\n");
        return -1;  // Возвращаем недопустимое значение, чтобы обозначить ошибку
    }
}

char* convertEnum(color clr) {
    switch (clr)
    {
    case 0:
        return "Red";
        break;
    case 1:
        return "Green";
        break;
    case 2:
        return "Blue";
        break;
    case 3:
        return "Yellow";
        break;
    case 4:
        return "Black";
    }
}

void listPushFront(List* list, color clr) {
    List_node* listNode = malloc(sizeof(List_node));
    listNode->next = NULL;
    listNode->value = clr;

    if (list->size == 0) {
        list->front = listNode;
    } else {
        listNode->next = list->front;
        list->front = listNode;
    }
    list->size++;
}

void listInsertIndex(List* list, color clr, int index) {
    if (index > list->size || index < 0) {
        printf("\tOut of bounds list\n");
        return;
    }
    
    List_node* listNode = malloc(sizeof(List_node));
    listNode->value = clr;

    if (index == 0) {
        listNode->next = list->front;
        list->front = listNode;
    } else {
        List_node* tmp = list->front;
        for (int i = 0; i < index - 1; i++) {
            tmp = tmp->next;
        }
        listNode->next = tmp->next;
        tmp->next = listNode;
    }
    list->size++;
}

void listPopIndex(List* list, int index) {
    if (index >= list->size || index < 0) {
        printf("\tOut of bounds list\n");
        return;
    }

    if (listIsEmpty(list)) {
        printf("\tList is empty\n");
        return;
    }

    List_node* tmp = list->front; // Временная переменная
    List_node* prev = NULL; // Предидущая переменная

    if (index == 0) {
        list->front = tmp->next;
    } else {
        for (int i = 0; i < index; i++) {
            prev = tmp;
            tmp = tmp->next;
        }    
        prev->next = tmp->next;
    }

    char* res = convertEnum(tmp->value); 
    printf("\tRemoved element: %s\n", res);
    free(tmp);
    if (prev != NULL) {
        free(prev);
    }

    list->size--;
}

void listPrintout(List* list) {
    if (listIsEmpty(list)) {
        printf("\tList is empty\n");
        return;
    }

    List_node* tmp = list->front;

    printf("\tList:\n");
    for (int i = 0; i < list->size; i++) {
        char* res = convertEnum(tmp->value);
        printf("%s\t", res);
        tmp = tmp->next;
    }
    free(tmp);
    printf("\n");
}

void listRemove(List* list) {
    if (listIsEmpty(list)) {
        printf("\tList is empty\n");
        return;
    }

    List_node* tmp = list->front;
    for (int i = 0; i < list->size; i++) {
        List_node* next = tmp->next;
        free(tmp);
        tmp = next; 
    }
    list->front = NULL;
    list->size = 0;
}

void listFoundElementDelete(List* list, color foundElement) {
    if (listIsEmpty(list)) {
        printf("\tList is empty\n");
        return;
    }
    
    List_node* tmp = list->front;

    while (tmp != NULL) {
        if (tmp->value == foundElement) {
            listRemove(list);
            printf("\tElement was finded! List was deleted\n");
            return;
        } 
        tmp = tmp->next;
    }
    printf("\tElement was not finded!\n");
}
```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.
<b>Подпись преподавателя:</b> _____________________

## 8. Распечатка протокола

```

```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 16.05.23 | 1:30 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы


## 11. Выводы
Была составлена программа на языке Си для обработки линейного списка заданной организации с отображением на динамические структуры и написана процедура для выполнения нестандартного действия по номеру варианта. Были получены навыки написания итераторов для структур данных, изучен принцип их работы. Были приобретены навыки, которые будут полезны для выполнения других лабораторных работ и курсовых проектов.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> _________________

