#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedefenum {
    FINAL,
    INTEGER,
    FLOATING,
    OPERATOR,
    VARIABLE,
    BRACKET
} TokenType;

typedefstruct {
TokenType type;
union {
intvalueInt;
floatvalueFloat;
char  operatorName;
bool  isLeftBracket;
char  variableName;
    } data;
} Token;

voidtokenPrint(Token* t);
voidtokenNext(Token* t);

#endif
