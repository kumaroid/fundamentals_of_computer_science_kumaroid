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