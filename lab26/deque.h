#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size, capacity;
} Deque;

Deque *dequeCreate();
void dequeDestroy(Deque *deque);
void dequeResize(Deque *deque, size_t size);
size_t dequeSize(Deque *deque);

void dequePushBack(Deque *deque, int value);
int dequePopBack(Deque *deque);
void dequePushFront(Deque *deque, int value);
int dequePopFront(Deque *deque);
int dequeTop(Deque *deque);
int dequeFront(Deque *deque);
void dequePrint(Deque *deque);

// Освобождает указатель deque. Возвращает указатель на созданный новый дек.
Deque *dequeReverse(Deque *deque);
// Освобождает указатели deque1 и deque2. Оба дека должны быть отсортированы. 
// Возвращает указатель на созданный новый дек, содержащий результат слияния.
Deque *dequeMerge(Deque *deque1, Deque *deque2);
Deque *dequeSort(Deque *deque);
