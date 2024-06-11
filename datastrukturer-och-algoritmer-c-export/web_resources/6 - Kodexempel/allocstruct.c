#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Line {
        char *string;           /* Pointer to the actual string */
        struct Line *next;      /* Pointer to next line */
};

int main(void)
{
        const char *s = "Hello";
        struct Line *p, *q;
        p = malloc(sizeof(*p));
        p->string = strdup(s);  /* strdup makes a dynamic copy of s */
        p->next = NULL;
        free(p->string);
        q = p->next;
        free(p);
        p = q;
        return 0;
}
