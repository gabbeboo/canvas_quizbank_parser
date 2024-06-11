#include <stdlib.h>
#include <stdio.h>
#include "int_list_2cell.h"

struct two_cell {
    struct two_cell *next;
    struct two_cell *prev;
    int val;
};

struct list {
    two_cell *head;
    two_cell *tail;
};

list *list_empty(void)
{
    list *l=malloc(sizeof(list)) ;
    l->head=malloc(sizeof(two_cell));
    l->tail=malloc(sizeof(two_cell));
    l->head->prev=NULL;
    l->head->next=l->tail;
    l->tail->prev=l->head;
    l->tail->next=NULL;
    return l;
}

bool list_isempty(const list *l)
{
    return l->head->next==l->tail;
}

int list_inspect(const list *l,const list_position pos)
{
    return pos->val;
}

list_position list_first(const list *l)
{
    return l->head->next;
}

list_position list_end(const list *l)
{
    return l->tail;
}

list_position list_next(const list *l,
                        const list_position p)
{
    return p->next;
}

list_position list_prev(const list *l,
                        const list_position p)
{
    return p->prev;
}

list_position list_insert(list *l,int val,
                          const list_position p)
{
    list_position q=malloc(sizeof(two_cell));
    q->val=val;
    q->next=p;
    q->prev=p->prev;
    p->prev=q;
    q->prev->next=q;
    return q;
}

list_position list_remove(list *l,const list_position p)
{
    list_position q=p->next;
    p->prev->next=p->next;
    p->next->prev=p->prev;
    free(p);
    return q;
}

void list_free(list *l)
{
    list_position p=list_first(l);

    while (!list_isempty(l)) {
        p=list_remove(l,p);
    }
    free(l->head);
    free(l->tail);
    free(l);
    return;
}

