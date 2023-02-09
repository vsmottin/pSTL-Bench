#include <iostream>
#include <numeric>
#include <chrono>
#include <execution>

#include "b1_for_each_linear.h"

#define ITERATIONS 10000
#define TIME_PRECISION std::chrono::nanoseconds

template<typename T>
constexpr const char *GetUnits(T) { return "unknown units"; }

template<>
constexpr const char *GetUnits(std::chrono::nanoseconds) { return "ns"; }

template<>
constexpr const char *GetUnits(std::chrono::microseconds) { return "\u03BCs"; }

template<>
constexpr const char *GetUnits(std::chrono::milliseconds) { return "ms"; }


int main() {

    const auto &precision_unit = GetUnits(TIME_PRECISION{});

    std::vector<TIME_PRECISION::rep> times;

    for (int i = 0; i < ITERATIONS; i++) {
        std::vector<int> x(1000, 1);
        const auto s1 = std::chrono::high_resolution_clock::now();

        b1_for_each_linear(std::execution::par, x);

        const auto d1 = std::chrono::duration_cast<TIME_PRECISION>(
                std::chrono::high_resolution_clock::now() - s1);
        times.push_back(d1.count());
    }
    const auto time_sum = std::accumulate(times.begin(), times.end(), static_cast<TIME_PRECISION::rep>(0));
    const auto avg_time = time_sum / times.size();
    std::cout << "Avg Time: " << avg_time << precision_unit << std::endl;

    std::cout << "Median Time: " << times[std::floor(ITERATIONS / 2)] << precision_unit << std::endl;

    return 0;
}
