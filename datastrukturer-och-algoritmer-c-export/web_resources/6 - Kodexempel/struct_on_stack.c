#include <stdio.h>
typedef struct node {
    int val;
    struct node *next;
} node;
void print_list(node *p)
{
    printf("list = ( ");
    while (p!=NULL) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf(")\n");
}
int main(void)
{
    node n1;
    node n2;
    node *head = NULL;
    print_list(head);
    n1.val = 22;
    n1.next = head;
    head = &n1;
    print_list(head);
    n2.val = 19;
    n2.next = head;
    head = &n2;
    print_list(head);
    return 0;
}

typedef struct abstract_node {
    void *val;
    struct abstract_node *next;
} abstract_node;
