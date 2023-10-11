
#ifndef PSTL_BENCH_FOR_EACH_H
#define PSTL_BENCH_FOR_EACH_H

#include <execution>

namespace omp
{
	template<class ExecutionPolicy, class ForwardIt, class UnaryFunction2>
	void for_each(ExecutionPolicy && policy, ForwardIt first, ForwardIt last, UnaryFunction2 f)
	{
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if constexpr (std::is_convertible_v<decltype(policy), std::execution::parallel_unsequenced_policy>)
		{
#pragma omp parallel for simd default(none) shared(first, last, f)
			for (std::size_t i = 0; i < std::distance(first, last); ++i)
			{
				f(first[i]);
			}
		}
		// if policy is std::execution::parallel_policy -> parallelization
		else if constexpr (std::is_convertible_v<decltype(policy), std::execution::parallel_policy>)
		{
#pragma omp parallel for default(none) shared(first, last, f)
			for (std::size_t i = 0; i < std::distance(first, last); ++i)
			{
				f(first[i]);
			}
		}
		// if policy is std::execution::unsequenced_policy -> vectorization
		else if constexpr (std::is_convertible_v<decltype(policy), std::execution::unsequenced_policy>)
		{
#pragma omp simd
			for (std::size_t i = 0; i < std::distance(first, last); ++i)
			{
				f(first[i]);
			}
		}
		// if policy is std::execution::sequenced_policy or any other unknown policy -> forward to the default...
		else { std::for_each(policy, first, last, f); }
	}
} // namespace omp

#endif //PSTL_BENCH_FOR_EACH_H
