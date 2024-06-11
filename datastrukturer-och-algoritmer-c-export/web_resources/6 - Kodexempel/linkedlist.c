#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Line {
        char *string;           /* Pointer to the actual string */
        struct Line *next;      /* Pointer to next line */
};

int main(void)
{
        const char *s = "First", *t = "Second";
        struct Line *p;                 /* work pointer */
        struct Line *head = NULL;       /* points to first line in list */
        /* Line 1 */
        p = malloc(sizeof(*p));         /* allocate struct #1 */
        p->string = strdup(s);          /* make a dynamic copy of s */
        p->next = head;                 /* set pointer to next line */
        head = p;                       /* set head to point to this line */
        /* Line 2 */
        p = malloc(sizeof(*p));         /* allocate struct #2 */
        p->string = strdup(t);          /* make a dynamic copy of t */
        p->next = head;                 /* set pointer to next line */
        head = p;                       /* set head to point to this line */
        /* Print content of list, in reverse */
        while (head != NULL) {          /* while we have remaining lines */
                p = head;               /* look at the first one... */
                printf("%s\n", p->string); /* print string */
                free(p->string);        /* free string */
                head = p->next;         /* grab next line */
                free(p);                /* free the struct pointer */
        }
        return 0;
}
