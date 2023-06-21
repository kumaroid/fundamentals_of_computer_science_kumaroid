#include "deque.h"
#include "assert.h"

Deque *dequeCreate() {
    Deque *deque = malloc(sizeof(Deque));
    deque->size = 0;
    deque->capacity = 1;
    deque->data = malloc(sizeof(int));
    return deque;
}

void dequeDestroy(Deque *deque) {
    if (deque != NULL) {
        free(deque->data);
        free(deque);
    }
}

void dequeResize(Deque *deque, size_t size) {
    assert(deque != NULL);
    size_t newCapacity = deque->capacity;
    while (newCapacity < size) {
        newCapacity *= 2;
    }
    deque->size = size;
    if (newCapacity != deque->capacity) {
        deque->capacity = newCapacity;
        deque->data = realloc(deque->data, sizeof(int) * deque->capacity);
    }
}

size_t dequeSize(Deque *deque) {
    assert(deque != NULL);
    return deque->size;
}

void dequePushBack(Deque *deque, int value) {
    assert(deque != NULL);
    dequeResize(deque, deque->size + 1);
    deque->data[deque->size - 1] = value;
}

int dequePopBack(Deque *deque) {
    assert(deque != NULL && deque->size != 0);
    dequeResize(deque, deque->size - 1);
    return deque->data[deque->size];
}

void dequePushFront(Deque *deque, int value) {
    assert(deque != NULL);
    dequeResize(deque, deque->size + 1);
    for (size_t i = deque->size; i > 0; i--) {
        deque->data[i] = deque->data[i - 1];
    }
    deque->data[0] = value;
}

int dequePopFront(Deque *deque) {
    assert(deque != NULL && deque->size != 0);
    dequeResize(deque, deque->size - 1);
    for (size_t i = 0; i < deque->size; i++) {
        deque->data[i] = deque->data[i + 1];
    }
}

int dequeTop(Deque *deque) {
    assert(deque != NULL && deque->size != 0);
    return deque->data[deque->size - 1];
}

int dequeFront(Deque *deque) {
    assert(deque != NULL && deque->size != 0);
    return deque->data[0];
}

void dequePrint(Deque *deque) {
    assert(deque != NULL);
    for (size_t i = 0; i < deque->size; i++) {
        printf("%d ", deque->data[i]);
    }
    putchar('\n');
}

Deque *dequeReverse(Deque *deque) {
    Deque *result = dequeCreate();
    while (dequeSize(deque) != 0) {
        dequePushBack(result, dequePopBack(deque));
    }
    dequeDestroy(deque);
    return result;
}

Deque *dequeMerge(Deque *deque1, Deque *deque2) {
    Deque *result = dequeCreate();
    while (dequeSize(deque1) != 0 || dequeSize(deque2) != 0) {
        if (dequeSize(deque1) == 0) {
            dequePushBack(result, dequePopBack(deque2));
        } else if (dequeSize(deque2) == 0) {
            dequePushBack(result, dequePopBack(deque1));
        } else {
            if (dequeTop(deque1) > dequeTop(deque2)) {
                dequePushBack(result, dequePopBack(deque1));
            } else {
                dequePushBack(result, dequePopBack(deque2));
            }
        }
    }
    dequeDestroy(deque1);
    dequeDestroy(deque2);
    return dequeReverse(result);
}

Deque *dequeSort(Deque *deque) {
    assert(deque != NULL);
    if (dequeSize(deque) <= 1) {
        return deque;
    }
    Deque *deque1 = dequeCreate(), *deque2 = dequeCreate();
    size_t startSize = dequeSize(deque);
    for (size_t i = 0; i < startSize / 2; i++) {
        dequePushBack(deque1, dequePopBack(deque));
    }
    while (dequeSize(deque) != 0) {
        dequePushBack(deque2, dequePopBack(deque));
    }
    deque1 = dequeSort(dequeReverse(deque1));
    deque2 = dequeSort(dequeReverse(deque2));
    return dequeMerge(deque1, deque2);
}
