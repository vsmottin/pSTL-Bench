#ifndef PSTL_BENCH_REDUCE_H
#define PSTL_BENCH_REDUCE_H

#include <execution>
#include <iterator>

namespace omp
{

	template<class ForwardIt, class T, class BinaryOp>
	T reduce_par_for_simd(ForwardIt first, ForwardIt last, T init, BinaryOp binary_op)
	{
		if (first == last) { return init; }

		T result = init;

#pragma omp parallel default(none) shared(first, last, result) firstprivate(init, binary_op)
		{
			const auto num_threads = omp_get_num_threads();

			const auto tid = omp_get_thread_num();

			const auto size = std::distance(first, last);

			// Divide the range into chunks
			const auto chunk_size = size % num_threads == 0 ? size / num_threads : size / num_threads + 1;

			// Calculate the range for the current thread
			const auto range_begin = std::min(last, first + tid * chunk_size);
			const auto range_end   = std::min(last, range_begin + chunk_size);

			if (range_begin < range_end)
			{
				auto p_result = *range_begin;

				// Calculate the partial result for the current thread
#pragma omp simd
				for (auto it = range_begin + 1; it < range_end; ++it)
				{
					p_result = binary_op(p_result, *it);
				}

#pragma omp critical
				result = binary_op(result, p_result);
			}
		}

		return result;
	}

	template<class ForwardIt, class T, class BinaryOp>
	T reduce_par_for(ForwardIt first, ForwardIt last, T init, BinaryOp binary_op)
	{
		if (first == last) { return init; }

		T result = init;

#pragma omp parallel default(none) shared(first, last, result) firstprivate(init, binary_op)
		{
			const auto num_threads = omp_get_num_threads();

			const auto tid = omp_get_thread_num();

			const auto size = std::distance(first, last);

			// Divide the range into chunks
			const auto chunk_size = size % num_threads == 0 ? size / num_threads : size / num_threads + 1;

			// Calculate the range for the current thread
			const auto range_begin = std::min(last, first + tid * chunk_size);
			const auto range_end   = std::min(last, range_begin + chunk_size);

			if (range_begin < range_end)
			{
				auto p_result = *range_begin;

				// Calculate the partial result for the current thread
				for (auto it = range_begin + 1; it < range_end; ++it)
				{
					p_result = binary_op(p_result, *it);
				}

#pragma omp critical
				result = binary_op(result, p_result);
			}
		}

		return result;
	}

	template<class ExecutionPolicy, class ForwardIt, class T, class BinaryOp>
	T reduce(ExecutionPolicy && policy, ForwardIt first, ForwardIt last, T init, BinaryOp binary_op)
	{
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if constexpr (std::is_convertible_v<decltype(policy), std::execution::parallel_unsequenced_policy>)
		{
			return reduce_par_for_simd(first, last, init, binary_op);
		}
		// if policy is std::execution::parallel_policy -> parallelization
		else if constexpr (std::is_convertible_v<decltype(policy), std::execution::parallel_policy>)
		{
			return reduce_par_for(first, last, init, binary_op);
		}
		// if policy is std::execution::unsequenced_policy -> vectorization
		else if constexpr (std::is_convertible_v<decltype(policy), std::execution::unsequenced_policy>)
		{
			T result = init;

#pragma omp simd
			for (auto it = first; it < last; ++it)
			{
				result = binary_op(result, *it);
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
