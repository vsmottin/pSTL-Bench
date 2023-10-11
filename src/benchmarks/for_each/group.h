#ifndef PSTL_BENCH_FOR_EACH_GROUP_H
#define PSTL_BENCH_FOR_EACH_GROUP_H

#include "for_each_exponential/group.h"
#include "for_each_linear/group.h"
#include "for_each_linear_mandelbrot/group.h"
#include "for_each_quadratic/group.h"
#include "for_each_quadratic_mandelbrot/group.h"

#ifdef ONLY_GPU


#define NESTED_PARALLELISM_GROUP FOR_EACH_LINEAR_MANDELBROT_WRAPPER


#else

// Register the function as a benchmark
#define FOR_EACH_GROUP                                                   \
	FOR_EACH_LINEAR_GROUP                                                \
	FOR_EACH_LINEAR_MANDELBROT_GROUP                                     \
	FOR_EACH_QUADRATIC_GROUP                                             \
	FOR_EACH_QUADRATIC_MANDELBROT_GROUP(std::execution::parallel_policy) \
	FOR_EACH_EXPONENTIAL_GROUP

#endif

#endif //PSTL_BENCH_FOR_EACH_GROUP_H
