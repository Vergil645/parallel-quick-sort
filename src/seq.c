#include "../include/seq.h"

static void swap(int *a, int *b) {
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort_seq(int *array, int size) {
    int x;
    int l;
    int r1;
    int r2;

    if (size <= 1) {
        return;
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

    sort_seq(array, l);
    sort_seq(array + r1, size - r1);
}