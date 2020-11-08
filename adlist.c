#include <stdlib.h>
#include <stdio.h>

typedef struct listNode
{
    struct listNode *prev;
    struct listNode *next;
    int value;
} listNode;

typedef struct list
{
    listNode *head;
    listNode *tail;
    unsigned int len;
} list;

list* listCreate()
{
    list* l = (list*)malloc(sizeof(struct list));
    l->head = NULL;
    l->tail = NULL;
    l->len = 0;
}

list *listAddNodeHead(list *list, int value)
{
    listNode* node = malloc(sizeof(struct listNode));
    node->value = value;

    if (list->len == 0) {
        node->next = node->prev = NULL;
        list->head = list->tail = node;
    } else {
        node->next = list->head;
        node->prev = NULL;
        list->head->prev = node;
        list->head = node;
    }
    list->len++;
    return list;
}

list *listAddNodeTail(list *list, int value)
{
    listNode* node = malloc(sizeof(struct listNode));
    node->value = value;

    if (list->len == 0) {
        node->next = node->prev = NULL;
        list->head = list->tail = node;
    } else {
        node->next = NULL;
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    list->len++;
    return list;
}

listNode* listSearchKey(list *list, int key)
{
    listNode *p = list->head;
    while(p != NULL) {
        if (p->value == key) {
            return p;
        } else {
            p = p->next;
        }
    }
    return p;
}


void listDelNode(list *list, listNode *node)
{
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    list->len--;
}

void listShow(list *list)
{
    listNode *p = list->head;
    while (p != NULL) {
        if (p->next != NULL) {
            printf("%d->", p->value);
        } else {
            printf("%d\n", p->value);
        }
        p = p->next;
    }
}

int main()
{
    list *l = listCreate();
    listAddNodeHead(l, 1);
    listAddNodeHead(l, 2);
    listAddNodeHead(l, 3);
    listShow(l);

    listNode *n = listSearchKey(l, 2);
    listDelNode(l, n);
    listShow(l);

    list *l2 = listCreate();
    listAddNodeTail(l2, 4);
    listAddNodeTail(l2, 5);
    listShow(l2);

    return 0;
}
