#include "list_2cell.h"

list *ListEmpty(void) {
    list *l=malloc(sizeof(*l));
    l->top=NULL;
    l->bottom=NULL;
    l->memFreeFunc=NULL;
}

bool ListIsempty(const list *l) {
    return l->top==NULL;
}

list_position ListFirst(const list *l) {
    return p->top;
}

list_position ListEnd(const list *l) {
    return NULL;
}

list_position ListNext(list_position p, const list *l) {
    if (p!=ListEnd(l))
        return p->next;
    else {
        fprintf(stderr, "Bad position");
        exit(1);
    }
}

list_position ListPrevious(list_position p, const list *l) {
    if (p!=ListFirst(l))
        return p->prev;
    else {
        fprintf(stderr, "Bad position");
        exit(1);
    }
}
