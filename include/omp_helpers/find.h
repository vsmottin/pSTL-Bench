
#ifndef PSTL_BENCH_OMP_FIND_H
#define PSTL_BENCH_OMP_FIND_H

#include <algorithm>
#include <execution>
#include <optional>

#include <omp.h>

namespace omp
{
	template<class ExecutionPolicy, class ForwardIt, class T, class Function>
	auto find_template(ExecutionPolicy && policy, ForwardIt first, ForwardIt last, const T & value,
	                   Function && local_find)
	{
		ForwardIt result = last;

#pragma omp parallel default(none) shared(first, last, value, result, local_find)
		{
			int num_threads = 0;

#pragma omp single
			num_threads = omp_get_num_threads();

			const auto tid = omp_get_thread_num();

			std::vector<ForwardIt> results(num_threads, last);

#pragma omp for
			for (std::size_t i = 0; i < num_threads; ++i)
			{
				const auto local_first = first + i * std::distance(first, last) / num_threads;
				const auto local_last  = std::min(first + (i + 1) * std::distance(first, last) / num_threads, last);

				auto local_result = local_find(policy, local_first, local_last, value);

				if (local_result not_eq local_last) { results[tid] = local_result; }
			}

#pragma omp single
			for (const auto & p_result : results)
			{
				if (p_result not_eq last)
				{
					result = p_result;
					break;
				}
			}
		}

		return result;
	}

	template<class ExecutionPolicy, class ForwardIt, class T>
	ForwardIt find(ExecutionPolicy && policy, ForwardIt first, ForwardIt last, const T & value)
	{
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_unsequenced_policy>)
		{
			find_template(std::execution::unseq, first, last, value,
			              [](auto && policy, auto && first, auto && last, auto && value) {
				              return std::find(policy, first, last, value);
			              });
		}
		// if policy is std::execution::parallel_policy -> parallelization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_policy>)
		{
			find_template(std::execution::seq, first, last, value,
			              [](auto && policy, auto && first, auto && last, auto && value) {
				              return std::find(policy, first, last, value);
			              });
		}
		// if policy is std::execution::unsequenced_policy -> vectorization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::unsequenced_policy>)
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
