
#pragma once

#include <algorithm>

namespace benchmark_none_of
{

	const auto none_of_std = [](auto && policy, const auto & begin, const auto & end, auto && condition) {
		return std::none_of(policy, begin, end, condition);
	};

} // namespace benchmark_none_of


