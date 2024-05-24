#pragma once

#include <parallel/numeric>

namespace benchmark_adjacent_difference
{
	const auto adjacent_difference_gnu = []([[maybe_unused]] auto & policy, const auto & input, auto & output) {
		__gnu_parallel::adjacent_difference(input.begin(), input.end(), output.begin(), std::minus<>());
	};
} // namespace benchmark_adjacent_difference


