Отчёт по лабораторной работе №15 по курсу "Фундаментальная информатика"
Студент группы: М80-108Б-22 Иванов Андрей Кириллович, № по списку 10

Контакты e-mail: andr-ushka2@yandex.ru

Работа выполнена: «29» ноября 2022 г.

Преподаватель: асп. каф. 806 Сахарин Никита Александрович

Входной контроль знаний с оценкой:

Отчет сдан «17» Декабря 2022 г.

Подпись преподавателя: ________________

1. Тема
Обработка матриц

2. Цель работы
Составить программу на языке Си, производящую обработку квадратной матрицы порядка NxN (1 <= N <= 8), из целых чисел, вводимой из стандартного входного текстового файла.

3. Задание (вариант № 9*)
Циклический сдвиг элементов матрицы в её строчном представлении на 8 элементов.(8 - номер группы)

4. Оборудование
Процессор: AMD Ryzen 5 5600H (12) @ 3.600GHz
ОП: 32GiB 3200 MHz LPDDR4
Текстовый редактор: Visual Studio Code версия 1.73.0

5. Программное обеспечение:
Операционная система семейства: Microsoft Windows 11 Pro
Компилятор: GNU Compiler Collection
Текстовый редактор: Visual Studio Code версия 1.73.0

6. Идея, метод, алгоритм решения задачи (в формах: словесной, псевдокода, графической [блок-схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями)
Ввод размера матрицы;
Создание матрицы;
Написание функций, необходимых для выполнения задачи;
Вывод ответа.
7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию].

```c
#include <stdio.h>
#include <stdlib.h>

void out(int N, int m[], int n_g){
  int b[N*N];
  for (int k = n_g%(N*N) - 1; k >= 0; --k)
  {
    b[k] = m[N*N - (n_g%(N*N) - k)];
  }
  for (int k = 0; k < N*N - n_g%(N*N); k++)
  {
    b[k + n_g%(N*N)] = m[k];
  }
  printf("OUT:\n");
  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++) {
      printf("%d ", b[i * N + j]);
    }
    printf("\n");
  }
}


int main() {
  int N;
  int n_g;
  printf("GROUP NUMBER\n");
  scanf("%d", &n_g);
  printf("MATRIX SIZE:\n");
  scanf("%d", &N);
  int m[N*N];
   
  printf("MATRIX:\n");

  for (int k = 0; k != N*N; k++)
  {
      scanf("%d", &m[k]);
  }
  out(N, m, n_g);
  
}
```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы. Допущен к выполнению работы.
Подпись преподавателя: ________________

8. Распечатка протокола

```c
PS C:\Users\1\Documents\cc> gcc -g lab15.c -pedantic -Wall
PS C:\Users\1\Documents\cc> ./a.exe
GROUP NUMBER
2
MATRIX SIZE:
3
MATRIX:
1 2 3 4 5 6 7 8 9
OUT:
8 9 1
2 3 4
5 6 7
PS C:\Users\1\Documents\cc> gcc -g lab15.c -pedantic -Wall
PS C:\Users\1\Documents\cc> ./a.exe
GROUP NUMBER
9
MATRIX SIZE:
3
MATRIX:
1 2 3 4 5 6 7 8 9
OUT:
1 2 3
4 5 6
7 8 9
PS C:\Users\1\Documents\cc> ./a.exe      
GROUP NUMBER
3
MATRIX SIZE:
4
MATRIX:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
OUT:
14 15 16 1
2 3 4 5
6 7 8 9
10 11 12 13
PS C:\Users\1\Documents\cc> gcc .\lab15.c
PS C:\Users\1\Documents\cc> ./a.exe      
GROUP NUMBER
12
MATRIX SIZE:
4
MATRIX:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
OUT:
5 6 7 8
9 10 11 12
13 14 15 16
1 2 3 4
```

10. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.
№	Лаб. или дом.	Дата	Время	Событие	Действие по исправлению	Примечание
1	дом.	29.11.22	13:00	Выполнение лабораторной работы	-	-
11. Замечания автора по существу работы — Написание команд для отработки навыков работы в ОС UNIX.
12. Выводы
Была написана программа на языке на Си, выполняющая указанное вариантом действие над квадратной матрицей. В результате выполнения работы, были приобретены навыки для работы с квадратными матрицами и обработки их элементов.

Недочёты при выполнении задания могут быть устранены следующим образом: —
