# Отчёт по лабораторной работе №23 по курсу “Языки и методы программирования”

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
Составить программу на Си для интерактивного взаимодействия с деревом поиска.
## 3. Задание (вариант № 15)
Проверить монотонность возрастания ширины уровня дерева.

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

Дерево поиска было реализовано с помощью динамических структур. Каждая вершина представляла собой структуру, содержащую значение узла и указатели на родителя, левого и
правого детей.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию].

main.c:
```src:main.c
#include <stdio.h>
#include <stdlib.h>

typedef struct Tst {
    int key;
    struct Tst *son;
    struct Tst *brother;
} Node;

Node* create_tree(int val) {
    Node* tree = (Node*)malloc(sizeof(Node));
    if (tree == NULL) {
        exit(1);
    }
    tree->key = val;
    tree->son = NULL;
    tree->brother = NULL;
    return tree;
}

void delete_tree(Node *tree) {
    if (tree == NULL){
        return;
    }
    delete_tree(tree->son);
    delete_tree(tree->brother);
    free(tree);
}

Node* find_node(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    if (root->key == key) {
        return root;
    }
    Node* node = find_node(root->son, key);
    if (node != NULL) {
        return node;
    }
    return find_node(root->brother, key);
}

void tree_print(Node* root, int depth) {
    if (root == NULL) {
        return;
    }
    if (root->key != -1) { 
        printf("%*s", depth * 4, "");
        printf("%d\n", root->key);
    }
    tree_print(root->son, depth + 1);
    tree_print(root->brother, depth); 
}

Node* delete_subtree(Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return NULL;
    }

    char c;
    Node* curr = root;
    Node* prev = NULL;
    Node* new_root = NULL;

    while ((c = getchar()) != '\n') {
        if (c == ' ') {
            continue;
        }
        if (c == 'r') {
            prev = NULL;
            curr = root;
        } else if (c == 's') {
            if (curr->son == NULL) {
                printf("Node has no son\n");
                return root;
            }
            prev = curr;
            curr = curr->son;
        } else if (c == 'b') {
            if (prev == NULL || prev->brother == NULL) {
                printf("Node has no brother\n");
                return root;
            }
            curr = prev->brother;
            prev = NULL;
        }
    }
    if (curr == root) {
        new_root = root->brother ? root->brother : root->son;
        free(root);
        root = NULL;
        return new_root;
    }
    if (prev == NULL) {
        new_root = curr->brother ? curr->brother : curr->son;
        free(curr);
        curr = NULL;
        return root;
    }
    if (prev->son == curr) {
        prev->son = curr->brother;
    } else {
        Node* temp = prev->son;
        while (temp->brother != curr) {
            temp = temp->brother;
        }
        temp->brother = curr->brother;
    }
    curr->son = NULL;
    curr->brother = NULL;
    free(curr); 
    return root;
}


Node* add_node(Node* tree) {
    Node* t = tree;
    int value;
    char c;
    while ((c = getchar()) != 'r') {
        continue;
    }
    if (tree == NULL) {
        if (scanf("%d", &value) != 1) {
            printf("Input error\n");
            free(create_tree(value));
            return tree;
        }
        tree = create_tree(value);
        return tree;
    }
    while ((c = getchar()) != ' ') {
        if (c == 's') {
            t = t->son;
        }
        if (c == 'b') {
            t = t->brother;
        }
    }
    if (scanf("%d", &value) != 1) {
        printf("Input error\n");
        Node* ntree = create_tree(value);
        free(ntree);
        return tree;
    }
    Node* ntree = create_tree(value);
    if (t->son != NULL) {
        t = t->son;
        while (t->brother != NULL) {
            t = t->brother;
        }
        t->brother = ntree;
    } else {
        t->son = ntree;
    }
    return tree;
}

int is_width_monotonic(Node* root) {
    if (root == NULL) {
        return 1;
    }

    int prev_width = 0; 
    int curr_width = 0;
    int increasing = 0; 
    Node* level_start = root; 
    Node* curr_node = NULL; 
    Node* next_level_start = NULL;

    while (level_start != NULL) {
        curr_node = level_start;
        curr_width = 0;
        while (curr_node != NULL) {
            curr_width++;
            if (curr_node->son != NULL) {
                if (next_level_start == NULL) {
                    next_level_start = curr_node->son;
                } else {
                    Node* temp = next_level_start;
                    while (temp->brother != NULL) {
                        temp = temp->brother;
                    }
                    temp->brother = curr_node->son;
                }
            }
            curr_node = curr_node->brother;
        }
        if (prev_width > curr_width) {
            increasing = 0;
            break;
        } else if (prev_width < curr_width) {
            increasing = 1;
        }
        prev_width = curr_width;
        level_start = next_level_start;
        next_level_start = NULL;
    }
    return increasing;
}

int main() {
    char c;
    Node* root = NULL;
    while ((c = getchar()) != EOF) {
        if (c == 'a') {
            root = add_node(root);
        }
        if (c == 'd') {
            root = delete_subtree(root); 
        }
        if (c == 'p'){
            tree_print(root, 0);
        }
        if (c == 't'){
          if (is_width_monotonic(root)) {
            printf("The tree has monotonically increasing width at each level.\n");
          } else {
            printf("The tree does not have monotonically increasing width at each level.\n");
          }
        }
        if (c == 'q'){
            break;
        }
    }
  delete_tree(root);
    return 0;
}
```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.
<b>Подпись преподавателя:</b> _____________________

## 8. Распечатка протокола
```

```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 12.06.23 | 18:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы

<a href = 'https://codeforces.com/contest/1840/submission/208779707'>def(Zaschita)</a>

## 11. Выводы
Были изучены динамические структуры данных. Была составлена программа на языке Си для обработки двоичного дерева. Были приобретены навыки, которые будут полезны для выполнения других лабораторных работ и курсовых проектов.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> _________________



