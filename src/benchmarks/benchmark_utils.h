
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
#include <iostream>

#include "../parallel_allocator.h"

#define CUSTOM_STATISTICS \
    ComputeStatistics("max", [](const std::vector<double>& v) -> double {return *(std::max_element(std::begin(v), std::end(v)));})-> \
    ComputeStatistics("min", [](const std::vector<double>& v) -> double {return *(std::min_element(std::begin(v), std::end(v)));})-> \
    UseManualTime()


#define WRAP_TIMING(code) \
    auto start = std::chrono::high_resolution_clock::now();                                         \
    code;                                                                                           \
    auto end = std::chrono::high_resolution_clock::now();                                           \
    auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);  \
    state.SetIterationTime(elapsed_seconds.count());


namespace suite {

    template<typename T>
    using base_type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

#ifdef USE_PARALLEL_ALLOCATOR

    template<typename VALUE_TYPE,
            typename ExecutionPolicy,
            class = typename std::enable_if<std::is_execution_policy<ExecutionPolicy>::value>::type
    >
    using vec = std::vector<VALUE_TYPE, suite::numa_allocator<VALUE_TYPE, ExecutionPolicy>>;

    template<typename ExecutionPolicy>
    using int_vec = suite::vec<int, ExecutionPolicy>;

    template<typename ExecutionPolicy>
    using double_vec = suite::vec<double, ExecutionPolicy>;

#else

    template<typename VALUE_TYPE,
            typename ExecutionPolicy>
    using vec = std::vector<VALUE_TYPE>;

    template<typename ExecutionPolicy>
    using int_vec = suite::vec<int, ExecutionPolicy>;

    template<typename ExecutionPolicy>
    using double_vec = suite::vec<double, ExecutionPolicy>;

#endif

    /**
     * Allows to create a vector using the allocation strategy configured
     * @tparam ExecutionPolicy the execution policy to use. Only considered when using the flag `USE_PARALLEL_ALLOCATOR`
     * @tparam Container the container type to create
     * @tparam Value_Type the value type of the container
     * @tparam Size_type the size type of the container
     * @param size the actual size of the container we want to create
     * @return  the newly created container
     */
    template<typename ExecutionPolicy,
            typename Container = suite::int_vec<ExecutionPolicy>,
            typename Value_Type = typename Container::value_type,
            typename Size_type = typename Container::size_type
    >
    Container get_vec(const Size_type size) {
#ifdef USE_PARALLEL_ALLOCATOR
        constexpr auto execution_policy = ExecutionPolicy{};

        const suite::numa_allocator<Value_Type, ExecutionPolicy> allocator(execution_policy);
        Container vec(size, allocator);
#else
        Container vec(size);
#endif
        return vec;
    }

    /**
     * Allows to create an empty vector using the allocation strategy configured
     * @tparam ExecutionPolicy the execution policy to use. Only considered when using the flag `USE_PARALLEL_ALLOCATOR`
     * @tparam Container the container type to create
     * @tparam Value_Type the value type of the container
     * @tparam Size_type the size type of the container
     * @param size the actual size of the container we want to create
     * @return  the newly created container
     */
    template<typename ExecutionPolicy,
            typename Container = suite::int_vec<ExecutionPolicy>,
            typename Value_Type = typename Container::value_type,
            typename Size_type = typename Container::size_type
    >
    Container get_emtpy_vec() {
#ifdef USE_PARALLEL_ALLOCATOR
        constexpr auto execution_policy = ExecutionPolicy{};

        const suite::numa_allocator<Value_Type, ExecutionPolicy> allocator(execution_policy);
        Container vec(allocator);
#else
        Container vec;
#endif
        return vec;
    }

    /**
     * Fills the given container with the provided value
     * @tparam ExecutionPolicy the execution policy to use for filling
     * @tparam Container  the container type to fill by default its suit::int_vec
     * @tparam Value_Type  the value type of the given container
     * @param container the container to fill
     * @param value the value that should be filled in
     */
    template<typename ExecutionPolicy,
            typename Container = suite::int_vec<ExecutionPolicy>,
            typename Value_Type = typename Container::value_type>
    void fill_init(Container &container, const Value_Type value) {
        constexpr auto execution_policy = ExecutionPolicy{};
        std::fill(execution_policy, container.begin(), container.end(), value);
    }

    template<typename ExecutionPolicy, typename T>
    auto
    generate_uniform_dist_vec(const std::size_t &size, const T &lower_bound,
                              const T &upper_bound) {
#if ONLY_GPU
        constexpr auto execution_policy = std::execution::seq;
#else
        constexpr auto execution_policy = ExecutionPolicy{};
#endif

        std::mt19937 mt_engine(std::time(nullptr));
        std::uniform_real_distribution<> dist(lower_bound, upper_bound);

        auto dist_vec = suite::get_vec<ExecutionPolicy, suite::vec<T, ExecutionPolicy>>(size);

        std::generate(execution_policy, dist_vec.begin(), dist_vec.end(), [&]() {
            return (T) dist(mt_engine);
        });

        return dist_vec;
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
            typename Container = suite::int_vec<ExecutionPolicy>,
            typename T = typename Container::value_type,
            typename Size_type = typename Container::size_type>
    Container
    generate_decrement(const ExecutionPolicy execution_policy,
                       const Size_type &size,
                       const T start_val,
                       const T decrement = 1) {

        auto generatedVec = suite::get_vec<ExecutionPolicy, Container>(size);

        // this vector of indices does not need to be parallel allocated since it is not performance critical
        for (Size_type index = 0; index < size; ++index) {
            generatedVec[index] = start_val - (index * decrement);
        }

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
            typename Container = suite::int_vec<ExecutionPolicy>,
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
            typename Container = suite::int_vec<ExecutionPolicy>,
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
