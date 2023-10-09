
#ifndef PSTL_BENCH_B7_2_ALL_OFF_VS_TRANSFORM_REDUCE_H
#define PSTL_BENCH_B7_2_ALL_OFF_VS_TRANSFORM_REDUCE_H

#include <algorithm>
#include <benchmark_utils.h>
#include <functional>
#include <numeric>
#include <vector>

namespace B7
{

	template<class ExecutionPolicy, typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>,
	         typename Pred = typename std::function<bool(std::vector<int>::const_reference)>>
	inline bool b7_2_all_of(ExecutionPolicy && policy, const suite::int_vec<BASE_POLICY> & container, Pred && pred)
	{
		return std::all_of(policy, container.begin(), container.end(), pred);
	}


	template<class ExecutionPolicy, typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>,
	         typename Pred = typename std::function<bool(std::vector<int>::const_reference)>>
	inline bool b7_2_custom_all_of_with_transform_reduce(ExecutionPolicy &&                  policy,
	                                                     const suite::int_vec<BASE_POLICY> & container, Pred && pred)
	{
		return std::transform_reduce(policy, container.begin(), container.end(), true, std::logical_and(), pred);
	}

} // namespace B7

#endif //PSTL_BENCH_B7_2_ALL_OFF_VS_TRANSFORM_REDUCE_H
