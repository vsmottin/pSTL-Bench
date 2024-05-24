#pragma once

#include <parallel/algorithm>

namespace benchmark_for_each
{

	const auto for_each_gnu = [](auto && policy, auto & input, auto && f) {
		__gnu_parallel::for_each(input.begin(), input.end(), f);
	};

} // namespace benchmark_for_each
