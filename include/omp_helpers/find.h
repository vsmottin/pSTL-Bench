
#ifndef PSTL_BENCH_OMP_FIND_H
#define PSTL_BENCH_OMP_FIND_H

#include <algorithm>
#include <execution>
#include <optional>

#include <omp.h>

namespace omp
{
	template<class ForwardIt, class T, class Function>
	auto find_template(ForwardIt first, ForwardIt last, const T & value, Function && local_find)
	{
		std::vector<ForwardIt> local_results;

#pragma omp parallel default(none) shared(first, last, value, local_find, local_results)
		{
			const auto num_threads = omp_get_num_threads();

#pragma omp single
			local_results.resize(num_threads, last);

			const auto tid = omp_get_thread_num();

			const auto size = std::distance(first, last);

			// Divide the range into chunks
			const auto chunk_size = size % num_threads == 0 ? size / num_threads : size / num_threads + 1;

			// Calculate the range for the current thread
			const auto range_begin = std::min(last, first + tid * chunk_size);
			const auto range_end   = std::min(last, range_begin + chunk_size);

			if (range_begin < range_end)
			{
				const auto p_result = local_find(range_begin, range_end, value);
				local_results[tid]  = p_result == range_end ? last : p_result;
			}
		}

		for (const auto & p_result : local_results)
		{
			if (p_result != last) { return p_result; }
		}

		return last;
	}

	template<class ExecutionPolicy, class ForwardIt, class T>
	ForwardIt find(ExecutionPolicy && policy, ForwardIt first, ForwardIt last, const T & value)
	{
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if constexpr (std::is_convertible_v<decltype(policy), std::execution::parallel_unsequenced_policy>)
		{
			return find_template(first, last, value, [=](auto && first, auto && last, auto && value) {
				return std::find(std::execution::unseq, first, last, value);
			});
		}
		// if policy is std::execution::parallel_policy -> parallelization
		else if constexpr (std::is_convertible_v<decltype(policy), std::execution::parallel_policy>)
		{
			return find_template(first, last, value, [=](auto && first, auto && last, auto && value) {
				return std::find(std::execution::seq, first, last, value);
			});
		}
		// if policy is std::execution::unsequenced_policy -> vectorization
		else if constexpr (std::is_convertible_v<decltype(policy), std::execution::unsequenced_policy>)
		{
			// TODO: implement
			return std::find(policy, first, last, value);
		}
		// if policy is std::execution::sequenced_policy or any other unknown policy -> forward to the default...
		else { return std::find(policy, first, last, value); }
	}

	template<class ExecutionPolicy, class ForwardIt, class UnaryPredicate>
	ForwardIt find_if(ExecutionPolicy && policy, ForwardIt first, ForwardIt last, UnaryPredicate p);

	template<class ExecutionPolicy, class ForwardIt, class UnaryPredicate>
	ForwardIt find_if_not(ExecutionPolicy && policy, ForwardIt first, ForwardIt last, UnaryPredicate q);
} // namespace omp

#endif //PSTL_BENCH_OMP_FIND_H
