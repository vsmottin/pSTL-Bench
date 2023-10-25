#ifndef PSTL_BENCH_BENCHMARK_PREFIX_H
#define PSTL_BENCH_BENCHMARK_PREFIX_H

// #define XSTRINGIFY(s) STRINGIFY(s)
// #define STRINGIFY(s)  #s

#ifndef BENCHMARK_BACKEND
#define BENCHMARK_BACKEND unknown
#endif

#ifndef BENCHMARK_COMPILER
#define BENCHMARK_COMPILER unknown
#endif

// Macros to concatenate compiler name, threading backend and benchmark name to form a benchmark name
// args:
// - only the benchmark name, the backend and the compiler name are automatically added
// - the threading backend and the benchmark name, the compiler name is automatically added
#define BENCHMARK_NAME(benchmark) BENCHMARK_NAME_WITH_BACKEND(BENCHMARK_BACKEND, benchmark)

#define BENCHMARK_NAME_WITH_BACKEND(backend, benchmark) \
	BENCHMARK_NAME_WITH_BACKEND_AND_COMPILER(BENCHMARK_COMPILER, backend, benchmark)

#define BENCHMARK_NAME_WITH_BACKEND_AND_COMPILER(compiler, backend, benchmark) compiler "_" backend "_" benchmark

#endif //PSTL_BENCH_BENCHMARK_PREFIX_H
