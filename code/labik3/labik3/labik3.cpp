#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node
{
    char inf[256];
    int priority;
    struct node* next;
};

struct node* head = NULL, * last = NULL;

struct node* get_struct(void);
struct node* get_struct_with_priority(void);
void spstore(void);
void review(void);
struct node* find(char* name);
void del(char* name);

void priority_enqueue(void);

void enqueue(void);
void dequeue(void);
void view_queue(void);

void push(void);
void pop(void);
void view_stack(void);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf("%s", s);
    if (*s == 0)
    {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }
    strcpy(p->inf, s);
    p->priority = 0;
    p->next = NULL;

    return p;
}

struct node* get_struct_with_priority(void)
{
    struct node* p = NULL;
    char s[256];
    int pr;

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: ");
    scanf("%s", s);
    if (*s == 0)
    {
        printf("Запись не была произведена\n");
        free(p);
        return NULL;
    }

    printf("Введите приоритет (целое число): ");
    scanf("%d", &pr);

    strcpy(p->inf, s);
    p->priority = pr;
    p->next = NULL;

    return p;
}

void review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Список пуст\n");
    }
    while (struc)
    {
        printf("Имя - %s", struc->inf);
        if (struc->priority != 0)
            printf(", Приоритет - %d", struc->priority);
        printf("\n");
        struc = struc->next;
    }
    return;
}


void del(char* name)
{
    struct node* struc = head;
    struct node* prev = NULL;
    int flag = 0;

    if (head == NULL)
    {
        printf("Список пуст\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        head = struc->next;
        if (head == NULL)
            last = NULL;
        free(struc);
        printf("Элемент удален\n");
        return;
    }

    prev = struc;
    struc = struc->next;

    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            flag = 1;
            prev->next = struc->next;
            if (struc == last)
                last = prev;
            free(struc);
            printf("Элемент удален\n");
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    if (flag == 0)
    {
        printf("Элемент не найден\n");
    }
}

void priority_enqueue(void)
{
    struct node* p = get_struct_with_priority();
    if (p == NULL) return;


    if (head == NULL || p->priority > head->priority)
    {
        p->next = head;
        head = p;
        if (last == NULL)
        {
            last = p;
        }
        printf("Элемент добавлен в приоритетную очередь\n");
        return;
    }

    struct node* current = head;
    while (current->next != NULL && current->next->priority >= p->priority)
    {
        current = current->next;
    }


    p->next = current->next;
    current->next = p;


    if (p->next == NULL)
    {
        last = p;
    }

    printf("Элемент добавлен в приоритетную очередь\n");
}


void enqueue(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;

    if (head == NULL)
    {
        head = p;
        last = p;
    }
    else
    {
        last->next = p;
        last = p;
    }
    printf("Элемент добавлен в очередь\n");
}

void dequeue(void)
{
    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    struct node* temp = head;
    printf("Извлечен элемент: %s\n", head->inf);
    head = head->next;

    if (head == NULL)
    {
        last = NULL;
    }

    free(temp);
}

void view_queue(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    printf("Содержимое очереди:\n");
    int position = 1;
    while (struc)
    {
        printf("%d. %s\n", position++, struc->inf);
        struc = struc->next;
    }
}


void push(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;

    p->next = head;
    head = p;

    if (last == NULL)
    {
        last = p;
    }

    printf("Элемент добавлен в стек\n");
}

void pop(void)
{
    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    struct node* temp = head;
    printf("Извлечен элемент: %s\n", head->inf);
    head = head->next;

    if (head == NULL)
    {
        last = NULL;
    }

    free(temp);
}

void view_stack(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    printf("Содержимое стека:\n");
    int position = 1;
    while (struc)
    {
        printf("%d. %s\n", position++, struc->inf);
        struc = struc->next;
    }
}


int main(void)
{
    setlocale(LC_ALL, "Russian");

    int choice;
    char name[256];

    printf("Лабораторная работа №3: Динамические списки\n");

    while (1)
    {
        printf("\n=== ГЛАВНОЕ МЕНЮ ===\n");
        printf("1. Просмотр всего списка\n");
        printf("2. Удалить элемент\n");
        printf("\n--- Приоритетная очередь ---\n");
        printf("3. Добавить элемент в приоритетную очередь\n");
        printf("\n--- Очередь ---\n");
        printf("4. Добавить элемент в очередь\n");
        printf("5. Извлечь элемент из очереди\n");
        printf("6. Просмотреть очередь\n");
        printf("\n--- Стек ---\n");
        printf("7. Добавить элемент в стек\n");
        printf("8. Извлечь элемент из стека\n");
        printf("9. Просмотреть стек\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            review();
            break;
        case 2:
            printf("Введите имя для удаления: ");
            scanf("%s", name);
            del(name);
            break;
        case 3:
            priority_enqueue();
            break;
        case 4:
            enqueue();
            break;
        case 5:
            dequeue();
            break;
        case 6:
            view_queue();
            break;
        case 7:
            push();
            break;
        case 8:
            pop();
            break;
        case 9:
            view_stack();
            break;
        case 0:
            printf("Выход из программы...\n");
            return 0;
        default:
            printf("Неверный выбор! Попробуйте снова.\n");
        }
    }

    return 0;
}