// Не сказано как назвать, поэтому назвал по номеру задачи.
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
static void* ecmalloc(size_t n) {
    void* p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    return p;
}
#define DECLARE_LIST(type, format) \
struct node_##type { \
    type value; \
    struct node_##type* next; \
    struct node_##type* prev; \
}; \
typedef struct node_##type Node_##type; \
\
struct list_##type { \
    Node_##type* head; \
    Node_##type* tail; \
    size_t size; \
}; \
typedef struct list_##type List_##type; \
\
void list_##type##_push_back(List_##type* pl, type value); \
void list_##type##_push_front(List_##type* pl, type value); \
\
List_##type list_##type##_init(size_t n) { \
    List_##type list; \
    list.head = NULL; \
    list.tail = NULL; \
    list.size = 0; \
    for (size_t i = 0; i < n; i++) { \
        list_##type##_push_back(&list, (type)0); \
    } \
    return list; \
} \
\
void list_##type##_print(const List_##type* pl) { \
    Node_##type* current = pl->head; \
    while (current != NULL) { \
        printf(format " ", current->value); \
        current = current->next; \
    } \
    printf("\n"); \
} \
\
void list_##type##_push_back(List_##type* pl, type value) { \
    Node_##type* new_node = (Node_##type*)ecmalloc(sizeof(Node_##type)); \
    new_node->value = value; \
    new_node->next = NULL; \
    new_node->prev = pl->tail; \
    if (pl->tail != NULL) { \
        pl->tail->next = new_node; \
    } \
    pl->tail = new_node; \
    if (pl->head == NULL) { \
        pl->head = new_node; \
    } \
    pl->size++; \
} \
\
type list_##type##_pop_back(List_##type* pl) { \
    if (pl->tail == NULL) { \
        fprintf(stderr, "Error: empty list\n"); \
        exit(1); \
    } \
    Node_##type* last = pl->tail; \
    type value = last->value; \
    pl->tail = last->prev; \
    if (pl->tail != NULL) { \
        pl->tail->next = NULL; \
    } else { \
        pl->head = NULL; \
    } \
    free(last); \
    pl->size--; \
    return value; \
} \
\
void list_##type##_push_front(List_##type* pl, type value) { \
    Node_##type* new_node = (Node_##type*)ecmalloc(sizeof(Node_##type)); \
    new_node->value = value; \
    new_node->prev = NULL; \
    new_node->next = pl->head; \
    if (pl->head != NULL) { \
        pl->head->prev = new_node; \
    } \
    pl->head = new_node; \
    if (pl->tail == NULL) { \
        pl->tail = new_node; \
    } \
    pl->size++; \
} \
\
type list_##type##_pop_front(List_##type* pl) { \
    if (pl->head == NULL) { \
        fprintf(stderr, "Error: empty list\n"); \
        exit(1); \
    } \
    Node_##type* first = pl->head; \
    type value = first->value; \
    pl->head = first->next; \
    if (pl->head != NULL) { \
        pl->head->prev = NULL; \
    } else { \
        pl->tail = NULL; \
    } \
    free(first); \
    pl->size--; \
    return value; \
} \
\
Node_##type* list_##type##_erase(List_##type* pl, Node_##type* p) { \
    if (p == NULL) return NULL; \
    if (p->prev != NULL) { \
        p->prev->next = p->next; \
    } else { \
        pl->head = p->next; \
    } \
    if (p->next != NULL) { \
        p->next->prev = p->prev; \
    } else { \
        pl->tail = p->prev; \
    } \
    Node_##type* next_node = p->next; \
    free(p); \
    pl->size--; \
    return next_node; \
} \
\
void list_##type##_splice(List_##type* plist, Node_##type* p, List_##type* pother) { \
    if (pother->head == NULL) return; \
    if (p == NULL) { \
        if (plist->tail != NULL) { \
            plist->tail->next = pother->head; \
            pother->head->prev = plist->tail; \
        } else { \
            plist->head = pother->head; \
        } \
        plist->tail = pother->tail; \
    } else if (p == plist->head) { \
        pother->tail->next = plist->head; \
        plist->head->prev = pother->tail; \
        plist->head = pother->head; \
    } else { \
        p->prev->next = pother->head; \
        pother->head->prev = p->prev; \
        pother->tail->next = p; \
        p->prev = pother->tail; \
    } \
    plist->size += pother->size; \
    pother->head = NULL; \
    pother->tail = NULL; \
    pother->size = 0; \
} \
\
void list_##type##_destroy(List_##type* pl) { \
    Node_##type* current = pl->head; \
    while (current != NULL) { \
        Node_##type* next = current->next; \
        free(current); \
        current = next; \
    } \
    pl->head = NULL; \
    pl->tail = NULL; \
    pl->size = 0; \
} \
\
void list_##type##_advance(Node_##type** pp, size_t n) { \
    Node_##type* current = *pp; \
    for (size_t i = 0; i < n && current != NULL; i++) { \
        current = current->next; \
    } \
    *pp = current; \
}