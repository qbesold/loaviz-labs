#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <queue>
#include <limits.h>

using namespace std;

#define INF INT_MAX

void BFSDweighted(int** G, int numG, int* dist, int s) {
    queue<int> q;
    int v;

    for (int i = 0; i < numG; i++) {
        dist[i] = INF;
    }

    q.push(s);
    dist[s] = 0;

    printf("\nПуть из вершины %d: ", s);

    while (!q.empty()) {
        v = q.front();
        q.pop();
        printf("%3d", v);

        for (int i = 0; i < numG; i++) {
            if (G[v][i] > 0) {
                int newDist = dist[v] + G[v][i];
                if (newDist < dist[i]) {
                    dist[i] = newDist;
                    q.push(i);
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    int** G;
    int** dist;
    int numG;
    int* ecc;
    int vert;

    printf("Введите количество вершин графа: ");
    scanf("%d", &numG);

    ecc = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    dist = (int**)malloc(numG * sizeof(int*));

    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
        dist[i] = (int*)malloc(numG * sizeof(int));
    }

    srand(time(NULL));

    for (int i = 0; i < numG; i++) {
        for (int j = i; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0;
            }
            else {
                G[i][j] = G[j][i] = (rand() % 100 < 70) ? (rand() % 10 + 1) : 0;
            }
        }
    }

    printf("\nМатрица смежности (весов):\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%4d", G[i][j]);
        }
        printf("\n");
    }

    printf("\nВычисление кратчайших расстояний из каждой вершины:\n");
    for (int i = 0; i < numG; i++) {
        BFSDweighted(G, numG, dist[i], i);
    }

    printf("\n\nМатрица расстояний:\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            if (dist[i][j] == INF) {
                printf("%4s", "INF");
            }
            else {
                printf("%4d", dist[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nВведите стартовую вершину для вывода расстояний: ");
    scanf("%d", &vert);

    if (vert >= 0 && vert < numG) {
        printf("\nРасстояния от вершины %d до остальных:\n", vert);
        for (int i = 0; i < numG; i++) {
            if (dist[vert][i] == INF) {
                printf("До вершины %d: недостижима\n", i);
            }
            else {
                printf("До вершины %d: %d\n", i, dist[vert][i]);
            }
        }
    }

    printf("\nЭксцентриситет вершин:\n");
    for (int i = 0; i < numG; i++) {
        ecc[i] = 0;
        for (int j = 0; j < numG; j++) {
            if (dist[i][j] != INF && dist[i][j] > ecc[i]) {
                ecc[i] = dist[i][j];
            }
        }
        printf("Вершина %d: %d\n", i, ecc[i]);
    }

    int diameter = 0;
    int radius = INF;

    for (int i = 0; i < numG; i++) {
        if (ecc[i] > diameter && ecc[i] != INF) diameter = ecc[i];
        if (ecc[i] < radius && ecc[i] > 0) radius = ecc[i];
    }

    printf("\nДиаметр графа: %d\n", diameter);
    printf("Радиус графа: %d\n", radius);

    printf("Центральные вершины (эксцентриситет = радиусу): ");
    for (int i = 0; i < numG; i++) {
        if (ecc[i] == radius) {
            printf("%d ", i);
        }
    }

    printf("\nПериферийные вершины (эксцентриситет = диаметру): ");
    for (int i = 0; i < numG; i++) {
        if (ecc[i] == diameter) {
            printf("%d ", i);
        }
    }
    printf("\n");

    for (int i = 0; i < numG; i++) {
        free(G[i]);
        free(dist[i]);
    }
    free(G);
    free(dist);
    free(ecc);

    printf("\nНажмите любую клавишу для выхода...");
    _getch();

    return 0;
}