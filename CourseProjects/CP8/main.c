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