#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum
{
    OUTSIDE,
    INSIDE_0,
    INSIDE_1,
    INSIDE_1_1,
    WRONG_WORD
} Conditions;


void fd_ispaniol(char fd)
{
    switch (fd)
    {
        case '2': 
            printf("veinti"); 
            return;
        case '3':  
            printf("treinta y "); 
            return;
        case '4':
            printf("cuarenta y "); 
            return;
        case '5': 
            printf("cincuenta y "); 
            return;
        case '6': 
            printf("sesenta y "); 
            return;
        case '7': 
            printf("setenta y "); 
            return;
    }
}

void sd_ispaniol(char sd)
{
    switch (sd)
    {
        case '1': 
            printf("uno ");
            return;
        case '2': 
            printf("dos "); 
            return;
        case '3': 
            printf("tres "); 
            return;
        case '4': 
            printf("cuatro ");
             return;
        case '5': 
            printf("cinco "); 
            return;
        case '6': 
            printf("seis "); 
            return;
        case '7': 
            printf("siete "); 
            return;
    }
}

void to_ispaniol(char fd, char sd)
{
    if (sd == '0')
    {
        switch (fd)
        {
            case '2': 
                printf("veinte ");
                return;
            case '3': 
                printf("treinta ");
                return;
            case '4': 
                printf("cuarenta ");
                return;
            case '5': 
                printf("cincuenta ");
                return;
            case '6': 
                printf("sesenta ");
                return;
            case '7': 
                printf("setenta ");
                return;
        }
    }else{
        fd_ispaniol(fd);
        sd_ispaniol(sd);
    }
}


bool is_8iric(char ch)
{
    return isdigit(ch) && ch != '8' && ch != '9';
}

void ispanio()
{
    int temp;
    int new;
    int k_0 = 0;
    bool minus = false;
    Conditions condition = OUTSIDE;
    for (int ch = getchar(); ch != EOF; ch = getchar())
    {
        switch (condition) 
        {
            case OUTSIDE:
                k_0 = 0;
                minus = false;
                if (ch == '0' || ch == '-')
                {
                    if (ch == '-')
                    {
                        minus = true;
                    }else 
                    {
                        k_0++;
                    }
                    condition = INSIDE_0;
                    continue;
                } else if  (is_8iric(ch) && ch != '1')
                {
                    temp = ch;
                    condition = INSIDE_1;
                    continue;
                }else if  (ch == '1')
                {
                    condition = INSIDE_1_1;
                    temp = ch;
                    continue;
                }else{
                    putchar(ch);
                    continue;
                }
            case WRONG_WORD:
                k_0 = 0;
                minus = false;
                while (ch != ' ' && ch != EOF)
                {
                    putchar(ch);
                    ch = getchar();
                }
                if (ch == EOF)
                {
                    putchar(ch);
                    break;
                }
                putchar(ch);
                condition = OUTSIDE;
            case INSIDE_0:
                if (ch == '0')
                {
                    k_0++;
                    continue;
                } else if  (is_8iric(ch) && ch != '1')
                {
                    temp = ch;
                    condition = INSIDE_1;
                    continue;
                }else if  (ch == '1')
                {
                    condition = INSIDE_1_1;
                    continue;
                }else if(ch == ' ')
                {
                    if (minus)
                    {
                        putchar('-');
                    }
                    for (int i = 0; i < k_0; i++){
                        putchar('0');
                    }
                    putchar(ch);
                    k_0 = 0;
                    minus = false;
                    condition = OUTSIDE;
                    continue;
                }else
                {
                    if (minus)
                    {
                        putchar('-');
                    }
                    for (int i = 0; i < k_0; i++){
                        putchar('0');
                    }
                    putchar(ch);
                    condition = WRONG_WORD;
                    continue;
                }
            case INSIDE_1:
                if (ch == ' ') 
                {
                    if (minus)
                    {
                        putchar('-');
                    }
                    for (int i = 0; i < k_0; i++){
                        putchar('0');
                    }
                    putchar(temp);
                    putchar(ch);
                    condition = OUTSIDE;
                    continue;
                }else if (ch == EOF)
                {
                    if (minus)
                    {
                        putchar('-');
                    }
                    for (int i = 0; i < k_0; i++){
                        putchar('0');
                    }
                    putchar(temp);
                    putchar(ch);
                    break;
                }
                new = getchar();
                if ((is_8iric(ch)) && (new == ' '|| new == EOF || new == '\n' || new == '\t' ))
                {
                    if (minus)
                    {
                        printf("menos ");
                    }
                    to_ispaniol(temp, ch);
                    condition = OUTSIDE;
                    continue;
                }else if(is_8iric(ch)){
                    if (minus)
                    {
                        putchar('-');
                    }
                    for (int i = 0; i < k_0; i++){
                        putchar('0');
                    }
                    putchar(temp);
                    putchar(ch);
                    putchar(new);
                    condition = WRONG_WORD;
                    continue;
                }else {
                    if (minus)
                    {
                        putchar('-');
                    }
                    for (int i = 0; i < k_0; i++){
                        putchar('0');
                    }
                    putchar(temp);
                    putchar(ch);
                    putchar(new);
                    condition = WRONG_WORD;
                    continue;
                }
            case INSIDE_1_1:
                new = getchar();
                if (ch == '7' && (new == ' ' || new == '\n' || new == '\t' || new == EOF))
                {
                    if (minus)
                    {
                        printf("menos ");
                    }
                    printf("diecisiete ");
                    condition = OUTSIDE;
                    continue;
                }else
                {
                    if (minus)
                    {
                        putchar('-');
                    }
                    for (int i = 0; i < k_0; i++){
                        putchar('0');
                    }
                    putchar('1');
                    putchar(ch);
                    putchar(new);
                    condition = WRONG_WORD;
                    continue;
                }
        }

    }

}

int main(){
    ispanio();
    return 0;
}



