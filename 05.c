#include <stdio.h>
struct node
{
    int value;
    struct node* ptr;
};
typedef struct node Node;
int main()
{
    Node first, second, third;
    first.value = 100;
    second.value = 200;
    third.value = 300;
    first.ptr = &second;
    second.ptr = &third;
    third.ptr = &first;
    Node* current = &first;
    while (1) {
        printf("%d ", current->value);
        current = current->ptr;
    }
    return 0;
}