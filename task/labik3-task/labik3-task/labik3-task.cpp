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

struct node* head_priority = NULL, * last_priority = NULL;  
struct node* head_queue = NULL, * last_queue = NULL;        
struct node* head_stack = NULL;                             

struct node* get_struct(void);
struct node* get_struct_with_priority(void);
void review_all(void);
void review_priority(void);
void review_queue(void);
void review_stack(void);
struct node* find(char* name);
void del_priority(char* name);
void del_queue(char* name);
void del_stack(char* name);

void priority_enqueue(void);
void enqueue(void);
void dequeue(void);
void push(void);
void pop(void);

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

void review_all(void)
{
    printf("\n=== ВСЕ СТРУКТУРЫ ДАННЫХ ===\n");

    printf("\n--- Приоритетная очередь ---\n");
    review_priority();

    printf("\n--- Очередь ---\n");
    review_queue();

    printf("\n--- Стек ---\n");
    review_stack();
}

void review_priority(void)
{
    struct node* struc = head_priority;
    if (head_priority == NULL)
    {
        printf("Приоритетная очередь пуста\n");
        return;
    }
    printf("Приоритетная очередь (сортировка по убыванию приоритета):\n");
    int position = 1;
    while (struc)
    {
        printf("%d. %s (приоритет: %d)\n", position++, struc->inf, struc->priority);
        struc = struc->next;
    }
}

void review_queue(void)
{
    struct node* struc = head_queue;
    if (head_queue == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }
    printf("Очередь:\n");
    int position = 1;
    while (struc)
    {
        printf("%d. %s\n", position++, struc->inf);
        struc = struc->next;
    }
}

void review_stack(void)
{
    struct node* struc = head_stack;
    if (head_stack == NULL)
    {
        printf("Стек пуст\n");
        return;
    }
    printf("Стек:\n");
    int position = 1;
    while (struc)
    {
        printf("%d. %s\n", position++, struc->inf);
        struc = struc->next;
    }
}

struct node* find(char* name)
{
    struct node* result = NULL;
    int found = 0;

    struct node* struc = head_priority;
    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            printf("Элемент '%s' найден в ПРИОРИТЕТНОЙ ОЧЕРЕДИ (приоритет: %d)\n", struc->inf, struc->priority);
            found = 1;
            result = struc;
        }
        struc = struc->next;
    }

    struc = head_queue;
    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            printf("Элемент '%s' найден в ОЧЕРЕДИ\n", struc->inf);
            found = 1;
            result = struc;
        }
        struc = struc->next;
    }

    struc = head_stack;
    while (struc)
    {
        if (strcmp(name, struc->inf) == 0)
        {
            printf("Элемент '%s' найден в СТЕКЕ\n", struc->inf);
            found = 1;
            result = struc;
        }
        struc = struc->next;
    }

    if (!found)
    {
        printf("Элемент '%s' не найден ни в одной структуре данных\n", name);
    }

    return result;
}

void del_priority(char* name)
{
    struct node* struc = head_priority;
    struct node* prev = NULL;
    int flag = 0;

    if (head_priority == NULL)
    {
        printf("Приоритетная очередь пуста\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        head_priority = struc->next;
        if (head_priority == NULL)
            last_priority = NULL;
        free(struc);
        printf("Элемент удален из приоритетной очереди\n");
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
            if (struc == last_priority)
                last_priority = prev;
            free(struc);
            printf("Элемент удален из приоритетной очереди\n");
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    if (flag == 0)
    {
        printf("Элемент не найден в приоритетной очереди\n");
    }
}

void del_queue(char* name)
{
    struct node* struc = head_queue;
    struct node* prev = NULL;
    int flag = 0;

    if (head_queue == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        head_queue = struc->next;
        if (head_queue == NULL)
            last_queue = NULL;
        free(struc);
        printf("Элемент удален из очереди\n");
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
            if (struc == last_queue)
                last_queue = prev;
            free(struc);
            printf("Элемент удален из очереди\n");
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    if (flag == 0)
    {
        printf("Элемент не найден в очереди\n");
    }
}

void del_stack(char* name)
{
    struct node* struc = head_stack;
    struct node* prev = NULL;
    int flag = 0;

    if (head_stack == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    if (strcmp(name, struc->inf) == 0)
    {
        flag = 1;
        head_stack = struc->next;
        free(struc);
        printf("Элемент удален из стека\n");
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
            free(struc);
            printf("Элемент удален из стека\n");
            return;
        }
        prev = struc;
        struc = struc->next;
    }

    if (flag == 0)
    {
        printf("Элемент не найден в стеке\n");
    }
}

void priority_enqueue(void)
{
    struct node* p = get_struct_with_priority();
    if (p == NULL) return;

    if (head_priority == NULL || p->priority > head_priority->priority)
    {
        p->next = head_priority;
        head_priority = p;
        if (last_priority == NULL)
        {
            last_priority = p;
        }
        printf("Элемент добавлен в приоритетную очередь\n");
        return;
    }

    struct node* current = head_priority;
    while (current->next != NULL && current->next->priority >= p->priority)
    {
        current = current->next;
    }

    p->next = current->next;
    current->next = p;

    if (p->next == NULL)
    {
        last_priority = p;
    }

    printf("Элемент добавлен в приоритетную очередь\n");
}

void enqueue(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;

    if (head_queue == NULL)
    {
        head_queue = p;
        last_queue = p;
    }
    else
    {
        last_queue->next = p;
        last_queue = p;
    }
    printf("Элемент добавлен в очередь\n");
}

void dequeue(void)
{
    if (head_queue == NULL)
    {
        printf("Очередь пуста\n");
        return;
    }

    struct node* temp = head_queue;
    printf("Извлечен элемент из очереди: %s\n", head_queue->inf);
    head_queue = head_queue->next;

    if (head_queue == NULL)
    {
        last_queue = NULL;
    }

    free(temp);
}

void push(void)
{
    struct node* p = get_struct();
    if (p == NULL) return;

    p->next = head_stack;
    head_stack = p;

    printf("Элемент добавлен в стек\n");
}

void pop(void)
{
    if (head_stack == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    struct node* temp = head_stack;
    printf("Извлечен элемент из стека: %s\n", head_stack->inf);
    head_stack = head_stack->next;

    free(temp);
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
        printf("1. Просмотр всех структур\n");
        printf("2. Поиск элемента по имени\n");
        printf("3. Удалить элемент\n");

        printf("\n--- Приоритетная очередь ---\n");
        printf("4. Добавить элемент\n");
        printf("5. Просмотреть\n");
        printf("6. Удалить элемент\n");

        printf("\n--- Очередь ---\n");
        printf("7. Добавить элемент\n");
        printf("8. Извлечь элемент\n");
        printf("9. Просмотреть\n");
        printf("10. Удалить элемент\n");

        printf("\n--- Стек ---\n");
        printf("11. Добавить элемент\n");
        printf("12. Извлечь элемент\n");
        printf("13. Просмотреть\n");
        printf("14. Удалить элемент\n");

        printf("0. Выход\n");
        printf("Выберите действие: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            review_all();
            break;
        case 2:
            printf("Введите имя для поиска: ");
            scanf("%s", name);
            find(name);
            break;
        case 3:
            printf("Введите имя для удаления: ");
            scanf("%s", name);
            del_priority(name);
            del_queue(name);
            del_stack(name);
            break;
        case 4:
            priority_enqueue();
            break;
        case 5:
            review_priority();
            break;
        case 6:
            printf("Введите имя для удаления из приоритетной очереди: ");
            scanf("%s", name);
            del_priority(name);
            break;
        case 7:
            enqueue();
            break;
        case 8:
            dequeue();
            break;
        case 9:
            review_queue();
            break;
        case 10:
            printf("Введите имя для удаления из очереди: ");
            scanf("%s", name);
            del_queue(name);
            break;
        case 11:
            push();
            break;
        case 12:
            pop();
            break;
        case 13:
            review_stack();
            break;
        case 14:
            printf("Введите имя для удаления из стека: ");
            scanf("%s", name);
            del_stack(name);
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