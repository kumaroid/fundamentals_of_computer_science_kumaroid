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