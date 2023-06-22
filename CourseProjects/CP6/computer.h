#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LEN 50

typedef struct _comp 
{
    char surname[MAX_LEN]; // Фамилия студента
    int num_of_proc; // Значение процессора
    char type_of_proc[MAX_LEN]; // Тип процессора
    int mem_size_ram; // Размер оперативной памяти
    char type_of_contr[MAX_LEN]; // Тип плажки оперативы
    int mem_size_video_proc; // Объем видеопамяти
    char type_of_disk[MAX_LEN]; // Тип хранилища
    int num_of_disk; // Количество хранилищ
    int cap_of_disk; // Объем хранилища в Гб
    int num_of_intcontr; // Количество интерфейсных контроллеров
    int num_of_dev; // Количество устройств i/o
    char os[MAX_LEN];
} pc;

void createFile(const char* filename);
int addStud(const char* filename);
int printTable(const char* filename);
int deleteFile(const char* filename);
int func(int p, const char* filename);
void deleteStudent(const char* filename);

#endif //_COMPUTER_H_