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

Makefile:
```src:Makefile
CC ?= gcc 
CFLAGS ?= -g -Werror -pedantic
main: main.o tree.o
	${CC} -o main main.o tree.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: tree.c tree.o
	${CC} ${CFLAGS} -c tree.c

clean: 
	rm -rf *.o main

```

main.c:
```src:main.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

int main(void)
{
    char s[8];

    Tree tree = NULL; // Указатель на корень дерева
    int root = 0, ver = 0, parent = 0; // Переменные для новых узлов дерева

    printf("\nPrint 'help' for more information\n\n"); // Выводим подсказку при запуске программы
    while (1) {
        scanf("%7s", s); // Ввод символа с клавиатуры
        if (!strcmp(s, "insert") || !strcmp(s, "ins")) { // Задаем корень дерева
            if(!tree) {
                printf("Add the value of the tree root:\n");
                scanf("%d", &root);
                tree = tree_create(root);
            }
            while (scanf("%d%d", &parent, &ver)) {
                tree_add_node(tree, parent, ver);
            }
        } else if (!strcmp(s, "delete")) { // Если команда delete
            if(!tree) printf("Tree doesnt exist, use command 'help'\n"); //Если нет дерева, выводим подсказку
            else {
                scanf("%d", &ver);
                tree_del_node(tree, ver); // Удаляем зачение
            }
        } else if (!strcmp(s, "quit")) { // Если команда quit
            if (tree) tree_destroy(tree); // Рушим дерево 
            break;
        } else if (!strcmp(s, "run")) { // Если команда run, начинаем проверку на монотонность
            if(!tree) printf("Tree doesnt exist, use command 'help'\n"); 
            else {
                check_monotonicity_of_decreaset(tree);
            }
        } else if (!strcmp(s, "print")) { // Если команда print, выводим дерево
            if (!tree) printf("Tree doesnt exist, use command 'help'\n");
            else {
                printf("\n\n");
                tree_print(tree);
                printf("\n\n");
            }
        } else if (!strcmp(s, "destroy")) { // Удаляем дерево
            if (!tree) printf("Tree doesnt exist, use command 'help'\n");
            else {
                tree_destroy(tree);
                tree = NULL;
            }
        } else if (!strcmp(s, "help")) { // Помощник
            printf("\n\nCommand 'insert' - if the tree doesnt exist, makes a tree. Command 'ins' - if tree was made, adds vertices in the tree\n\n");
            printf("Command 'delete num' deletes all the vertices and all her children\n\n");
            printf("Command 'print' prints the vertices of the tree\n\n");
            printf("Command 'run' checks monotonicity of decreseaset of the tree\n\n");
            printf("Command 'quit' stops the program\n\n");
            printf("Command 'destroy' deletes the tree completely\n\n");
        } else {
            printf("\n\nThat command doesnt exist, try command 'help' \n\n");
        }
    }
    return 0;
}
```

tree.c:
```src:tree.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

#define DEEP 0
#define max(x,y) ((x) > (y) ? (x) : (y)) //Выбираем константу функции максимума путем тернарного оператора


struct _tree { // Дерево
    TreeItem value; // Значение узла дерева
    Tree child; // Указатель на первого потомка узла
    Tree sibling; // Указатель на правого брата
}; //*Tree

Tree tree_create(TreeItem value) // Создание нового узла дерева
{
    Tree tree = (Tree) malloc(sizeof(*tree)); // Задаем размер в памяти для дерева, которую задает пользователь 
    if(!tree) { //Проверка на успешное выделение памяти
        fprintf(stderr, "%s\n", "Error: no memory");
        exit(1);
    }
    tree->value = value; // Устанавливаем значение поля value на структуру указателя tree
    tree->child = NULL;
    tree->sibling = NULL;
    
    return tree;
}

void tree_add_node(Tree tree, TreeItem parent, TreeItem value) // Добавление нового узла
{
    Tree parent_node = tree_find(tree, parent); // находим узел parent
    if(parent_node) { // Если узел найден
        if(!parent_node->child) { // Проверка на дочерний узел
            parent_node->child = tree_create(value); // Создаем новый узел
        } else {
            parent_node = parent_node->child; //Если нет, то новый узел - дочерний
            while(parent_node->sibling) { // Если новый узел имеет дочерние узлы, то находим последний и создаем соседа
                parent_node = parent_node->sibling;
            }
            parent_node->sibling = tree_create(value);
        }
    } else {
        printf("The specified parent vertex was not found\n"); // Если нет - выводим ошибку
    }
}

Tree tree_find(Tree tree, TreeItem c) // Функция поиск узла с заданным значением в дереве
{
    if(!tree) { // Рекурсивный обход всех узлов дерева
        return NULL;
    }

    if(tree->value == c) { // Нашел!
        return tree;
    }

    Tree result = NULL; // Возвращаемся из функции
    if(tree->child) {
        result = tree_find(tree->child, c);
        if(result) return result;
    }

    if(tree->sibling) { // Если соседний элемент есть
        result = tree_find(tree->sibling, c);
        if(result) return result;
    }

}


void tree_print_node(Tree tree, int indent) // Вывод на экран терминала узлы
{
    for(int i = 0; i < indent; ++i) { // Уменьшаем кол-во отступов \t
        printf("\t");
    }
    printf("%d\n", tree->value); // Значение узла
    if(tree->child) {
        tree_print_node(tree->child, indent + 1); // Если дочерний узел выводим его + отступ+1
    }
    if(tree->sibling) {
        tree_print_node(tree->sibling, indent); // Если соседний то значение узла + отступ
    }
}

void tree_print(Tree tree) // Рекурсивный вызов самой себя функции
{
    tree_print_node(tree, 0);
}

void tree_destroy(Tree tree)
{

    if(tree->child) {
        tree_destroy(tree->child);
    }
    if(tree->sibling) {
        tree_destroy(tree->sibling);
    }
    free(tree);
    tree = NULL;
}


void tree_del_node(Tree tree, TreeItem value) // Рекурсивно удаляет все дочерние и соседние узлы
{
    if(tree->child) { // Проверка у текущего узла наличие дочернего 
        if(tree->child->value == value) { // Если есть
            Tree tmp = tree->child; // Временный вызов
            tree->child = tree->child->sibling; // Если дочерний равен соседнему
            if (tmp->child) { // Временный имеет дочерний
                tree_destroy(tmp->child); // Подставляем
            }
            free(tmp); // Удаление tmp
            tmp = NULL; // Удаление
            return;
        } else {
            tree_del_node(tree->child, value); // Ничего
        }
    }


    if(tree->sibling) { // Проверка на наличие соседнего
        if(tree->sibling->value == value) { // Если есть
            Tree tmp = tree->sibling; // Временный вызов соседнего
            tree->sibling = tree->sibling->sibling; // Его соседние узлы
            if(tmp->child) { // Если есть у него дочерние
                tree_destroy(tmp->child); // Подставляем
            }
            free(tmp); // Удаление
            tmp = NULL; // Удаление
            return;
        } else {
            tree_del_node(tree->sibling, value); // Ничего
        }
    }
}

int max_level(Tree tree, int deep) // Поиск максимальной глубины дерева
{
    if(!tree) return deep - 1; // Поднимаемся выше по дереву
    return max(max_level(tree->child, deep + 1), max_level(tree->sibling, deep)); // Вызов каждого дочернего и соседнего узла
}

void couting_nodes_on_the_lvls(Tree tree, int level, int *mat) // Счетчик уровней дерева
{
    mat[level] += 1; // При каждом вызове увеличивает на 1
    if(tree->child) { // Если дочерний узел
        couting_nodes_on_the_lvls(tree->child, level + 1, mat);
    }
    if(tree->sibling) { // Если соседний узел
        couting_nodes_on_the_lvls(tree->sibling, level, mat);
    }
}

void check_monotonicity_of_decreaset(Tree tree) // Проверка на монотонное уменьшение
{
    bool more_one_lvl = false; // Проверка на наличие более одного уровня в дереве
    bool decreasing = true; // Уменьшение
    if(tree->child == NULL) { // Дочерних в дереве нет - монотонности нет
        printf("Tree consists only from root, thats not enough for definition the monotony\n");
    } else {
        if(tree->child->child) { // Если у дочерних есть дочерний
            more_one_lvl = true; // Проверяем
        }
        for(Tree tmp = tree->child; tmp->sibling; tmp = tmp->sibling) { 
            if(tmp->child != NULL) { // Если есть дочерний узел
                more_one_lvl = true; 
                break;
            }
        }
        if(more_one_lvl) { // Если больше одного
            int deep = max_level(tree, DEEP); // Выявление максимальной глубины дерева
            int level = 0; // Подсчет уровней
            int mat[deep]; // Создание массива на подсчет узлов на каждом уровне
            for(int i = 0; i <= deep; ++i) { 
                mat[i] = 0; // Заполнение подсчета
            }
            couting_nodes_on_the_lvls(tree, level, mat); // Заполняем массив счетчика
            for(int i = 1; i < deep; ++i) { // Проверка монотонности
                if(mat[i] <= mat[i + 1]) { // Если следующий больше предыдущего узла
                    printf("Tree doesnt decrease\n"); // "Не монотонно"
                    decreasing = false;
                    break;
                }
            }
            if(decreasing) printf("Tree decreases\n"); // Если дерево монотонно - true output
        } else printf("Tree have only 1 level, thats not enough for definition the monotony\n"); // Уровень дерева один - не подходит условию
    }
}
```

tree.h
```src:tree.h
#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int TreeItem;
typedef struct _tree *Tree;

Tree tree_create(TreeItem value);
void tree_add_node(Tree tree, TreeItem parent, TreeItem value);
void tree_print(Tree tree);
void tree_print_node(Tree tree, int indent);
void tree_destroy(Tree tree);
void tree_del_node(Tree tree, TreeItem value);
Tree tree_find(Tree tree, TreeItem c);

int max_level(Tree tree, int deep);
void counting_nodes_on_the_lvls(Tree tree, int level, int *mat);
void check_monotonicity_of_decreaset(Tree tree);

#endif // _TREE_H_
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



