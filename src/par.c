#include <stdlib.h>

#include <cilk/cilk.h>

#include "../include/par.h"

static void swap(int *a, int *b) {
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

int sort_par(int *array, int size) {
    int x;
    int l;
    int r1;
    int r2;

    if (size <= 1) {
        return 0;
    }

    swap(array + (size >> 1), array + size - 1);
    x = array[size - 1];

    l = 0;
    for (r1 = 0; r1 < size - 1; ++r1) {
        if (array[r1] < x) {
            swap(array + (l++), array + r1);
        }
    }

    swap(array + l, array + size - 1);
    r1 = l + 1;
    for (r2 = l + 1; r2 < size; ++r2) {
        if (array[r2] == x) {
            swap(array + (r1++), array + r2);
        }
    }

    cilk_scope {
        cilk_spawn sort_par(array, l);
        sort_par(array + r1, size - r1);
    }

    return 0;
}