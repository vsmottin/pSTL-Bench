#ifndef PSTL_BENCH_COUNT_IF_H
#define PSTL_BENCH_COUNT_IF_H

#include <execution>
#include <iterator>

namespace omp
{
	template<class ExecutionPolicy, class ForwardIt, class UnaryPredicate>
	typename std::iterator_traits<ForwardIt>::difference_type count_if(ExecutionPolicy && policy, ForwardIt first,
	                                                                   ForwardIt last, UnaryPredicate p)
	{
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if constexpr (std::is_convertible_v<decltype(policy), std::execution::parallel_unsequenced_policy>)
		{
			typename std::iterator_traits<ForwardIt>::difference_type count = 0;

			const auto dist = std::distance(first, last);

#pragma omp parallel for simd default(none) shared(first, last, p) firstprivate(dist) reduction(+ : count)
			for (std::size_t i = 0; i < dist; ++i)
			{
				if (p(*(first + i))) { ++count; }
			}

			return count;
		}
		// if policy is std::execution::parallel_policy -> parallelization
		else if constexpr (std::is_convertible_v<decltype(policy), std::execution::parallel_policy>)
		{
			typename std::iterator_traits<ForwardIt>::difference_type count = 0;

			const auto dist = std::distance(first, last);

#pragma omp parallel for default(none) shared(first, last, p) firstprivate(dist) reduction(+ : count)
			for (std::size_t i = 0; i < dist; ++i)
			{
				if (p(*(first + i))) { ++count; }
			}

			return count;
		}
		// if policy is std::execution::unsequenced_policy -> vectorization
		else if constexpr (std::is_convertible_v<decltype(policy), std::execution::unsequenced_policy>)
		{
			typename std::iterator_traits<ForwardIt>::difference_type count = 0;

			const auto dist = std::distance(first, last);

#pragma omp simd reduction(+ : count)
			for (std::size_t i = 0; i < dist; ++i)
			{
				if (p(*(first + i))) { ++count; }
			}

			return count;
		}
		// if policy is std::execution::sequenced_policy or any other unknown policy -> forward to the default...
		else { return std::count_if(policy, first, last, p); }
	}
} // namespace omp

#endif //PSTL_BENCH_COUNT_IF_H
