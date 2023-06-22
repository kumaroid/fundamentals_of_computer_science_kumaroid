#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "computer.h"

void helpBoard() {
    printf("\n help \t\t for call helpboard\n create \t\t for create a new dataset\n addstud \t\t for adding new record\n print \t\t for printing dataset\n delf \t\t for delering dataset\n func \t\t for make a task sample\n delstud \t\t for delete student info in file\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("CHECK:\n\t %s FILE_IN\n", argv[0]);
        exit(1);
    }
    helpBoard();
    FILE* file;
    file = fopen(argv[1], "r+");

    char str[9];
    while(1) {
        printf("Enter command -> ");
        scanf("%8s", str);
        if (!strcmp(str, "addstud")) {
            addStud(argv[1]);
        } else if(!strcmp(str, "create")) {
            createFile(argv[1]);
        } else if (!strcmp(str, "print")) {
            printTable(argv[1]);
        } else if (!strcmp(str, "delf")) {
            deleteFile(argv[1]);
            printf("The file has been deleted, please restart the program with a new file\n");
            fclose(file);
            return 0;
        } else if (!strcmp(str, "func")) {
            int p;
            printf("Enter a numbers of student:\n");
            scanf("%d", &p);
            func(p, argv[1]);
        } else if(!strcmp(str, "delstud")) {
            deleteStudent(argv[1]);
        } else if(!strcmp(str, "help")) {
            helpBoard();
        } else {
            printf("Command not found\n");
            helpBoard();
        }
    }
    return 0;
}