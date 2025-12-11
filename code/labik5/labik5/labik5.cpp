#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// 1. Генерация матрицы
void generateMatrix(int n, float p, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                float r = (float)rand() / RAND_MAX;
                if (r < p) {
                    matrix[i][j] = 1;
                }
                else {
                    matrix[i][j] = 0;
                }
                matrix[j][i] = matrix[i][j];
            }
        }
    }
}

// 2. Определение размера графа
int graphSize(int n, int** matrix) {
    int edges = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] == 1) {
                edges++;
            }
        }
    }
    return edges;
}

// 3. Поиск изолированных, концевых и доминирующих вершин
void findVertices(int n, int** matrix, int* degrees,
    int* isolated, int* isolated_count,
    int* pendant, int* pendant_count,
    int* dominating, int* dominating_count) {

    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) {
            deg += matrix[i][j];
        }
        degrees[i] = deg;

        if (deg == 0) {
            isolated[*isolated_count] = i;
            (*isolated_count)++;
        }
        else if (deg == 1) {
            pendant[*pendant_count] = i;
            (*pendant_count)++;
        }

        if (deg == n - 1) {
            dominating[*dominating_count] = i;
            (*dominating_count)++;
        }
    }
}

// Вывод матрицы
void printMatrix(int n, int** matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Вывод массива
void printArray(int arr[], int count, const char* label) {
    printf("%s: ", label);
    if (count == 0) {
        printf("нет");
    }
    else {
        for (int i = 0; i < count; i++) {
            printf("%d", arr[i]);
            if (i < count - 1) printf(", ");
        }
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));

    int n;
    float p = 0.3;

    printf("Введите количество вершин графа: ");
    scanf("%d", &n);

    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    int* degrees = (int*)malloc(n * sizeof(int));
    int* isolated = (int*)malloc(n * sizeof(int));
    int* pendant = (int*)malloc(n * sizeof(int));
    int* dominating = (int*)malloc(n * sizeof(int));

    int isolated_count = 0;
    int pendant_count = 0;
    int dominating_count = 0;

    generateMatrix(n, p, matrix);

    printf("\n1. Матрица смежности графа G:\n");
    printMatrix(n, matrix);

    int size = graphSize(n, matrix);
    printf("\n2. Размер графа G (количество ребер): %d\n", size);

    findVertices(n, matrix, degrees,
        isolated, &isolated_count,
        pendant, &pendant_count,
        dominating, &dominating_count);

    printf("\n3. Степени вершин: ");
    for (int i = 0; i < n; i++) {
        printf("%d", degrees[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");

    printArray(isolated, isolated_count, "   Изолированные вершины");
    printArray(pendant, pendant_count, "   Концевые вершины");
    printArray(dominating, dominating_count, "   Доминирующие вершины");

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(degrees);
    free(isolated);
    free(pendant);
    free(dominating);

    return 0;
}