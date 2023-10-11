#ifndef PSTL_BENCH_SORT_H
#define PSTL_BENCH_SORT_H

#include <algorithm>
#include <execution>

namespace omp
{
	namespace q_sort
	{
		// adapted from https://stackoverflow.com/a/54976413
		template<typename RandomIt, typename Compare>
		RandomIt partition(RandomIt first, RandomIt last, Compare comp)
		{
			auto pivot = std::prev(last, 1);
			auto i     = first;
			for (auto j = first; j != pivot; ++j)
			{
				if (comp(*j, *pivot)) { std::swap(*i++, *j); }
			}
			std::swap(*i, *pivot);
			return i;
		}

		template<class RandomIt, class Compare>
		void launch_tasks(RandomIt first, RandomIt last, Compare comp)
		{
			if (std::distance(first, last) <= 1) { return; }

			auto p = omp::q_sort::partition(first, last, comp);

#pragma omp task default(none) firstprivate(first, p, comp)
			launch_tasks(first, p, comp);
#pragma omp task default(none) firstprivate(last, p, comp)
			launch_tasks(p + 1, last, comp);
		}

		template<class RandomIt, class Compare>
		void parallel_q_sort(RandomIt first, RandomIt last, Compare comp)
		{
#pragma omp parallel default(none) firstprivate(first, last, comp)
			{
#pragma omp single
				launch_tasks(first, last, comp);
#pragma omp taskwait
			}
		}
	} // namespace q_sort


	template<class ExecutionPolicy, class RandomIt, class Compare>
	void sort(ExecutionPolicy && policy, RandomIt first, RandomIt last, Compare comp)
	{
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization
		// or std::execution::parallel_policy -> parallelization
		if constexpr (std::is_convertible_v<decltype(policy), std::execution::parallel_unsequenced_policy> ||
		              std::is_convertible_v<decltype(policy), std::execution::parallel_policy>)
		{
			q_sort::parallel_q_sort(first, last, comp);
		}
		// else, forward to the default...
		else { std::sort(policy, first, last, comp); }
	}


	template<class ExecutionPolicy, class RandomIt>
	void sort(ExecutionPolicy && policy, RandomIt first, RandomIt last)
	{
		omp::sort(policy, first, last, std::less<typename std::iterator_traits<RandomIt>::value_type>());
	}
} // namespace omp

#endif //PSTL_BENCH_SORT_H
