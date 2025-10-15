#pragma once
#include <stddef.h>
struct node
{
    int value;
    struct node* next;
    struct node* prev;
};
typedef struct node Node;
struct list
{
    Node* head;
    Node* tail;
    size_t size;
};
typedef struct list List;
List init(size_t n);
void print(const List* pl);
void push_back(List* pl, int value);
int pop_back(List* pl);
void push_front(List* pl, int value);
int pop_front(List* pl);
Node* erase(List* pl, Node* p);
void splice(List* plist, Node* p, List* pother);
void destroy(List* pl);
void advance(Node** pp, size_t n);