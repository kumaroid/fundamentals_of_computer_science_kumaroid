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