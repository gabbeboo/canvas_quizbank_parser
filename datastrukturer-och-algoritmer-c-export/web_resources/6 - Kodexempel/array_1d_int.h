#ifndef __ARRAY_1D_INT_H
#define __ARRAY_1D_INT_H

#include <stdbool.h>

typedef struct array array;
typedef void (*array_callback) (void *);

array *array_create(int low, int high);

void array_set_value(array * s, int pos, int val);
int array_inspect_value(const array * a, int pos);
bool array_has_value(const array * a, int pos);

int array_high(const array * a);
int array_low(const array * a);

void array_kill(array * a);

void array_print(const array * a, array_callback print_func);
#endif
