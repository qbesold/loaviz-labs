#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// 1. Генерация матрицы с возможностью петель
void generateMatrix(int n, int** matrix) {
    float p_edge = 0.0f;
    float p_loop = 0.5f;

    for (int i = 0; i < n; i++) {
        // Генерация петли
        float r_loop = (float)rand() / RAND_MAX;
        if (r_loop < p_loop) {
            matrix[i][i] = 1;
        }
        else {
            matrix[i][i] = 0;
        }

        for (int j = i + 1; j < n; j++) {
            float r_edge = (float)rand() / RAND_MAX;
            if (r_edge < p_edge) {
                matrix[i][j] = 1;
            }
            else {
                matrix[i][j] = 0;
            }
            matrix[j][i] = matrix[i][j];
        }
    }
}

// 2. Определение размера графа с учетом петель
int graphSize(int n, int** matrix) {
    int edges = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] == 1) {
                edges++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 1) {
            edges++;
        }
    }

    return edges;
}

// 3. Поиск изолированных, концевых и доминирующих вершин с учетом петель
void findVertices(int n, int** matrix, int* degrees,
    int* isolated, int* isolated_count,
    int* pendant, int* pendant_count,
    int* dominating, int* dominating_count) {

    for (int i = 0; i < n; i++) {
        int deg = 0;

        for (int j = 0; j < n; j++) {
            if (i == j) {
                deg += matrix[i][i] * 2;
            }
            else {
                deg += matrix[i][j];
            }
        }

        degrees[i] = deg;

        int connections_to_others = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && matrix[i][j] == 1) {
                connections_to_others = 1;
                break;
            }
        }

        if (connections_to_others == 0 && matrix[i][i] == 0) {
            isolated[*isolated_count] = i;
            (*isolated_count)++;
        }

        if (deg == 1) {
            pendant[*pendant_count] = i;
            (*pendant_count)++;
        }

        int connected_to_all = 1;
        for (int j = 0; j < n; j++) {
            if (i != j && matrix[i][j] == 0) {
                connected_to_all = 0;
                break;
            }
        }

        if (connected_to_all) {
            dominating[*dominating_count] = i;
            (*dominating_count)++;
        }
    }
}

// Вывод матрицы с выделением петель
void printMatrix(int n, int** matrix) {
    printf("   ");
    for (int j = 0; j < n; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%2d ", i);
        for (int j = 0; j < n; j++) {
            if (i == j && matrix[i][j] == 1) {
                printf("[1]");
            }
            else {
                printf(" %d ", matrix[i][j]);
            }
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

// Инфа о петлях
void printLoops(int n, int** matrix) {
    printf("Петли: ");
    int has_loops = 0;
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 1) {
            if (has_loops) printf(", ");
            printf("%d", i);
            has_loops = 1;
        }
    }
    if (!has_loops) printf("нет");
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(NULL));

    int n;

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

    generateMatrix(n, matrix);

    printf("\n1. Матрица смежности графа G:\n");
    printMatrix(n, matrix);

    printLoops(n, matrix);

    int size = graphSize(n, matrix);
    printf("\n2. Размер графа G (количество ребер): %d\n", size);

    findVertices(n, matrix, degrees,
        isolated, &isolated_count,
        pendant, &pendant_count,
        dominating, &dominating_count);

    printf("\n3. Степени вершин (петли +2):\n");
    for (int i = 0; i < n; i++) {
        printf("   Вершина %d: степень = %d", i, degrees[i]);
        if (matrix[i][i] == 1) {
            printf(" (есть петля)");
        }
        printf("\n");
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