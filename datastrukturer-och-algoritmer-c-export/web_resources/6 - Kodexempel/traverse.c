#include "dlist.h"

typedef void traverse_func(data);

void traverse(dlist *l,traverse_func f) {
   dlist_position p=dlist_first(l);
   while(!dlist_isEnd(l,p)) {
       f(dlist_inspect(l,p));
       p=dlist_next(l,p);
   }
}

void printInt(data d) {
   printf("%d ", *( (int *) d));
}

void printlnInt(data d) {
   printf("%d\n", *( (int *) d));
}

int main(void) {
   dlist *l=dlist_empty();
   dlist_setMemHandler(l,free);
   int *value;
   dlist_position p;
   value =malloc(sizeof(int));
   *value=0;
   p=dlist_insert(l, dlist_first(l), value);

   value =malloc(sizeof(int));
   *value=1;
   dlist_insert(l,p,value);
   
   printf("print_int\n");
   traverse(l,printInt);

   printf("\nprintln_int\n");
   traverse(l,printlnInt);

   dlist_free(l);
   return 0;
}
