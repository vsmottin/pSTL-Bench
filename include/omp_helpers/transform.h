
#ifndef PSTL_BENCH_TRANSFORM_H
#define PSTL_BENCH_TRANSFORM_H

#include <execution>

namespace omp
{
	template<class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class UnaryOperation>
	ForwardIt2 transform(ExecutionPolicy && policy, ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 d_first,
	                     UnaryOperation unary_op)
	{
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_unsequenced_policy>)
		{
#pragma omp parallel for simd default(none) shared(first1, last1, d_first, unary_op)
			for (std::size_t i = 0; i < std::distance(first1, last1); ++i)
			{
				d_first[i] = unary_op(first1[i]);
			}
			return d_first + std::distance(first1, last1);
		}
		// if policy is std::execution::parallel_policy -> parallelization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_policy>)
		{
#pragma omp parallel for default(none) shared(first1, last1, d_first, unary_op)
			for (std::size_t i = 0; i < std::distance(first1, last1); ++i)
			{
				d_first[i] = unary_op(first1[i]);
			}
			return d_first + std::distance(first1, last1);
		}
		// if policy is std::execution::unsequenced_policy -> vectorization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::unsequenced_policy>)
		{
#pragma omp simd
			for (std::size_t i = 0; i < std::distance(first1, last1); ++i)
			{
				d_first[i] = unary_op(first1[i]);
			}
			return d_first + std::distance(first1, last1);
		}
		// if policy is std::execution::sequenced_policy or any other unknown policy -> forward to the default...
		else { return std::transform(policy, first1, last1, d_first, unary_op); }
	}

	template<class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class ForwardIt3, class BinaryOperation>
	ForwardIt3 transform(ExecutionPolicy && policy, ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2,
	                     ForwardIt3 d_first, BinaryOperation binary_op)
	{
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_unsequenced_policy>)
		{
#pragma omp parallel for simd default(none) shared(first1, last1, first2, d_first, binary_op)
			for (std::size_t i = 0; i < std::distance(first1, last1); ++i)
			{
				d_first[i] = binary_op(first1[i], first2[i]);
			}
			return d_first + std::distance(first1, last1);
		}
		// if policy is std::execution::parallel_policy -> parallelization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_policy>)
		{
#pragma omp parallel for default(none) shared(first1, last1, first2, d_first, binary_op)
			for (std::size_t i = 0; i < std::distance(first1, last1); ++i)
			{
				d_first[i] = binary_op(first1[i], first2[i]);
			}
			return d_first + std::distance(first1, last1);
		}
		// if policy is std::execution::unsequenced_policy -> vectorization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::unsequenced_policy>)
		{
#pragma omp simd
			for (std::size_t i = 0; i < std::distance(first1, last1); ++i)
			{
				d_first[i] = binary_op(first1[i], first2[i]);
			}
			return d_first + std::distance(first1, last1);
		}
		// if policy is std::execution::sequenced_policy or any other unknown policy -> forward to the default...
		else { return std::transform(policy, first1, last1, first2, d_first, binary_op); }
	}
} // namespace omp

#endif //PSTL_BENCH_TRANSFORM_H
