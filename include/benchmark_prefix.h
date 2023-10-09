#ifndef PSTL_BENCH_BENCHMARK_PREFIX_H
#define PSTL_BENCH_BENCHMARK_PREFIX_H

#define xstr(s)        str(s)
#define str(s)         #s

#define DO_EXPAND(VAL) VAL##1
#define EXPAND(VAL)    DO_EXPAND(VAL)

// IS PREFIX SET AND NOT EMPTY
#if (defined(BENCHMARK_PREFIX) && (EXPAND(BENCHMARK_PREFIX) != 1))
#define PREFIX_DELIMITER _
#else // its empty or not set
#define BENCHMARK_PREFIX
#define PREFIX_DELIMITER
#endif // BENCHMARK_PREFIX

#define BENCHMARK_NAME(name) xstr(BENCHMARK_PREFIX) xstr(PREFIX_DELIMITER) name

#endif //PSTL_BENCH_BENCHMARK_PREFIX_H
