#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "lexer.h"

voidtokenNext(Token* t) { // Считываниетокенов
static bool canBeUnary = true;
char c;

do {
        c = fgetc(stdin);
    } while (isspace(c));

if (c == EOF) { // Если конец файла
t->type = FINAL;
    } else if (isalpha(c) || c == '_') { // Еслипеременная
t->type = VARIABLE;
t->data.variableName = c;
canBeUnary = false;
    } else if (isdigit(c)) { // Еслиэточисло
float result;
ungetc(c, stdin);
scanf("%f", &result);

if (result == (int) result) { // Еслицелочисленное
t->type = INTEGER;
t->data.valueInt = (int) result;
        } else { // Есливещественное
t->type = FLOATING;
t->data.valueFloat = result;
        }
canBeUnary = false;
    } else if (c == '(' || c == ')') { // Еслискобка
t->type = BRACKET;
t->data.isLeftBracket = (c == '('); // Присваиваемскобку
canBeUnary = t->data.isLeftBracket;
    } else if (canBeUnary&& (c == '-' || c == '+')) { // Еслиэтоунарныйоператор
int sign = (c == '+') ? +1 : -1; // Если это +, унарный знак = '+', если нет - '-'

do {
            c = fgetc(stdin);
        } while (isspace(c));

if (isdigit(c)) { // Если это число
ungetc(c, stdin);
tokenNext(t);
if (t->type == INTEGER) { // Еслицелочисленное
t->data.valueInt = sign * t->data.valueInt;
            } else { // Есливещественное
t->data.valueFloat = sign * t->data.valueFloat;
}
        } else{ // Если это оператор
ungetc(c, stdin);
t->type = OPERATOR;
t->data.operatorName = '-';
canBeUnary = true;
        }
    } else{ // Если это оператор
t->type = OPERATOR;
t->data.operatorName = c;
canBeUnary = true;
    }
}

voidtokenPrint(Token* t) { // Печатьтокенов

switch (t->type) {
case FINAL:
break;
case INTEGER:
printf("%d", t->data.valueInt);
break;
case FLOATING:
printf("%lg", t->data.valueFloat);
break;
case VARIABLE:
printf("%c", t->data.variableName); // %c - выводсимволов
break;
case OPERATOR:
printf("%c", t->data.operatorName);
break;
case BRACKET:
printf("%c", (t->data.isLeftBracket) ? '(' : ')');
break;
    }
}
