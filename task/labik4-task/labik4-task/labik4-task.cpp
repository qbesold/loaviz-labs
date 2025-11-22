#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Ошибка выделения памяти");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;
        return r;
    }

    if (data > r->data)
        r->right = CreateTree(r->right, data);
    else
        r->left = CreateTree(r->left, data);

    return r;
}

int findLastOccurrenceLevel(struct Node* r, int key, int level, int* lastLevel)
{
    if (r == NULL)
        return *lastLevel;

    if (r->data == key)
        *lastLevel = level;

    findLastOccurrenceLevel(r->left, key, level + 1, lastLevel);
    findLastOccurrenceLevel(r->right, key, level + 1, lastLevel);

    return *lastLevel;
}

struct Node* search(struct Node* r, int key)
{
    if (r == NULL || r->data == key)
        return r;

    if (r->data < key)
        return search(r->right, key);

    return search(r->left, key);
}

int countOccurrences(struct Node* r, int key)
{
    if (r == NULL)
        return 0;

    int count = 0;
    if (r->data == key)
        count = 1;

    return count + countOccurrences(r->left, key) + countOccurrences(r->right, key);
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL)
    {
        return;
    }

    print_tree(r->left, l + 1);

    for (int i = 0; i < l; i++)
    {
        printf("   ");
    }
    printf("%d\n", r->data);

    print_tree(r->right, l + 1);
}

void free_tree(struct Node* r)
{
    if (r == NULL) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}

int main()
{
    setlocale(LC_ALL, "");
    int D, start = 1;

    root = NULL;
    printf("ЛАБОРАТОРНАЯ РАБОТА №4\n\n");
    printf("-1 - окончание построения дерева\n\n");

    while (start)
    {
        printf("Введите число: ");
        scanf_s("%d", &D);
        if (D == -1)
        {
            printf("Построение дерева окончено\n\n");
            start = 0;
        }
        else
            root = CreateTree(root, D);
    }

    printf("Дерево:\n");
    print_tree(root, 0);
    printf("\n");

    printf("Введите число для поиска: ");
    scanf_s("%d", &D);

    struct Node* result = search(root, D);
    if (result != NULL)
    {
        printf("Элемент %d найден в дереве.\n", D);

        int lastLevel = -1;
        findLastOccurrenceLevel(root, D, 0, &lastLevel);
        printf("Уровень последнего вхождения элемента %d: %d\n", D, lastLevel);
    }
    else
    {
        printf("Элемент %d не найден в дереве.\n", D);
    }

    int occurrences = countOccurrences(root, D);
    printf("Число вхождений элемента %d в дереве: %d\n", D, occurrences);

    free_tree(root);

    return 0;
}