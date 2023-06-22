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