
#ifndef MASTER_BENCHMARKS_BENCHMARK_UTILS_H
#define MASTER_BENCHMARKS_BENCHMARK_UTILS_H

#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

namespace suite {

// some compilers did not implement the both fields (for example nvc++@22.5) so we just define it ourselfs
#ifdef __cpp_lib_hardware_interference_size
    constexpr std::size_t hardware_constructive_interference_size = std::hardware_constructive_interference_size;
    constexpr std::size_t hardware_destructive_interference_size = std::hardware_destructive_interference_size;
#else
    constexpr std::size_t hardware_constructive_interference_size = 64;
    constexpr std::size_t hardware_destructive_interference_size = 64;
#endif


    template<typename T>
    std::vector<T>
    generate_uniform_dist_vec(const std::size_t &size, const int &lower_bound, const int &upper_bound) {

        std::mt19937 mt_engine(std::time(nullptr));
        std::uniform_real_distribution<> dist(lower_bound, upper_bound);

        std::vector<T> randValues(size);

        std::generate(randValues.begin(), randValues.end(), [&]() {
            return (T) dist(mt_engine);
        });

        return randValues;
    }

    /**
     * Generates a vector of type T that contains size elements where the first element is start_val
     * and then every next element is decremented by decrement
     *
     * @tparam T the type of the vector
     * @param size the number of elements
     * @param start_val the start val
     * @param decrement the value to use to decrement
     */
    template<typename T>
    std::vector<T>
    generate_decrement_vec(const std::size_t &size, const T &start_val, const T &decrement = 1) {

        std::vector<T> randValues(size);

        T n = start_val;
        std::generate(randValues.begin(), randValues.end(), [&n, &decrement] { return n -= decrement; });

        return randValues;
    }

    /**
     * Generates a vector of type T that contains size elements where the first element is 0
     * and then every next element is incremented by increment
     *
     * @tparam T the type of the vector
     * @param size the number of elements
     * @param increment the increment to use
     */
    template<typename T>
    std::vector<T>
    generate_increment_vec(const std::size_t &size, const T &increment) {
        return suite::generate_decrement_vec<T>(size, static_cast<T>(0), -increment);
    }

}
#endif //MASTER_BENCHMARKS_BENCHMARK_UTILS_H
