# Отчёт по заданию №6 по курсовому проекту по циклу дисциплин «Информатика»

<b>Студент группы:</b> <ins>М80-108Б-22 Иванов Андрей Кириллович, № по списку: 9</ins>

<b>Контакты e-mail:</b> <ins>andr-ushka2@ya.ru</ins>

<b>Работа выполнена:</b> «28» <ins>марта</ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> </ins>

<b>Отчет сдан</b> «28» <ins>марта</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> </ins>

<b>Подпись преподавателя:</b> ___________

## 1. Тема

Обработка последовательной файловой структуры на языке Си

## 2. Цель работы

Разработать последовательную структуру данных для представления простейшей базы данных на
файлах в СП Си в соответствии с заданным вариантом.

## 3. Задание

Составить программу генерации внешнего
нетекстового файла заданной структуры, содержащего представительный набор записей.
Распечатать содержимое сгенерированного файла в виде таблицы и выполнить над ним заданное действие для
запроса `p` и распечатать результат.

Действие по выборке данных из файла оформить в виде отдельной программы с параметрами запроса,
вводимыми из стандартного входного текстового файла, или получаемыми из командной строки UNIX.
Второй способ задания параметров обязателен для работ, оцениваемых на хорошо и отлично. Параметры
задаются с помощью ключей `–f [name]` (имя обрабатываемого файла) или `–p [parameter]` (параметры конкретного варианта
задания). Получение параметров из командной строки производится с помощью стандартных библиотечных
функций `argс` и `argv`.

Cтруктуры данных и константы, совместно используемые программами, следует вынести в отдельный
заголовочный файл.

В процессе отладки и тестирования рекомендуется использовать команды обработки текстовых файлов
ОС UNIX и переадресацию ввода-вывода. Сгенерированные и отформатированные тестовые данные
необходимо заранее поместить в текстовые файлы и распечатывать при протоколировании. Рекомендуется
подобрать реальные или правдоподобные тестовые данные. Число наборов тестовых данных должно быть не
менее трёх. Имя файла с бинарными данными является обязательным параметром второй программы.

**Содержимое и структура файла:**

Сведения о вступительных экзаменах абитуриентов: фамилия, инициалы, пол, номер школы, наличие
медали, оценки в баллах и зачет/незачет по сочинению.

**Действие**

Найти абитуриентов-медалистов, не набравших проходной балл p.

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

Программа содержит два исполняемых файла: один переводит из текстового формата в бинарный, другой обрабатывает бинарный файл.

## 7. Сценарий выполнения работы:

Makefile:
```
CC = gcc
CFLAGS ?= -g -Wall -Wextra -std=c99 -w -lm -Wformat=2

all:
	$(CC) $(CFLAGS) serialization.c computer.c main.c -o main

main: main.o computer.o serialization.o
	${CC} -o main main.o computer.o converter.o serialization.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: computer.c computer.o converter.c converter.o serialization.c serialization.o
	${CC} ${CFLAGS} -c computer.c converter.c

converter:
	${CC} ${CFLAGS} computer.c converter.c serialization.c -o conv

#Use this command, and run: ./a.out [number_of_students], then give filename wich will record
generate:
	${CC} ${CFLAGS} computer.c serialization.c make_test.c -o gener

clean: 
	rm -rf *.bin *.txt *.o main
```

main.c:
```src:main.c
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
```

computer.h:
```src:computer.h
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

```

computer.c:
```src:computer.c
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

```

serialization.c
```src:serialization.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "computer.h"
#include "serialization.h"

int studentReadTxt(pc *s, FILE *in) {
    fscanf(in, "%s", s->surname);
    fscanf(in, "%d", &(s->num_of_proc));
    fscanf(in, "%s", s->type_of_proc);
    fscanf(in, "%d", &(s->mem_size_ram));
    fscanf(in, "%s", s->type_of_contr);
    fscanf(in, "%d", &(s->mem_size_video_proc));
    fscanf(in, "%s", s->type_of_disk);
    fscanf(in, "%d", &(s->num_of_disk));
    fscanf(in, "%d", &(s->cap_of_disk));
    fscanf(in, "%d", &(s->num_of_intcontr));
    fscanf(in, "%d", &(s->num_of_dev));
    fscanf(in, "%s", s->os);

    return !feof(in);
}

void studentWriteTxt(pc *s, FILE *out) {
    fprintf(out, "%s\t", s->surname);
    fprintf(out, "%d\t", s->num_of_proc);
    fprintf(out, "%s\t", s->type_of_proc);
    fprintf(out, "%d\t", s->mem_size_ram);
    fprintf(out, "%s\t", s->type_of_contr);
    fprintf(out, "%d\t", s->mem_size_video_proc);
    fprintf(out, "%s\t", s->type_of_disk);
    fprintf(out, "%d\t", s->num_of_disk);
    fprintf(out, "%d\t", s->cap_of_disk);
    fprintf(out, "%d\t", s->num_of_intcontr);
    fprintf(out, "%d\t", s->num_of_dev);
    fprintf(out, "%s\t", s->os);

    fprintf(out, "\n");
}

void writeStrBin(char *str, FILE *out) {
    int lenght = strlen(str);
    fwrite(&lenght, sizeof(int), 1, out);
    fwrite(str, sizeof(char), lenght, out);
}

void studentWriteBin(pc *s, FILE *out) {
    writeStrBin(s->surname, out);
    fwrite(&(s->num_of_proc), sizeof(int), 1, out);
    writeStrBin(s->type_of_proc, out);
    fwrite(&(s->mem_size_ram), sizeof(int), 1, out);
    writeStrBin(s->type_of_contr, out);
    fwrite(&(s->mem_size_video_proc), sizeof(int), 1, out);
    writeStrBin(s->type_of_disk, out);
    fwrite(&(s->num_of_disk), sizeof(int), 1, out);
    fwrite(&(s->cap_of_disk), sizeof(int), 1, out);
    fwrite(&(s->num_of_intcontr), sizeof(int), 1, out);
    fwrite(&(s->num_of_dev), sizeof(int), 1, out);
    writeStrBin(s->os, out);
}

void readStrBin(char *str, FILE *in) {
    int length;
    fread(&length, sizeof(int), 1, in);
    fread(str, sizeof(char), length, in);
}

int studentReadBin(pc *s, FILE *in) {
    readStrBin(s->surname, in);
    fread(&(s->num_of_proc), sizeof(int), 1, in);
    readStrBin(s->type_of_proc, in);
    fread(&(s->mem_size_ram), sizeof(int), 1, in);
    readStrBin(s->type_of_contr, in);
    fread(&(s->mem_size_video_proc), sizeof(int), 1, in);
    readStrBin(s->type_of_disk, in);
    fread(&(s->num_of_disk), sizeof(int), 1, in);
    fread(&(s->cap_of_disk), sizeof(int), 1, in);
    fread(&(s->num_of_intcontr), sizeof(int), 1, in);
    fread(&(s->num_of_dev), sizeof(int), 1, in);
    readStrBin(s->os, in);

    return !feof(in);
}

```

serialization.h
```src:serialization.h
#ifndef __SERIALIZATION_H__
#define __SERIALIZATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "computer.h"

int studentReadTxt(pc *s, FILE *in);
void studentWriteTxt(pc *s, FILE *out);
void writeStrBin(char *str, FILE *out);
void studentWriteBin(pc *s, FILE *out);
void readStrBin(char *str, FILE *in);
int studentReadBin(pc *s, FILE *in);

#endif // __SERIALIZATION_H__

```

converter.c
```src:converter.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "computer.h"
#include "serialization.h"

int main(int argc, char *argv[]) 
{   
    if (argc != 4) {
        printf("Usage:\n\t%s  FILE_FROM FILE_TO [ttb] (txtToBin) | [btt] (BinToTxt)\n", argv[0]);
        exit(0);
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (!in || !out) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    pc s;
    
    if (!strcmp(argv[3], "ttb")) {
        while(studentReadTxt(&s, in)) {
            studentWriteBin(&s, out);
            memset(&s, 0, sizeof(pc));
        }
    } else if (!strcmp(argv[3], "btt")) {
        while(studentReadBin(&s, in)) {
            studentWriteTxt(&s, out);
            memset(&s, 0, sizeof(pc));
        }
    } else {
        printf("Unknown command\n");
    }
    fclose(in);
    fclose(out);

    return 0;
}

```

make_test.c
```src:make_test.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "computer.h"
#include "serialization.h"

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("CHECK:\n\t %s FILE_OUT NUMBERS_OF_STUDENTS\n", argv[0]);
        exit(1);
    }	
	int p, k, s, g, h;
	FILE* file;
    file = fopen(argv[1], "r+");
    sscanf(argv[2], "%d", &p);
    for (int i = 0; i < p; ++i) {
    	pc ran;
		memset(&ran, 0, sizeof(pc)); // Проинициализурем нулями. (Строки => нулевыми байтами, числа => нулём)
    	k = rand() % 2;
    	s = rand() % 2;
    	g = rand() % 2;
    	h = rand() % 2;
    	file = fopen(argv[1], "a");
    	for (int i = 0; i < 10; ++i) {
    		ran.surname[i] = (char)(rand()%26 + 0x61);	
    	}
    	ran.num_of_proc = 2 + rand()%(12 - 2 + 1);
		if (k == 0) {
			
			strcpy(ran.type_of_proc, "x86");
		} else {
			strcpy(ran.type_of_proc, "x64");
		}
    	ran.mem_size_ram = 2 + rand()%(64 - 2 + 1);
		if (s == 0) {
			strcpy(ran.type_of_contr, "AGP");
		} else {
			strcpy(ran.type_of_contr, "PCI");
		}
    	ran.mem_size_video_proc = 2 + rand()%(3 - 2 + 1);

    	if (g == 0) {
			strcpy(ran.type_of_disk, "SSD");
    	} else {
			strcpy(ran.type_of_disk, "HDD");
    	}
    	ran.num_of_disk = 2 + rand()%(4 - 2 + 1);
    	ran.cap_of_disk = 128 + rand()%(1024);
    	ran.num_of_intcontr = 2 + rand()%(16 - 2 + 1);
    	ran.num_of_dev = 2 + rand()%(16 - 2 + 1);
    	if (h == 0) {
			strcpy(ran.os, "Ubuntu");
    	} else {
			strcpy(ran.os, "Windows");
    	}
		studentWriteBin(&ran, file);
        fclose(file);
    }
	return 0;
}

```

test.txt:
```
bbmqbhcdar	9	x64	51	AGP	2	HDD	2	212	3	13	Windows	
scdxrjmowf	11	x86	3	PCI	2	HDD	3	474	11	5	Ubuntu	
sarcbynecd	8	x64	34	PCI	2	SSD	3	417	2	16	Windows	
llnmpapqfw	4	x64	53	AGP	2	HDD	3	184	8	10	Ubuntu	
wnkuewhsqm	7	x86	58	AGP	3	HDD	3	810	15	4	Windows	
swmdkqtbxi	11	x64	42	PCI	3	SSD	2	277	14	13	Windows	
nsnfwzqfjm	12	x64	5	PCI	2	HDD	4	671	16	2	Windows	
```

## 8. Распечатка протокола

```

```

## 9. Замечания автора по существу работы

<a href = 'https://codeforces.com/contest/1821/submission/202878112'>def(Zaschita)</a>


## 10.Вывод работы:

После выполнения работы, были получены навыки обработки бинарных файлов в Си, а так же строгой обработки ползовательского ввода.

<b>Подпись студента:</b> ________________

