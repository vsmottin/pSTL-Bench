#pragma once

#include "pstl/utils/elem_t.h"

#define XSTRINGIFY(s) STRINGIFY(s)
#define STRINGIFY(s)  #s

#ifndef PSTL_BENCH_BACKEND
#define PSTL_BENCH_BACKEND unknown
#endif

#ifndef PSTL_BENCH_COMPILER
#define PSTL_BENCH_COMPILER unknown
#endif

// Macros to concatenate compiler name, threading backend and benchmark name to form a benchmark name
// args:
// - only the benchmark name, the backend and the compiler name are automatically added
// - the threading backend and the benchmark name, the compiler name is automatically added
#define PSTL_BENCH_BENCHMARK_NAME(benchmark) PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND(PSTL_BENCH_BACKEND, benchmark)

#define PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND(backend, benchmark) \
	PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND_AND_COMPILER(PSTL_BENCH_COMPILER, backend, benchmark)

#define PSTL_BENCH_BENCHMARK_NAME_WITH_BACKEND_AND_COMPILER(compiler, backend, benchmark) \
	compiler "-" backend "/" benchmark "/" XSTRINGIFY(PSTL_ELEM_T)
