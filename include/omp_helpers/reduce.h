#ifndef PSTL_BENCH_REDUCE_H
#define PSTL_BENCH_REDUCE_H

#include <execution>
#include <iterator>

namespace omp
{
	template<class ExecutionPolicy, class ForwardIt, class T, class BinaryOp>
	T reduce(ExecutionPolicy && policy, ForwardIt first, ForwardIt last, T init, BinaryOp binary_op)
	{
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_unsequenced_policy>)
		{
			T result = init;

#pragma omp parallel for simd default(none) shared(first, last, result, binary_op)
			for (std::size_t i = 0; i < std::distance(first, last); ++i)
			{
				result = binary_op(result, first[i]);
			}
			return result;
		}
		// if policy is std::execution::parallel_policy -> parallelization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_policy>)
		{
			T result = init;

#pragma omp parallel for default(none) shared(first, last, result, binary_op)
			for (std::size_t i = 0; i < std::distance(first, last); ++i)
			{
				result = binary_op(result, first[i]);
			}
			return result;
		}
		// if policy is std::execution::unsequenced_policy -> vectorization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::unsequenced_policy>)
		{
			T result = init;

#pragma omp simd
			for (std::size_t i = 0; i < std::distance(first, last); ++i)
			{
				result = binary_op(result, first[i]);
			}
			return result;
		}
		// if policy is std::execution::sequenced_policy or any other unknown policy -> forward to the default...
		else { return std::reduce(policy, first, last, init, binary_op); }
	}

	template<class ExecutionPolicy, class ForwardIt, class T>
	T reduce(ExecutionPolicy && policy, ForwardIt first, ForwardIt last, T init)
	{
		return omp::reduce(policy, first, last, init, std::plus<>());
	}

	template<class ExecutionPolicy, class ForwardIt>
	typename std::iterator_traits<ForwardIt>::value_type reduce(ExecutionPolicy && policy, ForwardIt first,
	                                                            ForwardIt last)
	{
		return omp::reduce(policy, first, last, typename std::iterator_traits<ForwardIt>::value_type{}, std::plus<>());
	}


} // namespace omp

#endif //PSTL_BENCH_REDUCE_H
