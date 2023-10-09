#ifndef PSTL_BENCH_B1_GROUP_H
#define PSTL_BENCH_B1_GROUP_H

#include "b1_1_for_each_linear/b1_1_group.h"
#include "b1_2_for_each_linear_mandelbrot/b1_2_group.h"
#include "b1_3_for_each_quadratic/b1_3_group.h"
#include "b1_4_for_each_quadratic_mandelbrot/b1_4_group.h"
#include "b1_5_for_each_exponential/b1_5_group.h"

#ifdef ONLY_GPU


#define NESTED_PARALLELISM_GROUP B1_2_FOR_EACH_LINEAR_MANDELBROT_WRAPPER


#else

// Register the function as a benchmark
#define NESTED_PARALLELISM_GROUP                                              \
	B1_1_FOR_EACH_LINEAR_GROUP                                                \
	B1_2_FOR_EACH_LINEAR_MANDELBROT_GROUP                                     \
	B1_3_FOR_EACH_QUADRATIC_GROUP                                             \
	B1_4_FOR_EACH_QUADRATIC_MANDELBROT_GROUP(std::execution::parallel_policy) \
	B1_5_FOR_EACH_EXPONENTIAL_GROUP

#endif

#endif //PSTL_BENCH_B1_GROUP_H
