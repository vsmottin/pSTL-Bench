
#ifndef MASTER_BENCHMARKS_BENCHMARK_UTILS_H
#define MASTER_BENCHMARKS_BENCHMARK_UTILS_H

#include <vector>
#include <list>
#include <random>
#include <algorithm>
#include <ctime>
#include <atomic>
#include <execution>
#include <numeric>

#ifndef __GNUG__
#include <chrono>
#endif

#define CUSTOM_STATISTICS \
    ComputeStatistics("max", [](const std::vector<double>& v) -> double {return *(std::max_element(std::begin(v), std::end(v)));})-> \
    ComputeStatistics("min", [](const std::vector<double>& v) -> double {return *(std::min_element(std::begin(v), std::end(v)));})-> \
    UseManualTime()


#define WRAP_TIMING(code) \
    auto start = std::chrono::high_resolution_clock::now();                                         \
    code;                                                                                           \
    auto end = std::chrono::high_resolution_clock::now();                                           \
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);  \
    state.SetIterationTime(elapsed_seconds.count());                                                \



namespace suite {

    typedef std::vector<int> int_vec;

    template<typename ExecutionPolicy,
            typename Container = suite::int_vec,
            typename Value_Type = typename Container::value_type>
    void fill_init(Container &container, const Value_Type value) {
        constexpr auto execution_policy = ExecutionPolicy{};
        std::fill(execution_policy, container.begin(), container.end(), value);
    }

    template<typename ExecutionPolicy, typename T>
    std::vector<T>
    generate_uniform_dist_vec(const std::size_t &size, const T &lower_bound,
                              const T &upper_bound) {
        constexpr auto execution_policy = ExecutionPolicy{};

        std::mt19937 mt_engine(std::time(nullptr));
        std::uniform_real_distribution<> dist(lower_bound, upper_bound);

        std::vector<T> randValues(size);

        std::generate(execution_policy, randValues.begin(), randValues.end(), [&]() {
            return (T) dist(mt_engine);
        });

        return randValues;
    }

    /**
     * Generates a container of type Container that contains size elements where the first element is start_val
     * and then every next element is decremented by decrement
     *
     * @tparam ExecutionPolicy the executionpolicy to use for the creation
     * @tparam T the value type of the container
     * @tparam Container the container type
     * @param size the number of elements
     * @param start_val the start val
     * @param decrement the value to use to decrement
     */
    template<typename ExecutionPolicy,
            typename Container = suite::int_vec,
            typename T = typename Container::value_type,
            typename Size_type = typename Container::size_type>
    Container
    generate_decrement(const ExecutionPolicy execution_policy,
                       const Size_type &size,
                       const T start_val,
                       const T decrement = 1) {

        Container generatedVec(size);

        std::vector<Size_type> indices(size);
        std::iota(indices.begin(), indices.end(), 1);

        std::transform(execution_policy, indices.begin(), indices.end(), generatedVec.begin(), [=](const auto index) {
            return start_val - ((index - 1) * decrement);
        });


        return generatedVec;
    }

    /**
     * Generates a Container of type Container that contains size elements where the first element is start
     * and then every next element is incremented by increment
     *
     * the vector contains elements [start,start+(size*increment) )
     *
     * @tparam T the value type of the container
     * @tparam Container the container type
     * @param start the number to start the range from
     * @param size the number of elements
     * @param increment the increment to use
     */
    template<typename ExecutionPolicy,
            typename Container = suite::int_vec,
            typename T = typename Container::value_type,
            typename Size_type = typename Container::size_type>
    Container
    generate_increment(const ExecutionPolicy execution_policy,
                       const Size_type &size,
                       const T start,
                       const T increment) {
        return suite::generate_decrement<ExecutionPolicy, Container>(execution_policy, size, start, -increment);
    }

    /**
     * Generates a vector of type T that contains size elements where the first element is 0
     * and then every next element is incremented by increment
     *
     * @tparam T the type of the vector
     * @param size the number of elements
     * @param increment the increment to use
     */
    template<typename ExecutionPolicy,
            typename Container = suite::int_vec,
            typename T = typename Container::value_type,
            typename Size_type = typename Container::size_type>
    Container
    generate_increment(const ExecutionPolicy execution_policy,
                       const Size_type size,
                       const T increment
    ) {
        return suite::generate_increment<ExecutionPolicy, Container>(execution_policy,
                                                                     size,
                                                                     static_cast<T>(0),
                                                                     increment
        );
    }

}
#endif //MASTER_BENCHMARKS_BENCHMARK_UTILS_H
