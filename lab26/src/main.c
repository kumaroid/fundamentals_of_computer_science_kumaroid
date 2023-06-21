#include "deque.h"

int main() {
    Deque *deque = dequeCreate();
    dequePushBack(deque, 3);
    dequePushFront(deque, 7);
    dequePushBack(deque, 12);
    dequePushBack(deque, -11);
    dequePushBack(deque, 34);
    dequePushBack(deque, 5);
    dequePrint(deque);
    deque = dequeSort(deque);
    dequePrint(deque);
    dequeDestroy(deque);
}
