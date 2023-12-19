#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "../include/sort.h"

#define USECS_IN_SEC 1000000

#define RUN_COUNT  5
#define ARRAY_SIZE 100000000

static int check_array_is_sorted(int *array, int size) {
    int i;

    for (i = 0; i < size - 1; ++i) {
        if (array[i] > array[i + 1]) {
            return 0;
        }
    }

    return 1;
}

static double get_diff_secs(struct timeval begin, struct timeval end) {
    return (double) (end.tv_usec - begin.tv_usec) / USECS_IN_SEC + (double) (end.tv_sec - begin.tv_sec);
}

int main(void) {
    int run_no;
    int size;
    int *array_orig;
    int *array_copy;
    int i;
    struct timeval begin;
    struct timeval end;
    double seq_time;
    double par_time;
    double ratio[RUN_COUNT];
    double ratio_sum;
    double ratio_avg;
    int ret;

    srand(time(NULL));

    ratio_sum = 0;
    for (run_no = 0; run_no < RUN_COUNT; ++run_no) {
        size = ARRAY_SIZE;

        array_orig = (int *) malloc(sizeof(int) * size);
        if (array_orig == NULL) {
            printf("run[%d] FAIL: cannot allocate array of size %d\n", run_no + 1, size);
            return 101;
        }

        array_copy = (int *) malloc(sizeof(int) * size);
        if (array_copy == NULL) {
            printf("run[%d] FAIL: cannot allocate array of size %d\n", run_no + 1, size);
            free(array_orig);
            return 102;
        }

        for (i = 0; i < size; ++i) {
            array_orig[i] = rand();
            array_copy[i] = array_orig[i];
        }

        gettimeofday(&begin, NULL);
        sort_seq(array_orig, size);
        gettimeofday(&end, NULL);
        seq_time = get_diff_secs(begin, end);

        gettimeofday(&begin, NULL);
        ret = sort_par(array_copy, size);
        gettimeofday(&end, NULL);
        par_time = get_diff_secs(begin, end);

        ratio[run_no] = (double) seq_time / par_time;
        ratio_sum += ratio[run_no];

        if (ret != 0) {
            printf("run[%d] FAIL: sort_par exit with non-zero code %d\n", run_no + 1, ret);
            free(array_copy);
            free(array_orig);
            return ret;
        }

        if (!check_array_is_sorted(array_orig, size)) {
            printf("run[%d] FAIL: array is not sorted after execution of sort_seq\n", run_no + 1);
            free(array_copy);
            free(array_orig);
            return 1;
        }

        if (!check_array_is_sorted(array_copy, size)) {
            printf("run[%d] FAIL: array is not sorted after execution of sort_par\n", run_no + 1);
            free(array_copy);
            free(array_orig);
            return 2;
        }

        free(array_copy);
        free(array_orig);

        printf("run[%d] SUCCESS: sort_par is %.3f times faster than sort_seq\n", run_no + 1, ratio[run_no]);
    }

    ratio_avg = ratio_sum / RUN_COUNT;
    printf("RESULT: sort_par is faster than sort_seq on average %.3f times\n", ratio_avg);

    return 0;
}