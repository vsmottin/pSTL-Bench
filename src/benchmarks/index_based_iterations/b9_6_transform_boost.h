
#ifndef PSTL_BENCH_B9_6_TRANSFORM_BOOST_H
#define PSTL_BENCH_B9_6_TRANSFORM_BOOST_H

#include <algorithm>
#include <benchmark_utils.h>
#include <boost/iterator/counting_iterator.hpp>
#include <vector>

namespace B9
{

	const auto b9_6_transform_boost = [](auto && policy, const auto & input_data, auto & res, auto && f) {
		std::transform(policy, boost::counting_iterator<int>(0), boost::counting_iterator<int>(input_data.size()),
		               res.begin(), [&input_data, &f](const auto & i) { return f(input_data[i]); });
	};

}

#endif //PSTL_BENCH_B9_6_TRANSFORM_BOOST_H
