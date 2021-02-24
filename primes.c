#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <qc.h>

static size_t square_root(size_t x) {
    return (size_t) sqrt(x);
}

int main(int argc, char *argv[]) {
    qc_err *err = qc_err_new();
    qc_args* args = qc_args_new();
    qc_args_set_brief(args, "Compute all primes up to N");
    bool quiet;
    qc_args_flag(args, 'q', "quiet", &quiet, "Suppress output");
    size_t n;
    qc_args_unsigned_default(args, "N", 100, &n, "number to compute primes up to");
    if (qc_args_parse(args, argc, argv, err) == QC_FAILURE) {
        qc_err_fatal(err, "Failed to parse command line arguments");
    } else if (n < 2) {
        qc_err_set(err, "n should be greater or equal to 2");
        qc_err_fatal(err, "Wrong arguments passed");
    }
    bool* A = qc_malloc(n);
    for (size_t i = 0; i < n; ++i) A[i] = true;
    for (size_t i = 2; i < square_root(n); ++i) {
        if (A[i]) {
            for (size_t j = i * i; j < n; j += i) A[j] = false;
        }
    }
    if (!quiet) for (size_t i = 2; i < n; ++i) if (A[i]) printf("%zu\n", i);
    free(A);
    qc_args_free(args);
    qc_err_free(err);
}
