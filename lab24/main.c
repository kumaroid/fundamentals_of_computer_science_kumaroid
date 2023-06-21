#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "lexer.h"
#include "tree.h"
#include "transform.h"

intmain()
{
Tokentokens[256]; // Массив переданных токенов
size_ttokensQty = 0; // Количество токенов в массиве

Tokentoken; // Объявления переменной каждого токена
printf("Please enter an expression. After finishing input, press EOF (ctrl+d)\nYourexpression:");
tokenNext(&token); // Заполнениямассиватокенов

while (token.type != FINAL) { // Пока не конец массива
tokens[tokensQty++] = token; 
tokenNext(&token);
    }

if (tokens[1].type == FINAL) {
printf("\nExpression is empty\n");
return 0;
    }

    Tree tree = treeCreate(tokens, 0, tokensQty - 1); // Созданиядеревавыражения

printf("\ntree:\n");
treePrint(tree, 0);

int a = treeTransform(&tree); // Производимпреобразования

printf("\nTree's infix linearization:\n");
treeInfix(tree);
printf("\n");
treeDelete(&tree);
printf("%d", a);


return 0;
}
