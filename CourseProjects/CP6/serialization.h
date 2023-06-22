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