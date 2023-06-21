#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "tree.h"

intgetPriority(char c) { // Возвращение приоритета символа
switch (c) {
case '+': case '-': return 1;
case '*': case '/': return 2;
case '^': return 3;
    }
return 17;
}

Tree treeCreate(Token tokens[], intindexLeft, intindexRight) { // Функцияпостроениядерева
    Tree t = (Tree)malloc(sizeof(structtree_node));

if (indexLeft>indexRight) { // Если закончился проход по массиву токенов
return NULL;
    }

if (indexLeft == indexRight) { // Еслипоследнийтокен
t->node  = tokens[indexLeft];
t->left  = NULL;
t->right = NULL;
return t;
    }

int priority; // Переменнаяприоритета
intpriorityMin = getPriority('a'); // Задаемминимальныйприоритет
intbrackets = 0; // Счетчик скобок
intoperPos; // Позиция оператора

for (inti = indexLeft; i<= indexRight; ++i) { // Проходимсяпоскобкам
if ((tokens[i].type == BRACKET) && (tokens[i].data.isLeftBracket)) { // Еслиэтолеваяскобка
++brackets; // Прибавляем в счетчик
continue; // Заканчиваем итерацию
}

if ((tokens[i].type == BRACKET) && !(tokens[i].data.isLeftBracket)) { // Еслиэтоправаяскобка
            --brackets; // Отбавляем
continue;
        }
if (brackets > 0) { // Еслиужеоткрыты
continue;
        }
if (tokens[i].type == OPERATOR) { // Еслиэтооператор
priority = getPriority(tokens[i].data.operatorName); // Задаемприоритетомэтоттокен

if (priority<= priorityMin) { // Если приоритет меньше или равен минимальному
priorityMin = priority; // Присваиваем его
operPos = i; // Присваиваем новую позицию
}
        }
    }

    // Особыйслучай, новыйпотомок
if ((priorityMin == getPriority('a')) && (tokens[indexLeft].type == BRACKET) && (tokens[indexLeft].data.isLeftBracket) &&(tokens[indexRight].type  == BRACKET) && !(tokens[indexRight].data.isLeftBracket)) {
free(t); // Удаляемузел
returntreeCreate(tokens, indexLeft + 1, indexRight - 1);
    }

if (tokens[operPos].data.operatorName == '^') { // Еслиэтостепень
brackets = 0; // Зануляемскобки

for (inti = operPos; i>= indexLeft; --i) { // Проходимсяпоскобкамстепени
if ((tokens[i].type == BRACKET) && !(tokens[i].data.isLeftBracket)) { // Еслиправаяскобка
                ++brackets;
continue;
            }

if ((tokens[i].type == BRACKET) && (tokens[i].data.isLeftBracket)) { // Еслилеваяскобка
                --brackets;
continue;
            }

if (brackets > 0) { // Еслинесколько
continue;
            }

if (tokens[i].type == OPERATOR) { // Есливстретилсяоператор
priority = getPriority(tokens[i].data.operatorName); // Меняемприоритет

if (priority == 3) { // Если еще одна степень
operPos = i; // Задаем новую позицию оператора
                }
            }
        }
    }

    t->node  = tokens[operPos]; // Записываем в значение выражение
t->left  = treeCreate(tokens, indexLeft, operPos - 1); // Запускаемрекурсиювлевогопотомка
t->right = treeCreate(tokens, operPos + 1, indexRight); // Запускаемрекурсиювправогопотомка

if (t->right == NULL) {
exit(1);
    }

return t;
}

voidtreeDelete(Tree* t) { // Функцияудалениядерева
if ((*t) != NULL) { // Если указатель на дерево не пустой
treeDelete(&((*t)->left)); // Рекурсивный переход к левому узлу
treeDelete(&((*t)->right)); // Рекурсивный переход к правому узлу
    }
free(*t); // Удаляем узел
    *t = NULL; // Указатель пуст
}

voidtreeInfix(Tree t) { // Вывод инфиксного выржаения
if (t != NULL) {
if (t->left&& t->right) // Если существует и левое, и правое поддерево
printf("("); 

treeInfix(t->left); // Рекурсия перехода к левому узлу
tokenPrint(&(t->node)); // Выводим токен
treeInfix(t->right); // Рекурсия перехода к правому узлу

if (t->right && t->left)
printf(")");
    }
}

voidtreePrint(Tree t, size_t depth) {
if (t != NULL) {
for (inti = 0; i< depth; i++) {
printf("\t"); // Вывод табуляции с уходом в глубь дерева
        }
tokenPrint(&(t->node)); // Печатаем значения токена на этом узле дерева
printf("\n"); // Переносстроки
treePrint(t->left, depth + 1);
treePrint(t->right, depth + 1);
    }
}
