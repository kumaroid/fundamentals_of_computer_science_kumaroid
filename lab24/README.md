# Отчёт по лабораторной работе №24 по курсу “Языки и методы программирования”

<b>Студент группы:</b> <ins>М80-108Б-22 Иванов Андрей Кириллович, № по списку: 9</ins>

<b>Контакты e-mail:</b> <ins>andr-ushka2@ya.ru</ins>

<b>Работа выполнена:</b> «28» <ins>марта</ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> </ins>

<b>Отчет сдан</b> «28» <ins>марта</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> </ins>

<b>Подпись преподавателя:</b> ___________

## 1. Тема
Динамические структуры данных. Обработка деревьев
## 2. Цель работы
Составить программу на Си выполнения заданных преобразований арифметическиз выражений с применением деревьев.
## 3. Задание (вариант № 37)
Подсчитать количество целочисленных констант в выражении.

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


## 6. Идея, метод, алгоритм решения задачи (в формах: словесной, псевдокода, графической [блок-схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями)

Выражение представляется в виде бинарного дерева, в каждом узле храним либо операнд, либо значение. Проходимся по дереву, смотрим на каждый узел, если в нем есть целочисленная константа, то увеличиваем счетчик.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию].

lexer.c
```src:lexer.c
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

```

transform.c
```src:transform.c
#include "tree.h"
#include "transform.h"
#include <math.h>

voidswapNode(Tree** a, Tree** b) {
    Tree* tmp = *a;
    *a = *b;
    *b = tmp;
}

int transform(Tree* t) {
staticint count = 0;
if (*t == NULL) {
return count;
    }
if ((*t)->node.type == INTEGER) {
        ++count;
    }
}

inttreeTransform(Tree* t) {
staticint count = 0;
if ((*t) == NULL) {
return count;
    }
treeTransform(&((*t)->left));
treeTransform(&((*t)->right));

count = transform(t);
}


```

tree.c
```src:tree.c
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


```

tree.h
```src:tree.h
#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include "lexer.h"

typedefstructtree_node *Tree;
structtree_node {
    Token node;
    Tree left;
    Tree right;
};

Tree treeCreate(Token tokens[], intidx_left, intidx_right);
voidtreeDelete(Tree* t);
voidtreeInfix(Tree t);
voidtreePrint(Tree t, size_t depth);

#endif


```


lexer.h
```src:lexer.h
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

```

transform.h
```src:transform.h
#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "tree.h"

inttreeTransform(Tree* t);

#endif // __TRANSFORM_

```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.
<b>Подпись преподавателя:</b> _____________________

## 8. Распечатка протокола

```
aleksandr@aanedosekin:~/andrew/lab24$ ./a.out
Please enter an expression. After finishing input, press EOF (ctrl+d)
Your expression:a+10+34+67+4.12+d

tree:
+
  +
    +
      +
        +
          a
          10
        34
      67
    4.12
  d

Tree's infix linearization:
(((((a+10)+34)+67)+4.12)+d)
3

aleksandr@aanedosekin:~/andrew/lab24$ valgrind ./a.out
==14084== Memcheck, a memory error detector
==14084== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==14084== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==14084== Command: ./a.out
==14084== 
Please enter an expression. After finishing input, press EOF (ctrl+d)
Your expression:a+b+25+g

tree:
+
  +
    +
      a
      b
    25
  g

Tree's infix linearization:
(((a+b)+25)+g)
3==14084== 
==14084== HEAP SUMMARY:
==14084==     in use at exit: 0 bytes in 0 blocks
==14084==   total heap usage: 9 allocs, 9 frees, 2,216 bytes allocated
==14084== 
==14084== All heap blocks were freed -- no leaks are possible
==14084== 
==14084== For lists of detected and suppressed errors, rerun with: -s
==14084== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 15.06.23 | 18:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы

[def(Zaschita)](https://codeforces.com/contest/1807/submission/201943354)

## 11. Выводы
Были детальнее изучены динамические структуры данных. Были получены основы синтаксического анализа и написания парсеров для текста. Было получено более глубокое понимание принципов работы компиляторов.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> _________________

