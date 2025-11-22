#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

#define ROWS 3
#define COLS 4

struct student
{
    char famil[20];
    char name[20];
    char facult[20];
    int Nomzach;
};

int partial_match(const char* str1, const char* str2) {
    return strstr(str1, str2) != NULL;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("ЗАДАНИЕ 1:\n\n");

    int n = 10;
    int a[10];
    int i;

    srand(time(NULL));

    for (i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }

    printf("Сгенерированный массив: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    int min = a[0];
    int max = a[0];

    for (i = 1; i < n; i++)
    {
        if (a[i] < min)
            min = a[i];
        if (a[i] > max)
            max = a[i];
    }

    printf("Минимальный элемент: %d\n", min);
    printf("Максимальный элемент: %d\n", max);
    printf("Разница между максимальным и минимальным: %d\n", max - min);

    printf("\nЗАДАНИЕ 2:\n\n");

    int b[10];

    for (i = 0; i < n; i++)
    {
        b[i] = rand() % 100;
    }

    printf("Массив случайных чисел:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d ", b[i]);
    }
    printf("\n");

    printf("\nЗАДАНИЕ 3:\n\n");

    int size;
    int* dynamic_array;

    printf("Введите размер массива: ");
    scanf("%d", &size);

    dynamic_array = (int*)malloc(size * sizeof(int));

    if (dynamic_array == NULL)
    {
        printf("Ошибка выделения памяти!\n");
    }
    else
    {
        printf("Введите %d элементов массива:\n", size);
        for (i = 0; i < size; i++)
        {
            printf("Элемент %d: ", i + 1);
            scanf("%d", &dynamic_array[i]);
        }

        printf("Введенный массив:\n");
        for (i = 0; i < size; i++)
        {
            printf("%d ", dynamic_array[i]);
        }
        printf("\n");

        free(dynamic_array);
    }

    while (getchar() != '\n');

    printf("\nЗАДАНИЕ 4:\n\n");

    int matrix[ROWS][COLS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int col_sums[COLS] = { 0 };
    int j;

    printf("Исходная матрица:\n");
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }

    for (j = 0; j < COLS; j++)
    {
        for (i = 0; i < ROWS; i++)
        {
            col_sums[j] += matrix[i][j];
        }
    }

    printf("\nСуммы по столбцам:\n");
    for (j = 0; j < COLS; j++)
    {
        printf("Столбец %d: %d\n", j + 1, col_sums[j]);
    }

    printf("\nЗАДАНИЕ 5:\n\n");

    struct student stud[4];
    int found = 0;
    char search_string[20];
    int search_nomzach;
    int search_choice;

    for (i = 0; i < 4; i++)
    {
        printf("Введите фамилию студента %d: ", i + 1);
        scanf("%19s", stud[i].famil);
    }

    for (i = 0; i < 4; i++)
    {
        printf("Введите имя студента %s: ", stud[i].famil);
        scanf("%19s", stud[i].name);
    }

    for (i = 0; i < 4; i++)
    {
        printf("Введите название факультета студента %s %s: ", stud[i].famil, stud[i].name);
        scanf("%19s", stud[i].facult);
    }

    for (i = 0; i < 4; i++)
    {
        printf("Введите номер зачётной книжки студента %s %s: ", stud[i].famil, stud[i].name);
        scanf("%d", &stud[i].Nomzach);
    }

    printf("\nСписок всех студентов:\n");
    for (i = 0; i < 4; i++)
    {
        printf("Студент %s %s обучается на факультете %s, номер зачётной книжки %d \n",
            stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
    }

    printf("\nПоиск студента:\n");
    printf("1 - По фамилии\n");
    printf("2 - По имени\n");
    printf("3 - По номеру зачетной книжки\n");
    printf("Выберите вариант поиска: ");
    scanf("%d", &search_choice);

    switch (search_choice)
    {
    case 1:
        printf("Введите фамилию для поиска: ");
        scanf("%19s", search_string);
        for (i = 0; i < 4; i++)
        {
            if (partial_match(stud[i].famil, search_string))
            {
                printf("Найден студент: %s %s, факультет: %s, номер: %d\n",
                    stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
                found = 1;
            }
        }
        break;

    case 2:
        printf("Введите имя для поиска: ");
        scanf("%19s", search_string);
        for (i = 0; i < 4; i++)
        {
            if (partial_match(stud[i].name, search_string))
            {
                printf("Найден студент: %s %s, факультет: %s, номер: %d\n",
                    stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
                found = 1;
            }
        }
        break;

    case 3:
        printf("Введите номер зачетной книжки: ");
        scanf("%d", &search_nomzach);
        for (i = 0; i < 4; i++)
        {
            if (stud[i].Nomzach == search_nomzach)
            {
                printf("Найден студент: %s %s, факультет: %s, номер: %d\n",
                    stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
                found = 1;
            }
        }
        break;

    default:
        printf("Неверный выбор!\n");
        break;
    }

    if (!found && search_choice >= 1 && search_choice <= 4)
    {
        printf("Студент не найден!\n");
    }

    printf("\nДОП.ЗАДАНИЕ:\n\n");

    int matrix_size;
    printf("Введите размер квадратной матрицы: ");
    scanf("%d", &matrix_size);

    int** dynamic_matrix = (int**)malloc(matrix_size * sizeof(int*));
    for (i = 0; i < matrix_size; i++) {
        dynamic_matrix[i] = (int*)malloc(matrix_size * sizeof(int));
    }

    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++) {
            dynamic_matrix[i][j] = 2 + rand() % 4;
        }
    }

    for (i = 0; i < matrix_size; i++) {
        dynamic_matrix[i][i] = 0;
    }

    for (i = 0; i < matrix_size; i++) {
        for (j = i + 1; j < matrix_size; j++) {
            dynamic_matrix[j][i] = dynamic_matrix[i][j];
        }
    }

    printf("\nРезультирующая матрица:\n");
    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++) {
            printf("%3d ", dynamic_matrix[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < matrix_size; i++) {
        free(dynamic_matrix[i]);
    }
    free(dynamic_matrix);

    system("pause");
    return 0;
}