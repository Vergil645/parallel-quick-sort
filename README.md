# parallel-quick-sort

Sequential and parallel implementation of a [Quicksort](https://en.wikipedia.org/wiki/Quicksort) algorithm.

## Requirements

You need to install [OpenCilk](https://www.opencilk.org/) to compile and run parallel version of an algorithm.

## Build

1. Configure a build tree:
   ```sh
   $ ./configure.sh <opencilk path>
   ```
2. Build and run unit tests:
   ```sh
   $ ./build.sh
   ```

## Run

Sequential and parallel *Quicksort* implementations are compiled into a static library [libsort.a](./lib/libsort.a) (**Linux**), which you can link to your code.

## Comparison of implementations

[compare](./src/compare.c) compares execution time of both (sequential and parallel) implementations on **5** random arrays of size **100'000'000**.

Parallel implementation on **4** processes is **~3 times faster** than sequential implementation:

```sh
$ CILK_NWORKERS=4 ./bin/compare
run[1] SUCCESS: sort_par is 3.017 times faster than sort_seq
run[2] SUCCESS: sort_par is 3.099 times faster than sort_seq
run[3] SUCCESS: sort_par is 3.034 times faster than sort_seq
run[4] SUCCESS: sort_par is 3.063 times faster than sort_seq
run[5] SUCCESS: sort_par is 3.001 times faster than sort_seq
RESULT: sort_par is faster than sort_seq on average 3.043 times
```

## Notes

* All binary files (in ./<...>/bin and ./<...>/lib directories) are compiled on **Debian 6.1.55-1 x86_64 GNU/Linux**.