
#ifndef PSTL_BENCH_INCLUSIVE_SCAN_H
#define PSTL_BENCH_INCLUSIVE_SCAN_H

#include <execution>
#include <numeric>

namespace omp
{

	template<class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class BinaryOperation, class T>
	ForwardIt2 inclusive_scan(ExecutionPolicy && policy, ForwardIt1 first, ForwardIt1 last, ForwardIt2 d_first,
	                          BinaryOperation binary_op, T init)
	{
		// If the range is empty, just return d_first.
		if (first == last) { return d_first; }

		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_unsequenced_policy>)
		{
			*d_first++ = init;

			const auto dist = std::distance(first, last);

#pragma omp parallel for simd default(none) shared(first, last, d_first, init, binary_op)
			// for (; __first != __last; ++__first)
			for (std::size_t i = 0; i < dist; ++i)
			{
				init       = binary_op(init, *first++);
				*d_first++ = init;
			}
		}
		// if policy is std::execution::parallel_policy -> parallelization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::parallel_policy>)
		{
			*d_first++ = init;

			const auto dist = std::distance(first, last);

#pragma omp parallel for default(none) shared(first, last, d_first, init, binary_op)
			for (std::size_t i = 0; i < dist; ++i)
			{
				init       = binary_op(init, *first++);
				d_first[i] = init;
			}
		}
		// if policy is std::execution::unsequenced_policy -> vectorization
		else if constexpr (std::is_same_v<decltype(policy), std::execution::unsequenced_policy>)
		{
			*d_first++ = init;

			const auto dist = std::distance(first, last);

#pragma omp simd
			for (std::size_t i = 0; i < dist; ++i)
			{
				init       = binary_op(init, *first++);
				d_first[i] = init;
			}
		}
		// if policy is std::execution::sequenced_policy or any other unknown policy -> forward to the default...
		else { return std::inclusive_scan(policy, first, last, d_first, binary_op, init); }

		return d_first;
	}

	template<class ExecutionPolicy, class ForwardIt1, class ForwardIt2, class BinaryOperation>
	ForwardIt2 inclusive_scan(ExecutionPolicy && policy, ForwardIt1 first, ForwardIt1 last, ForwardIt2 d_first,
	                          BinaryOperation binary_op)
	{
		typename std::iterator_traits<ForwardIt1>::value_type init = d_first++;

		return omp::inclusive_scan(policy, first, last, d_first, binary_op, init);
	}

	template<class ExecutionPolicy, class ForwardIt1, class ForwardIt2>
	ForwardIt2 inclusive_scan(ExecutionPolicy && policy, ForwardIt1 first, ForwardIt1 last, ForwardIt2 d_first)
	{
		typename std::iterator_traits<ForwardIt1>::value_type init = *d_first++;

		return omp::inclusive_scan(policy, first, last, d_first, std::plus<>(), init);
	}

} // namespace omp

#endif //PSTL_BENCH_INCLUSIVE_SCAN_H
