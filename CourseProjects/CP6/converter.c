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