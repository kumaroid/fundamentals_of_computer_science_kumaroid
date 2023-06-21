# Отчёт по лабораторной работе №24 по курсу “Языки и методы программирования”

<b>Студент группы:</b> <ins>М80-108Б-22 Рамалданов Рустамхан Ражудинович, № по списку: 15</ins>

<b>Контакты e-mail:</b> <ins>mrpepelulka@gmail.com</ins>

<b>Работа выполнена:</b> «28» <ins>марта</ins> <ins>2023</ins> г.

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Входной контроль знаний с оценкой:</b> <ins> </ins>

<b>Отчет сдан</b> «28» <ins>марта</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins> </ins>

<b>Подпись преподавателя:</b> ___________

## 1. Тема
Динамические структуры данных. Обработка деревьев
## 2. Цель работы
Составить программу на Си выполнения заданных преобразований арифметическиз выражений с применением деревьев.
## 3. Задание (вариант № 15)
Убрать из выражений все сомножители, равные единице.

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
<b>Местонахождение и имена файлов программ и данных на домашнем компьютере:</b> /home/pepelulka<br/>

## 6. Идея, метод, алгоритм решения задачи (в формах: словесной, псевдокода, графической [блок-схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями)

Выражение представляется в виде бинарного дерева, вершины-листы которого представляют переменные или числовые значения, а вершины, не являющиеся листами хранят в себе операцию, выполняемую над выражениями в поддеревьях.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию].

main.c
```src:main.c
#include <stdio.h>

#include "tree.h"

void solve() {
    Tree *tree;
    printf("Введите выражение в инфиксной записи:\n");

    parseFromStdin(&tree);

    printf("Дерево выражения:\n");
    treePrint(tree);
    printf("\n");
    treeRemoveMultOne(tree);
    printf("Преобразованное выражение:\n");
    treeConvertToStdout(tree);
    printf("\nДерево преобразованного выражения:\n");
    treePrint(tree);
    treeDestroy(tree);
}

int main() {
    solve();
    return 0;
}
```

tree_print.h
``` src:tree_print.h
#pragma once

#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// ================
// Tree print
// ================

#define MAX_STRING_LENGTH 200

typedef struct _TextChunkNode {
    char *str;
    struct _TextChunkNode *next;
} TextChunkNode;

// Представление для прямоугольного куска текста. Хранит в себе односвязный список строк.
typedef struct {
    int rootIndex;
    int rowCount;
    int columnCount;
    TextChunkNode *first, *last;
} TextChunk;

// === String functions ===

char* intToString(int val, int base);

char *stringGenerate(char c, int n);

void stringConcatenate(char *str1, char *str2);

char *stringGenerateCell(char *str);

// ========================\ String functions

// === TextChunk interface ===

TextChunkNode *TextChunkNodeCreate();

TextChunk *textChunkCreate();

// Result in chunk1
void textChunkAdd(TextChunk *chunk1, TextChunk *chunk2);

// Result in chunk1
void textChunkConcatenate(TextChunk *chunk1, TextChunk *chunk2);

TextChunk *textChunkGenerateBlank(int n, int m);

TextChunkNode *textChunkGet(TextChunk *chunk, int index);

void textChunkPush(TextChunk *chunk, char *str);

void textChunkComplement(TextChunk *chunk, int n);

void textChunkEven(TextChunk *chunk1, TextChunk *chunk2);

void textChunkPrint(TextChunk *chunk);

void textChunkNodeDestroy(TextChunkNode *node);

void textChunkDestroy(TextChunk *chunk);

// ===========================\ TextChunk interface

#define SUBTREE_SPACING 1 // Must be odd
#define CELL_LENGTH 7 // Must be odd

TextChunk *treeGenerateTextChunkForSubtree(void *node,
                                           char *(*valueAccessor)(void*),
                                           void *(*leftChildAccessor)(void*),
                                           void *(*rightChildAccessor)(void*));

// valueAccessor must return unsafe string.
void treePrintUniversal(void *node,
                        char *(*valueAccessor)(void*),
                        void *(*leftChildAccessor)(void*),
                        void *(*rightChildAccessor)(void*));

```

tree_print.c
```src:tree_print.c
#include "tree_print.h"

// ================
// Tree print
// ================

// === String functions ===

char* intToString(int val, int base) {
	static char buf[32] = {0};
    if (val == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}

// Returns unsafe string
char *stringGenerate(char c, int n) {
    char *result = malloc(sizeof(char) * (n + 1));
    if (n <= 0) {
        result[0] = '\0';
        return result;
    }
    for (int i = 0; i < n; i++) {
        result[i] = c;
    }
    result[n] = '\0';
    return result;
}

void stringConcatenate(char *str1, char *str2) {
    int ptr1 = 0, ptr2 = 0;
    while (str1[ptr1] != '\0') ptr1++;
    while (str2[ptr2] != '\0') {
        str1[ptr1] = str2[ptr2];
        ptr1++; ptr2++;
    }
    str1[ptr1] = '\0';
}

// Returns unsafe string
char *stringGenerateCell(char *str) {
    char *result = malloc(sizeof(char) * (CELL_LENGTH + 1));
    char curResult[20];
    curResult[0] = '\0';
    result[0] = '\0';
    stringConcatenate(curResult, str);
    int numberLength = strlen(curResult);
    int diff = CELL_LENGTH - numberLength;
    assert(diff >= 0);

    // Helping strings
    char *s1 = stringGenerate(' ', diff / 2);
    char *s2 = stringGenerate(' ', diff / 2 + 1);
    //

    if (diff % 2 == 0) {
        stringConcatenate(result, s1);
        stringConcatenate(result, curResult);
        stringConcatenate(result, s1);
    } else {
        stringConcatenate(result, s1);
        stringConcatenate(result, curResult);
        stringConcatenate(result, s2);
    }
    free(s1); free(s2);
    return result;
}

// ========================\ String functions

// === TextChunk interface ===

TextChunkNode *TextChunkNodeCreate() {
    TextChunkNode *node = malloc(sizeof(TextChunkNode));
    node->str = malloc(sizeof(char) * MAX_STRING_LENGTH);
    node->str[0] = '\0';
    node->next = NULL;
    return node;
}


TextChunk *textChunkCreate() {
    TextChunk *chunk = malloc(sizeof(TextChunk));
    chunk->rowCount = 0;
    chunk->columnCount = 0;
    chunk->first = NULL;
    chunk->last = NULL;
    return chunk;
}

void textChunkAdd(TextChunk *chunk1, TextChunk *chunk2) {
    assert(chunk1 != NULL && chunk2 != NULL);
    assert(chunk1->rowCount == chunk2->rowCount);
    if (chunk1->rowCount == 0) return;
    TextChunkNode *node1 = chunk1->first, *node2 = chunk2->first;
    while (node1 != NULL) {
        stringConcatenate(node1->str, node2->str);

        node1 = node1->next; node2 = node2->next;
    }
    chunk1->columnCount += chunk2->columnCount;
}

void textChunkConcatenate(TextChunk *chunk1, TextChunk *chunk2) {
    assert(chunk1 != NULL && chunk2 != NULL);
    if (chunk1->rowCount == 0) {
        chunk1->first = chunk2->first;
        chunk1->last = chunk2->last;
    } else {
        chunk1->last->next = chunk2->first;
        if (chunk2->last != NULL) chunk1->last = chunk2->last;
    }
    chunk1->rowCount += chunk2->rowCount;
}

TextChunk *textChunkGenerateBlank(int n, int m) {
    TextChunk *result = textChunkCreate();
    char *sm = stringGenerate(' ', m);
    for (int i = 0;i < n;i++) {
        textChunkPush(result, sm);
    }
    free(sm);
    return result;
}

TextChunkNode *textChunkGet(TextChunk *chunk, int index) {
    assert(index < chunk->rowCount);
    TextChunkNode *node = chunk->first;
    while (index--) node = node->next;
    return node;
}

void textChunkPush(TextChunk *chunk, char *str) {
    assert(chunk != NULL);
    TextChunkNode *node = TextChunkNodeCreate();
    stringConcatenate(node->str, str);
    if (chunk->rowCount == 0) {
        chunk->first = node;
        chunk->last = node;
        chunk->rowCount = 1;
        chunk->columnCount = strlen(str);
    } else {
        assert((int)strlen(str) == chunk->columnCount);
        chunk->last->next = node;
        chunk->last = node;
        chunk->rowCount++;
    }
}

void textChunkComplement(TextChunk *chunk, int n) {
    assert(chunk != NULL);
    if (chunk->rowCount < n) {
        TextChunk *blank = textChunkGenerateBlank(n - chunk->rowCount, chunk->columnCount);
        textChunkConcatenate(chunk, blank);
        free(blank);
    }
}

void textChunkEven(TextChunk *chunk1, TextChunk *chunk2) {
    textChunkComplement(chunk1, chunk2->rowCount);
    textChunkComplement(chunk2, chunk1->rowCount);
}

void textChunkPrint(TextChunk *chunk) {
    assert(chunk != NULL);
    TextChunkNode *node = chunk->first;
    while (node != NULL) {
        printf("%s\n", node->str);
        node = node->next;
    }
    printf("\n");
}

void textChunkNodeDestroy(TextChunkNode *node) {
    assert(node != NULL);
    free(node->str);
    free(node);
}

void textChunkDestroy(TextChunk *chunk) {
    assert(chunk != NULL);
    if (chunk->first == NULL) {
        free(chunk);
        return;
    }
    TextChunkNode *node, *next;
    node = chunk->first;
    while (node != NULL) {
        next = node->next;
        textChunkNodeDestroy(node);
        node = next;
    }
    free(chunk);
}

// =========================== \TextChunk interface

TextChunk *treeGenerateTextChunkForSubtree(void *node,
                                           char *(*valueAccessor)(void*),
                                           void *(*leftChildAccessor)(void*),
                                           void *(*rightChildAccessor)(void*)) {
    assert(node != NULL);
    char *value = valueAccessor(node);
    if (leftChildAccessor(node) == NULL && rightChildAccessor(node) == NULL) {
        TextChunk *chunk = textChunkCreate();
        char *cellStr = stringGenerateCell(value);
        chunk->rootIndex = strlen(cellStr) / 2;
        textChunkPush(chunk, cellStr);
        free(cellStr); free(value);
        return chunk;
    } else if (rightChildAccessor(node) == NULL) {
        TextChunk *lChunk = treeGenerateTextChunkForSubtree(leftChildAccessor(node),
                                                            valueAccessor,
                                                            leftChildAccessor,
                                                            rightChildAccessor);
        TextChunk *spaceChunk = textChunkGenerateBlank(lChunk->rowCount, SUBTREE_SPACING);
        TextChunk *rChunk = textChunkGenerateBlank(lChunk->rowCount, lChunk->columnCount);

        int subtreeWidth = lChunk->columnCount;
        int spaceWidth = SUBTREE_SPACING;
        int allWidth = 2 * subtreeWidth + spaceWidth;

        textChunkAdd(lChunk, spaceChunk);
        textChunkAdd(lChunk, rChunk);

        textChunkDestroy(spaceChunk);
        textChunkDestroy(rChunk);

        char *str1 = malloc(sizeof(char) * (allWidth + 1));
        char *str2 = malloc(sizeof(char) * (allWidth + 1));
        str1[0] = '\0'; str2[0] = '\0';
        // stringConcatenate(str2, s5);
        // stringConcatenate(str2, "|");
        // stringConcatenate(str2, s6);

        // Helping
        char *s1 = stringGenerate(' ', (allWidth - CELL_LENGTH) / 2);
        char *s2 = stringGenerateCell(value);
        char *s3 = stringGenerate(' ', subtreeWidth / 2);
        char *s4 = stringGenerate('-', subtreeWidth / 2);
        char *s5 = stringGenerate(' ', spaceWidth / 2);
        char *s6 = stringGenerate(' ', subtreeWidth + (spaceWidth / 2));
        //

        // str1
        stringConcatenate(str1, s1);
        stringConcatenate(str1, s2);
        stringConcatenate(str1, s1);

        // str2
        stringConcatenate(str2, s3);
        stringConcatenate(str2, "|");
        stringConcatenate(str2, s4);
        stringConcatenate(str2, s5);
        stringConcatenate(str2, "+");
        stringConcatenate(str2, s6);

        int rootIndex = strlen(s3) + 1 + strlen(s4) + strlen(s5);

        free(s1); free(s2); free(s3); free(s4); free(s5); free(s6);

        TextChunk *header = textChunkCreate();
        textChunkPush(header, str1);
        textChunkPush(header, str2);

        textChunkConcatenate(header, lChunk); // lChunk is alive !!!

        header->rootIndex = rootIndex;
        free(lChunk);
        free(str1); free(str2); free(value);
        return header;
    } else if (leftChildAccessor(node) == NULL) {
        TextChunk *rChunk = treeGenerateTextChunkForSubtree(rightChildAccessor(node),
                                                            valueAccessor,
                                                            leftChildAccessor,
                                                            rightChildAccessor);
        TextChunk *lChunk = textChunkGenerateBlank(rChunk->rowCount, rChunk->columnCount);
        TextChunk *spaceChunk = textChunkGenerateBlank(rChunk->rowCount, SUBTREE_SPACING);

        int subtreeWidth = rChunk->columnCount;
        int spaceWidth = SUBTREE_SPACING;
        int allWidth = 2 * subtreeWidth + spaceWidth;

        textChunkAdd(lChunk, spaceChunk);
        textChunkAdd(lChunk, rChunk);

        textChunkDestroy(spaceChunk);
        textChunkDestroy(rChunk);

        char *str1 = malloc(sizeof(char) * (allWidth + 1));
        char *str2 = malloc(sizeof(char) * (allWidth + 1));
        str1[0] = '\0'; str2[0] = '\0';

        // Helping
        char *s1 = stringGenerate(' ', (allWidth - CELL_LENGTH) / 2);
        char *s2 = stringGenerateCell(value);
        char *s3 = stringGenerate(' ', subtreeWidth / 2);
        char *s5 = stringGenerate('-', spaceWidth / 2 + subtreeWidth / 2);
        char *s6 = stringGenerate(' ', subtreeWidth + (spaceWidth / 2));
        //

        // str1
        stringConcatenate(str1, s1);
        stringConcatenate(str1, s2);
        stringConcatenate(str1, s1);

        // str2
        stringConcatenate(str2, s6);
        stringConcatenate(str2, "+");
        stringConcatenate(str2, s5);
        stringConcatenate(str2, "|");
        stringConcatenate(str2, s3);

        int rootIndex = strlen(s6);

        free(s1); free(s2); free(s3); free(s5); free(s6);

        TextChunk *header = textChunkCreate();
        textChunkPush(header, str1);
        textChunkPush(header, str2);

        textChunkConcatenate(header, lChunk); // lChunk is alive!!!
        header->rootIndex = rootIndex;

        free(lChunk);
        free(str1); free(str2); free(value);
        return header;
    } else {
        TextChunk *rChunk = treeGenerateTextChunkForSubtree(rightChildAccessor(node),
                                                            valueAccessor,
                                                            leftChildAccessor,
                                                            rightChildAccessor);
        TextChunk *lChunk = treeGenerateTextChunkForSubtree(leftChildAccessor(node),
                                                            valueAccessor,
                                                            leftChildAccessor,
                                                            rightChildAccessor);

        textChunkEven(lChunk, rChunk);

        TextChunk *spaceChunk = textChunkGenerateBlank(lChunk->rowCount, SUBTREE_SPACING);

        int leftWidth = lChunk->columnCount;
        int spaceWidth = SUBTREE_SPACING;
        int rightWidth = rChunk->columnCount;
        int allWidth = leftWidth + spaceWidth + rightWidth;
        int lRootIndex = lChunk->rootIndex;
        int rRootIndex = rChunk->rootIndex;


        textChunkAdd(lChunk, spaceChunk);
        textChunkAdd(lChunk, rChunk);

        textChunkDestroy(spaceChunk);
        textChunkDestroy(rChunk);

        char *str1 = malloc(sizeof(char) * (allWidth + 1));
        char *str2 = malloc(sizeof(char) * (allWidth + 1));
        str1[0] = '\0'; str2[0] = '\0';

        // Helping
        char *s1 = stringGenerate(' ', (leftWidth + spaceWidth / 2 - CELL_LENGTH / 2));
        char *s2 = stringGenerate(' ', (rightWidth + spaceWidth / 2 - CELL_LENGTH / 2));
        char *s3 = stringGenerate(' ', lRootIndex);
        char *s4 = stringGenerate('-', leftWidth + spaceWidth / 2 - lRootIndex - 1);
        char *s5 = stringGenerate('-', leftWidth + spaceWidth + rRootIndex - (leftWidth + spaceWidth / 2 + 1));
        char *s6 = stringGenerate(' ', rightWidth - rRootIndex - 1);
        char *s7 = stringGenerateCell(value);
        //

        // str1
        stringConcatenate(str1, s1);
        stringConcatenate(str1, s7);
        stringConcatenate(str1, s2);

        // str2
        stringConcatenate(str2, s3);
        stringConcatenate(str2, "|");
        stringConcatenate(str2, s4);
        stringConcatenate(str2, "+");
        stringConcatenate(str2, s5);
        stringConcatenate(str2, "|");
        stringConcatenate(str2, s6);

        int rootIndex = strlen(s3) + 1 + strlen(s4);

        free(s1); free(s2); free(s3); free(s4); free(s5); free(s6); free(s7);

        TextChunk *header = textChunkCreate();
        textChunkPush(header, str1);
        textChunkPush(header, str2);

        textChunkConcatenate(header, lChunk); // lChunk is alive!!!
        header->rootIndex = rootIndex;

        free(lChunk);
        free(str1); free(str2); free(value);
        return header;
    }
}

void treePrintUniversal(void *node,
                        char *(*valueAccessor)(void*),
                        void *(*leftChildAccessor)(void*),
                        void *(*rightChildAccessor)(void*)) {
    TextChunk *chunk = treeGenerateTextChunkForSubtree(node, valueAccessor, leftChildAccessor, rightChildAccessor);
    textChunkPrint(chunk);
    textChunkDestroy(chunk);
}

```

tree.h
```src:tree.h
#include "tree_print.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

// Constants ===

#define VARIABLE_MAX_LENGTH 50
#define TREE_PRINT_SHIFT 4

// Statuses for expression validation
#define STATUS_OK 0
#define STATUS_ERROR -1

// =============

typedef enum {
    BLANK,
    INTEGER,
    VARIABLE,
    BRACKETS_OPEN,
    BRACKETS_CLOSE,
    OPERATION_PLUS,
    OPERATION_MINUS,
    OPERATION_MULT,
    OPERATION_DIVIDE
} TokenType;

typedef struct {
    TokenType type;
    int value; // If type == INTEGER
    char name[VARIABLE_MAX_LENGTH]; // If type == VARIABLE
} Token;

// Node of AST Tree
typedef struct _TreeNode {
    Token token;
    struct _TreeNode *left, *right;
    bool finished; // Used for tree build
} TreeNode;

// AST Tree
typedef struct {
    TreeNode *root;
} Tree;

// Node of stack of AstTreeNodes
typedef struct _TNStackNode {
    struct _TNStackNode *previous;
    TreeNode *value;
} TNStackNode;

// Stack of AstTreeNodes
typedef struct {
    size_t size;
    TNStackNode *last;
} TNStack;

// ================================================================================
// ================================================= Declaration part over ========
// ================================================================================

// Util ===

bool tokenTypeIsOperation(TokenType type);
void tokenPrint(Token token);
char *tokenGetValue(Token token);

// ========

// TreeNode interface ===

TreeNode *treeNodeCreate();
void treeNodeDestroy(TreeNode *node);
void treeNodeDestroySubtree(TreeNode *node);
void treeNodeSimplePrintSubtree(TreeNode *node, int shift);

// =========================

// Tree interface ===

Tree *treeCreate();
void treeDestroy(Tree *tree);
void treeSimplePrint(Tree *tree);
void treePrint(Tree *tree);

// =====================

// Stack interface ===

TNStackNode *tnStackNodeCreate();
void tnStackNodeDestroy(TNStackNode *node);

TNStack *tnStackCreate();
void tnStackDestroy(TNStack *stack);

void tnStackPush(TNStack *stack, TreeNode *value);
size_t tnStackSize(TNStack *stack);
bool tnStackEmpty(TNStack *stack);
TreeNode *tnStackTop(TNStack *stack);
void tnStackSetTop(TNStack *stack, TreeNode *node);
TreeNode *tnStackPop(TNStack *stack);

// ===================

// Parser ===

// ! Status
int parseUnit(char *unit, Token *resultToken);
void parseUtilPlaceMostRightNull(TNStackNode *stackNode, TreeNode *placingNode);
void parseUtilPriorityEmplacement(TNStackNode *stackNode, TreeNode *operationNode);
void parseUtilUnpriorityEmplacement(TNStackNode *stackNode, TreeNode *operationNode);

int parseFromStdin(Tree **resultTree);

// ==========

// Tree to string expression ===

void tokenConvertToStdout(Token token);
void treeNodeSubtreeConvertToStdout(TreeNode *node, bool isRoot);
void treeConvertToStdout(Tree *tree);

// =============================

// ||======||
// ||      ||
// ||      ||
// ||======||

// Special function:

void treeRemoveMultOne(Tree *tree);

```

tree.c
```src:tree.c
#include "tree.h"

// Util ===

bool tokenTypeIsOperation(TokenType type) {
    return type >= OPERATION_PLUS;
}

void tokenPrint(Token token) {
    switch (token.type) {
        case INTEGER:
            printf("%d", token.value);
            break;
        case VARIABLE:
            printf("%s", token.name);
            break;
        case OPERATION_PLUS:
            printf("+");
            break;
        case OPERATION_MINUS:
            printf("-");
            break;
        case OPERATION_MULT:
            printf("*");
            break;
        case OPERATION_DIVIDE:
            printf("/");
            break;
        case BRACKETS_OPEN:
            printf("(");
            break;
        case BRACKETS_CLOSE:
            printf(")");
            break;
        case BLANK:
            break;
    }
}

char *tokenGetValue(Token token) {
    char *s = malloc(sizeof(char) * (VARIABLE_MAX_LENGTH + 1));
    switch (token.type) {
        case INTEGER:
            strcpy(s, intToString(token.value, 10));
            break;
        case VARIABLE:
            strcpy(s, token.name);
            return s;
            break;
        case OPERATION_PLUS:
            s[0] = '+'; s[1] = '\0';
            return s;
            break;
        case OPERATION_MINUS:
            s[0] = '-'; s[1] = '\0';
            return s;
            break;
        case OPERATION_MULT:
            s[0] = '*'; s[1] = '\0';
            return s;
            break;
        case OPERATION_DIVIDE:
            s[0] = '/'; s[1] = '\0';
            return s;
            break;
        case BRACKETS_OPEN:
            s[0] = '('; s[1] = '\0';
            return s;
            break;
        case BRACKETS_CLOSE:
            s[0] = ')'; s[1] = '\0';
            return s;
            break;
        case BLANK:
            s[0] = '\0';
            return s;
            break;
    }
    return s;
}

// ========

// AstNodeTree interface ===

TreeNode *treeNodeCreate() {
    TreeNode *result = malloc(sizeof(TreeNode));
    result->left = NULL;
    result->right = NULL;
    result->finished = false;
    return result;
}

void treeNodeDestroy(TreeNode *node) {
    if (node != NULL) {
        free(node);
    }
}

void treeNodeDestroySubtree(TreeNode *node) {
    if (node != NULL) {
        treeNodeDestroySubtree(node->left);
        treeNodeDestroySubtree(node->right);
        treeNodeDestroy(node);
    }
}

void treeNodeSimplePrintSubtree(TreeNode *node, int shift) {
    if (node == NULL) return;
    treeNodeSimplePrintSubtree(node->left, shift + TREE_PRINT_SHIFT);
    for (int i = 0;i < shift;i++) putchar(' ');
    tokenPrint(node->token);
    putchar('\n');
    treeNodeSimplePrintSubtree(node->right, shift + TREE_PRINT_SHIFT);
}

// =========================

// Tree interface ===

Tree *treeCreate() {
    Tree *tree = malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

void treeDestroy(Tree *tree) {
    if (tree != NULL) {
        treeNodeDestroySubtree(tree->root);
        free(tree);
    }
}

void treeSimplePrint(Tree *tree) {
    assert(tree != NULL);
    treeNodeSimplePrintSubtree(tree->root, 0);
}

// Tree Print

char *valueAccessor(void *obj) {
    TreeNode *node = (TreeNode*)obj;
    //
    return tokenGetValue(node->token);
}

void *leftChildAccessor(void *obj) {
    TreeNode *node = (TreeNode*)obj;
    //
    return (void*)node->left;
}

void *rightChildAccessor(void *obj) {
    TreeNode *node = (TreeNode*)obj;
    //
    return (void*)node->right;
}

void treePrint(Tree *tree) {
    assert(tree != NULL);
    if (tree->root == NULL) return;
    treePrintUniversal((void*)tree->root, valueAccessor, leftChildAccessor, rightChildAccessor);
}

//

// =====================

// Stack interface ===

TNStackNode *tnStackNodeCreate() {
    TNStackNode *node = malloc(sizeof(TNStackNode));
    node->previous = NULL;
    return node;
}

void tnStackNodeDestroy(TNStackNode *node) {
    if (node != NULL) free(node);
}

TNStack *tnStackCreate() {
    TNStack *stack = malloc(sizeof(TNStack));
    stack->size = 0;
    stack->last = NULL;
    return stack;
}

void tnStackDestroy(TNStack *stack) {
    if (stack != NULL) {
        if (stack->last != NULL) {
            TNStackNode *nextNode = stack->last;
            TNStackNode *currentNode = nextNode->previous;
            while (currentNode != NULL) {
                free(nextNode);
                nextNode = currentNode;
                currentNode = nextNode->previous;
            }
            free(nextNode);
        }
        free(stack);
    }
}

void tnStackPush(TNStack *stack, TreeNode *value) {
    assert(stack != NULL);
    if (stack->last == NULL) {
        TNStackNode *node = tnStackNodeCreate();
        node->value = value;
        stack->last = node;
    } else {
        TNStackNode *node = tnStackNodeCreate();
        node->previous = stack->last;
        node->value = value;
        stack->last = node;
    }
    stack->size++;
}

size_t tnStackSize(TNStack *stack) {
    assert(stack != NULL);
    return stack->size;
}

bool tnStackEmpty(TNStack *stack) {
    assert(stack != NULL);
    return tnStackSize(stack) == 0;
}

TreeNode *tnStackTop(TNStack *stack) {
    assert(stack != NULL);
    assert(!tnStackEmpty(stack));
    return stack->last->value;
}

void tnStackSetTop(TNStack *stack, TreeNode *node) {
    assert(stack != NULL);
    stack->last->value = node;
}

TreeNode *tnStackPop(TNStack *stack) {
    assert(stack != NULL);
    assert(!tnStackEmpty(stack));
    TreeNode *result = stack->last->value;
    if (tnStackSize(stack) == 1) {
        tnStackNodeDestroy(stack->last);
        stack->last = NULL;
    } else {
        TNStackNode *previous = stack->last->previous;
        tnStackNodeDestroy(stack->last);
        stack->last = previous;
    }
    stack->size--;
    return result;
}

// ===================

// Parser ===

int parseUnit(char *unit, Token *resultToken) {
    if (unit[0] == '\0') {
        Token token;
        token.type = BLANK;
        *resultToken = token;
    }
    Token token;
    // May be operation
    // One character token
    if (unit[1] == '\0') {
        switch (unit[0]) {
            case '+':
                token.type = OPERATION_PLUS;
                break;
            case '-':
                token.type = OPERATION_MINUS;
                break;
            case '*':
                token.type = OPERATION_MULT;
                break;
            case '/':
                token.type = OPERATION_DIVIDE;
                break;
            case '(':
                token.type = BRACKETS_OPEN;
                break;
            case ')':
                token.type = BRACKETS_CLOSE;
                break;
            default:
                if (isdigit(unit[0])) {
                    token.type = INTEGER;
                    token.value = atoi(unit);
                    break;
                }
                token.type = VARIABLE;
                strcpy(token.name, unit);
                break;
        }
        *resultToken = token;
        return STATUS_OK;
    }

    // Not one character token
    size_t size = strlen(unit);
    if (size > VARIABLE_MAX_LENGTH) return STATUS_ERROR;

    // May be an integer
    if (isdigit(unit[0]) || unit[0] == '-') {
        for (int i = 1;i < (int)size;i++) {
            if (!isdigit(unit[i])) return STATUS_ERROR;
        }
        token.type = INTEGER;
        token.value = atoi(unit);
        *resultToken = token;
        return STATUS_OK;
    }

    // Then it's a variable
    token.type = VARIABLE;
    strcpy(token.name, unit);
    *resultToken = token;
    return STATUS_OK;
}

// Util
void parseUtilPlaceMostRightNull(TNStackNode *stackNode, TreeNode *placingNode) {
    TreeNode *node = stackNode->value;
    if (node == NULL) {
        stackNode->value = placingNode;
        return ;
    }
    while (node->right != NULL) node = node->right;
    node->right = placingNode;
    placingNode->finished = true;
}

void parseUtilPriorityEmplacement(TNStackNode *stackNode, TreeNode *operationNode) {
    TreeNode *node = stackNode->value;
    if (node->finished) {
        operationNode->left = node;
        operationNode->finished = true;
        stackNode->value = operationNode;
    } else {
        while (!node->right->finished) node = node->right;
        TreeNode *rChild = node->right;
        node->right = operationNode;
        operationNode->left = rChild;
        operationNode->finished = true;
    }
}

void parseUtilUnpriorityEmplacement(TNStackNode *stackNode, TreeNode *operationNode) {
    TreeNode *node = stackNode->value;
    operationNode->left = node;
    stackNode->value = operationNode;
}

int parseFromStdin(Tree **resultTree) {
    assert(resultTree != NULL);
    Tree *tree = treeCreate();
    char str[100];
    Token token;
    TNStack *stack = tnStackCreate();

    tnStackPush(stack, NULL);

    do {
        scanf("%[^ \n]", str);
        //
        if (parseUnit(str, &token) == STATUS_ERROR) return STATUS_ERROR;

        if (token.type == BRACKETS_OPEN) {
            tnStackPush(stack, NULL);
        } else if (token.type == INTEGER || token.type == VARIABLE) {
            TreeNode *node = tnStackTop(stack);
            if (node == NULL) {
                node = treeNodeCreate();
                node->token = token;
                node->finished = true;
                tnStackPop(stack);
                tnStackPush(stack, node);
            } else {
                TreeNode *newNode = treeNodeCreate();
                newNode->token = token;
                parseUtilPlaceMostRightNull(stack->last, newNode);
            }
        } else if (token.type == OPERATION_PLUS || token.type == OPERATION_MINUS) {
            TreeNode *operationNode = treeNodeCreate();
            operationNode->token = token;
            parseUtilUnpriorityEmplacement(stack->last, operationNode);
        } else if (token.type == OPERATION_MULT || token.type == OPERATION_DIVIDE) {
            TreeNode *operationNode = treeNodeCreate();
            operationNode->token = token;
            parseUtilPriorityEmplacement(stack->last, operationNode);
        } else if (token.type == BRACKETS_CLOSE) {
            TNStackNode *prev = stack->last->previous;
            parseUtilPlaceMostRightNull(prev, tnStackPop(stack));
            tnStackTop(stack)->finished = true;
        }

    } while (getchar() != '\n');

    tree->root = tnStackPop(stack);
    tnStackDestroy(stack);
    *resultTree = tree;

    return STATUS_OK;
}

// ==========

// Tree to string expression ===

void tokenConvertToStdout(Token token) {
    if (token.type == OPERATION_PLUS) printf("+");
    else if (token.type == OPERATION_MINUS) printf("-");
    else if (token.type == OPERATION_MULT) printf("*");
    else if (token.type == OPERATION_DIVIDE) printf("/");
    else if (token.type == INTEGER) printf("%d", token.value);
    else if (token.type == VARIABLE) printf("%s", token.name);
}

void treeNodeSubtreeConvertToStdout(TreeNode *node, bool isRoot) {
    if (node->finished && !isRoot && (node->token.type == OPERATION_PLUS || node->token.type == OPERATION_MINUS)) {
        printf("( ");
        treeNodeSubtreeConvertToStdout(node->left, false);
        printf(" "); tokenConvertToStdout(node->token); printf(" ");
        treeNodeSubtreeConvertToStdout(node->right, false);
        printf(" )");
    } else if (tokenTypeIsOperation(node->token.type)) {
        treeNodeSubtreeConvertToStdout(node->left, false);
        printf(" "); tokenConvertToStdout(node->token); printf(" ");
        treeNodeSubtreeConvertToStdout(node->right, false);
    } else {
        tokenConvertToStdout(node->token);
    }
}

void treeConvertToStdout(Tree *tree) {
    treeNodeSubtreeConvertToStdout(tree->root, true);
}

// =============================

// ||======||
// ||      ||
// ||      ||
// ||======||

// Special function:

void treeUtilDestroyMultOne(Tree *tree, TreeNode *node, TreeNode *parent, bool isOneLeft) {
    if (parent == NULL) {
        if (isOneLeft) {
            tree->root = node->right;
            free(node->left);
            free(node);
        }
        else {
            tree->root = node->left;
            free(node->right);
            free(node);
        }
        return ;
    }
    if (isOneLeft) {
        treeNodeDestroy(node->left);
        if (parent->left == node) parent->left = node->right;
        else parent->right = node->right;
        treeNodeDestroy(node);
    } else {
        treeNodeDestroy(node->right);
        if (parent->left == node) parent->left = node->left;
        else parent->right = node->left;
        treeNodeDestroy(node);
    }
}

void treeNodeRemoveMultOne(Tree *tree, TreeNode *node, TreeNode *parent) {
    if (node == NULL) return;
    treeNodeRemoveMultOne(tree, node->left, node);
    treeNodeRemoveMultOne(tree, node->right, node);
    if (node->token.type == OPERATION_MULT) {
        if (node->left != NULL && node->left->token.type == INTEGER && node->left->token.value == 1)
            treeUtilDestroyMultOne(tree, node, parent, true);
        else if (node->right != NULL && node->right->token.type == INTEGER && node->right->token.value == 1)
            treeUtilDestroyMultOne(tree, node, parent, false);
    }
}

void treeRemoveMultOne(Tree *tree) {
    assert(tree != NULL);
    treeNodeRemoveMultOne(tree, tree->root, NULL);
}

```


Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.
<b>Подпись преподавателя:</b> _____________________

## 8. Распечатка протокола

```
pepelulka@pepelulka:~/Desktop/labs/repo/Lab24-expr_tree$ build/bin/main
Введите выражение в инфиксной записи:
A * B + ( 1 * B * C * 1 ) - 1 * 2 * 3 - 1 * 1 + BAB
Дерево выражения:
                                                                                       +
                                                                       |---------------+---|
                                                                       -                  BAB
                                               |-----------------------+-------|
                                               -                               *
               |-------------------------------+---------------|           |---+---|
               +                                               *           1       1
       |-------+-----------------------|               |-------+---|
       *                               *               *           3
   |---+---|                   |-------+---|       |---+---|
   A       B                   *           1       1       2
                       |-------+---|
                       *           C
                   |---+---|
                   1       B


Преобразованное выражение:
( A * B + B * C ) - 2 * 3 - 1 + BAB
Дерево преобразованного выражения:
                                                       +
                                               |-------+---|
                                               -          BAB
                               |---------------+---|
                               -                   1
               |---------------+-------|
               +                       *
       |-------+-------|           |---+---|
       *               *           2       3
   |---+---|       |---+---|
   A       B       B       C
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 15.06.23 | 18:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы

<b>Div 3</b>

[1840A](https://codeforces.com/contest/1840/submission/208720444)
[1840B](https://codeforces.com/contest/1840/submission/208727610)
[1840C](https://codeforces.com/contest/1840/submission/208738984)
[1840D](https://codeforces.com/contest/1840/submission/208752432)

Дорешка:

[1840G1](https://codeforces.com/contest/1840/submission/209866290)

## 11. Выводы
Были детальнее изучены динамические структуры данных. Были получены основы синтаксического анализа и написания парсеров для текста. Было получено более глубокое понимание принципов работы компиляторов.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> _________________

