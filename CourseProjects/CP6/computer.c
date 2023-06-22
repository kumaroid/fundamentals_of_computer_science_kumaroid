#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "computer.h"
#include "serialization.h"

void createFile(const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fclose(file);
    }
}

int addStud(const char* filename) {
    pc rec; // Переменная типа 'pc' для записи характеристик компа
    FILE* file = fopen(filename, "ab");
    if (!file) {
        printf("File not found\n");
        return -1;
    }
    memset(&rec, 0, sizeof(pc));
    printf("Enter a surname\n");
    scanf("%s", rec.surname);
    printf("Enter a number of processors\n");
    scanf("%d", &rec.num_of_proc);
    printf("Enter a type of processors\n");
    scanf("%s", rec.type_of_proc);
    printf("Enter a RAM size\n");
    scanf("%d", &rec.mem_size_ram);
    printf("Enter a type of controller\n");
    scanf("%s", rec.type_of_contr);
    printf("Enter a video memory size\n");
    scanf("%d", &rec.mem_size_video_proc);
    printf("Enter a type of disk\n");
    scanf("%s", rec.type_of_disk);
    printf("Enter a number of disks\n");
    scanf("%d", &rec.num_of_disk);
    printf("Enter a capacity of disk\n");
    scanf("%d", &rec.cap_of_disk);
    printf("Enter a number of integrated controllers\n");
    scanf("%d", &rec.num_of_intcontr);
    printf("Enter a number of peripheral devices\n");
    scanf("%d", &rec.num_of_dev);
    printf("Enter an OS\n");
    scanf("%s", rec.os);

    studentWriteBin(&rec, file);
    fclose(file);
    return 0;
}

int printTable(const char* filename) {
    FILE* file = fopen(filename, "rb");
    pc read;
    memset(&read, 0, sizeof(pc));
    if (!file) { // Если файл не найден
        return -1;
    } else {
        printf("Surname\t\tPNum\tPType\tRAM\tCType\tVMem\tDType\tDNum\tDCap\tICNum\tPDNum\tOS\n");
        while (studentReadBin(&read, file)) {
            printf("%s\t%d\t%s\t%d\t%s\t%d\t%s\t%d\t%d\t%d\t%d\t%s\n", read.surname, read.num_of_proc, read.type_of_proc, read.mem_size_ram, read.type_of_contr, read.mem_size_video_proc, read.type_of_disk, read.num_of_disk, read.cap_of_disk, read.num_of_intcontr, read.num_of_dev, read.os);
            memset(&read, 0, sizeof(pc));
        }
        fclose(file);
    }
}

int deleteFile(const char* filename) {
    if (remove(filename) != 0) {
        return -1;
    } else {
        return 0; // Удаление файла прошло успешно
    }
}

void deleteStudent(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("File not found\n");
        return;
    }
    printf("Enter student surname:\n");
    char surname[100];
    scanf("%s", surname);
    if (!file) {
        return;
    }  
    char tmp_name[100];
    FILE* tmp_file;
    int name_lenght = strlen(filename);
    strcpy(tmp_name, filename);
    tmp_name[name_lenght] = '_';
    tmp_name[name_lenght + 1] = '\0';
    tmp_file = fopen(tmp_name, "ab");
    if (!tmp_file) {
        printf("fopen failed, errno = %d\n", errno);
        return;
    }

    pc row;
    while (studentReadBin(&row, file)) {
        if (strcmp(row.surname, surname) != 0) {
            studentWriteBin(&row, tmp_file);
        }
        memset(&row, 0, sizeof(pc));
    }
    fclose(tmp_file);
    fclose(file);
    
    if (remove(filename) != 0) {
        printf("Failed to delete file\n");
        return;
    }

    if (rename(tmp_name, filename) != 0) {
        printf("Failed to rename temporary file\n");
        return;
    }
}


int func(int p, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return -1;
    }
    pc find, select;
    memset(&find, 0, sizeof(pc));
    int count = 0;
    
    printf("Enter minimal number of processors\n");
    scanf("%d", &select.num_of_proc);
    printf("Enter minimal size of RAM, GB\n");
    scanf("%d", &select.mem_size_ram);
    printf("Enter minimal size of video memory, GB\n");
    scanf("%d", &select.mem_size_video_proc);
    printf("Enter minimal number of disks\n");
    scanf("%d", &select.num_of_disk);
    printf("Enter minimal capacity of disk, GB\n");
    scanf("%d", &select.cap_of_disk);
    printf("Enter minimal number of integrated controllers\n");
    scanf("%d", &select.num_of_intcontr);
    printf("Enter necessary OS\n");
    scanf("%s", select.os);
    
    while (studentReadBin(&find, file)) {
        if ((find.num_of_proc < select.num_of_proc) || (find.mem_size_ram < select.mem_size_ram) || (find.mem_size_video_proc < select.mem_size_video_proc) || (find.num_of_disk < select.num_of_disk) || (find.cap_of_disk < select.cap_of_disk) || (find.num_of_intcontr < select.num_of_intcontr) || (!strcmp(find.os, select.os))) {
            count++;
        }
        memset(&find, 0, sizeof(pc));
    }
    
    fclose(file);

    if (count < p) {
        return -1;
    } else {
        file = fopen(filename, "rb");
        printf("\nList of students whose computers need to be upgraded:\n");
        while (studentReadBin(&find, file)) {
            if (!((find.num_of_proc >= select.num_of_proc) && (find.mem_size_ram >= select.mem_size_ram) && (find.mem_size_video_proc >= select.mem_size_video_proc) && (find.num_of_disk >= select.num_of_disk) && (find.cap_of_disk >= select.cap_of_disk) && (find.num_of_intcontr >= select.num_of_intcontr) && (!strcmp(find.os, select.os)))) {
                printf("\t%s\n", find.surname);
            }
            memset(&find, 0, sizeof(pc));
        }
        fclose(file);
    }

    return 0;
}