#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void create_matrix(int st, int col, int matrix[st][col]);
void print_right_center(int st, int col, int matrix[st][col]);

void print_right_right_up(int st, int col, int matrix[st][col]);

void print_right_up(int st, int col, int matrix[st][col]);

void print_right_up_up(int st, int col, int matrix[st][col]);

void print_center_up(int st, int col, int matrix[st][col]);

void print_left_up_up(int st, int col, int matrix[st][col]);

void print_left_up(int st, int col, int matrix[st][col]);

void print_left_left_up(int st, int col, int matrix[st][col]);

void print_left_center(int st, int col, int matrix[st][col]);

void print_left_left_down(int st, int col, int matrix[st][col]);

void print_left_down(int st, int col, int matrix[st][col]);

void print_left_down_down(int st, int col, int matrix[st][col]);

void print_center_down(int st, int col, int matrix[st][col]);

void print_right_down_down(int st, int col, int matrix[st][col]);

void print_right_down(int st, int col, int matrix[st][col]);

void print_right_right_down(int st, int col, int matrix[st][col]);

void main() {
    int size;
    scanf("%d", &size);
    int matrix[size][size];
    create_matrix(size, size, matrix);
    print_right_center(size, size, matrix);

    print_right_right_up(size, size, matrix);

    print_right_up(size, size, matrix);

    print_right_up_up(size, size, matrix);

    print_center_up(size, size, matrix);

    print_left_up_up(size, size, matrix);

    print_left_up(size, size, matrix);

    print_left_left_up(size, size, matrix);

    print_left_center(size, size, matrix);

    print_left_left_down(size, size, matrix);

    print_left_down(size, size, matrix);

    print_left_down_down(size, size, matrix);

    print_center_down(size, size, matrix);

    print_right_down_down(size, size, matrix);

    print_right_down(size, size, matrix);

    print_right_right_down(size, size, matrix);
    
    getch();
}

void create_matrix(int st, int col, int matrix[st][col]){
    int num, size = st;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
}

void print_right_center(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2, width = (st - 1) / 2;
    for(width; width < col; width++){
        printf("%d ", matrix[height][width]);
    }
    printf("\n");
}

void print_right_right_up(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2 - 1, width = st - 1, center = (st - 1) / 2;
    while (height != 0)
    {
        if (abs(center - height) != abs(center - width))
        {
            printf("%d ", matrix[height][width]);
            width--;
        }
        else
        { 
            height-- ;
            width = st - 1;
        }
    }
    printf("\n");
}

void print_right_up(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2, width = (st - 1) / 2;
    for(width; width < col; width++){
        printf("%d ", matrix[height][width]);
        height--;
    }
    printf("\n");
}

void print_right_up_up(int st, int col, int matrix[st][col]){
    int height = 0, i = 0, width = st - 2, center = (st - 1) / 2;
    while (st - 2 - i != center)
    {
        if (width != center)
        {
            printf("%d ", matrix[height][width]);
            width--;
            height++;
        }
        else
        { 
            height = 0 ;
            i++;
            width = st - 2 - i;
        }
    }
    printf("\n");
}

void print_center_up(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2, width = (st - 1) / 2;
    for(height; height >= 0; height--){
        printf("%d ", matrix[height][width]);
    }
    printf("\n");
}

void print_left_up_up(int st, int col, int matrix[st][col]){
    int height = 0, width = (st - 1) / 2 - 1, center = (st - 1) / 2;
    while (width != 0)
    {
        if (abs(center - height) != abs(center - width))
        {
            printf("%d ", matrix[height][width]);
            height++;
        }
        else
        { 
            height = 0 ;
            width--;
        }
    }
    printf("\n");
}

void print_left_up(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2, width = (st - 1) / 2;
    for(width; width >= 0; width--){
        printf("%d ", matrix[height][width]);
        height--;
    }
    printf("\n");
}

void print_left_left_up(int st, int col, int matrix[st][col]){
    int height = 1, width = 0, center = (st - 1) / 2, i = 1;
    while (i != center)
    {
        if (height != center)
        {
            printf("%d ", matrix[height][width]);
            width++;
            height++;
        }
        else
        { 
            width = 0;
            i++;
            height = i;
        }
    }
    printf("\n");
}

void print_left_center(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2, width = (st - 1) / 2;
    for(width; width >= 0; width--){
        printf("%d ", matrix[height][width]);
    }
    printf("\n");
}

void print_left_left_down(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2 + 1, width = 0, center = (st - 1) / 2, i = center + 1;
    while (i != st - 1)
    {
        if (abs(center - height) != abs(center - width))
        {
            printf("%d ", matrix[height][width]);
            width++;
        }
        else
        { 
            width = 0;
            i++;
            height = i;
        }
    }
    printf("\n");
}


void print_left_down(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2, width = (st - 1) / 2;
    for(width; width >= 0; width--){
        printf("%d ", matrix[height][width]);
        height++;
    }
    printf("\n");
}

void print_left_down_down(int st, int col, int matrix[st][col]){
    int height = st - 1, i = 1, width = 1, center = (st - 1) / 2;
    while (i != center)
    {
        if (width != center)
        {
            printf("%d ", matrix[height][width]);
            width++;
            height--;
        }
        else
        { 
            height = st - 1 ;
            i++;
            width = i;
        }
    }
    printf("\n");
}

void print_center_down(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2, width = (st - 1) / 2;
    for(height; height < st; height++){
        printf("%d ", matrix[height][width]);
    }
    printf("\n");
}

void print_right_down_down(int st, int col, int matrix[st][col]){
    int height = st - 1, width = (st - 1) / 2 + 1, center = (st - 1) / 2;
    while (width != st - 1)
    {
        if (abs(center - height) != abs(center - width))
        {
            printf("%d ", matrix[height][width]);
            height--;
        }
        else
        { 
            height = st - 1 ;
            width++;
        }
    }
    printf("\n");
}

void print_right_down(int st, int col, int matrix[st][col]){
    int height = (st - 1) / 2, width = (st - 1) / 2;
    for(width; width < col; width++){
        printf("%d ", matrix[height][width]);
        height++;
    }
    printf("\n");
}

void print_right_right_down(int st, int col, int matrix[st][col]){
    int height = st - 2, width = st - 1, center = (st - 1) / 2, i = st - 2;
    while (i != center)
    {
        if (height != center)
        {
            printf("%d ", matrix[height][width]);
            width--;
            height--;
        }
        else
        { 
            width = st - 1;
            i--;
            height = i;
        }
    }
    printf("\n");
}
