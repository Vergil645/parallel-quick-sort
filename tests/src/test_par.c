#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../include/par.h"

#define TEST_CASES 5

static int sizes[TEST_CASES] = {1, 10, 100, 10000, 1000000};

static int check_array_is_sorted(int *array, int size) {
    int i;

    for (i = 0; i < size - 1; ++i) {
        if (array[i] > array[i + 1]) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    int test_case;
    int size;
    int *array;
    int i;
    int is_succ = 1;
    int failures_count = 0;
    int sort_ret;
    int ret;

    srand(time(NULL));

    for (test_case = 0; test_case < TEST_CASES; ++test_case) {
        size = sizes[test_case];

        array = (int *) malloc(sizeof(int) * size);
        if (array == NULL) {
            printf("test[%d] FAIL: cannot allocate array of size %d\n", test_case, size);
            return 100;
        }

        for (i = 0; i < size; ++i) {
            array[i] = rand();
        }

        sort_ret = sort_par(array, size);

        if (sort_ret == 0 && check_array_is_sorted(array, size)) {
            printf("test[%d] SUCCESS\n", test_case);
        } else {
            printf("test[%d] FAIL\n", test_case);
            is_succ = 0;
            ++failures_count;
        }

        free(array);
    }

    if (is_succ) {
        printf("ALL TESTS PASSED\n");
        ret = 0;
    } else {
        printf("%d TESTS FAILED\n", failures_count);
        ret = 1;
    }

    return ret;
}