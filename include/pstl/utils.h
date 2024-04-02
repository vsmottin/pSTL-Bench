
#ifndef PSTL_BENCH_UTILS_H
#define PSTL_BENCH_UTILS_H

#include <algorithm>
#include <atomic>
#include <chrono>
#include <ctime>
#include <execution>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

#include <numa.h>

#include <benchmark/benchmark.h>

#ifdef USE_PARALLEL_ALLOCATOR
#include "parallel_allocator.h"
#endif

#include "elem_t.h"

#ifdef USE_PAPI
#include <papi.h>

#define PRINT_PAPI_ERROR(retval, zone_name)                                                                          \
	{                                                                                                                \
		std::cerr << "Error " << retval << " for zone " << zone_name << " : " << PAPI_strerror(retval) << std::endl; \
	}
#endif

#ifdef USE_LIKWID
#include <likwid-marker.h>
#endif

#ifdef USE_HPX
#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>
#endif

#ifdef USE_GNU
#include <parallel/algorithm>
#endif

#define CUSTOM_STATISTICS                                                               \
	ComputeStatistics("max",                                                            \
	                  [](const std::vector<double> & v) -> double {                     \
		                  return *(std::max_element(std::begin(v), std::end(v)));       \
	                  })                                                                \
	    ->ComputeStatistics("min",                                                      \
	                        [](const std::vector<double> & v) -> double {               \
		                        return *(std::min_element(std::begin(v), std::end(v))); \
	                        })                                                          \
	    ->UseManualTime()

#define MEASURE_TIME(code)                                           \
	const auto _start = std::chrono::high_resolution_clock::now();   \
	code;                                                            \
	const auto _end     = std::chrono::high_resolution_clock::now(); \
	const auto _seconds = std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start);

namespace pstl
{
	template<typename Function>
	void for_each_core(Function && f)
	{
		// 0. Get the default bitmask
		cpu_set_t default_cpuset;
		CPU_ZERO(&default_cpuset);
		sched_getaffinity(0, sizeof(default_cpuset), &default_cpuset);

		// 1. Iterate over all cores in the system
		for (int i = 0; i < numa_num_configured_cpus(); i++)
		{
			// 1.1 If the core is not online, skip it
			if (!numa_bitmask_isbitset(numa_all_cpus_ptr, i)) { continue; }

			// 1.2 Set the affinity to the core
			cpu_set_t cpuset;
			CPU_ZERO(&cpuset);
			CPU_SET(i, &cpuset);
			sched_setaffinity(0, sizeof(cpuset), &cpuset);

			// 1.3 Call the function
			f();
		}

		// 2. Reset the affinity to the default bitmask
		sched_setaffinity(0, sizeof(default_cpuset), &default_cpuset);
	}

	void hw_counters_begin(const benchmark::State & state)
	{
#if defined(USE_PAPI) or defined(USE_LIKWID)
		const auto region = state.name() + "/" + std::to_string(state.range(0));
#if defined(USE_PAPI)
		auto marker_start_f = [&]() {
			int retval = PAPI_hl_region_begin(region.c_str());
			if (retval) { PRINT_PAPI_ERROR(retval, region.c_str()); }
		};
#elif defined(USE_LIKWID)
		auto marker_start_f = [&]() {
			LIKWID_MARKER_START(region.c_str());
		};
		LIKWID_MARKER_REGISTER(region.c_str());
#endif

		for_each_core(marker_start_f);
#endif
	}

	void hw_counters_end(const benchmark::State & state)
	{
#if defined(USE_PAPI) or defined(USE_LIKWID)
		const auto region = state.name() + "/" + std::to_string(state.range(0));
#if defined(USE_PAPI)
		auto marker_stop_f = [&]() {
			int retval = PAPI_hl_region_end(region.c_str());
			if (retval) { PRINT_PAPI_ERROR(retval, region.c_str()); }
		};
#elif defined(USE_LIKWID)
		auto marker_stop_f = [&]() {
			LIKWID_MARKER_STOP(region.c_str());
		};
#endif
		for_each_core(marker_stop_f);
#endif
	}
} // namespace pstl

#define WRAP_TIMING(code)           \
	pstl::hw_counters_begin(state); \
	MEASURE_TIME(code);             \
	pstl::hw_counters_end(state);   \
	state.SetIterationTime(_seconds.count());


namespace pstl
{

	template<typename T>
	using base_type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

#ifdef USE_PARALLEL_ALLOCATOR

	template<typename VALUE_TYPE, typename ExecutionPolicy,
	         class = typename std::enable_if<std::is_execution_policy<ExecutionPolicy>::value>::type>
	using vec = std::vector<VALUE_TYPE, pstl::numa_allocator<VALUE_TYPE, ExecutionPolicy>>;

#else

	template<typename VALUE_TYPE, typename ExecutionPolicy>
	using vec = std::vector<VALUE_TYPE>;

#endif

	/**
     * Allows to create a vector using the allocation strategy configured
     * @tparam ExecutionPolicy the execution policy to use. Only considered when using the flag `USE_PARALLEL_ALLOCATOR`
     * @tparam Container the container type to create
     * @tparam ValueType the value type of the container
     * @tparam Size_type the size type of the container
     * @param size the actual size of the container we want to create
     * @return  the newly created container
     */
	template<typename ExecutionPolicy, typename ValueType = pstl::elem_t,
	         typename Container = pstl::vec<ValueType, ExecutionPolicy>,
	         typename Size_type = typename Container::size_type>
	Container get_vec(const Size_type size)
	{
#ifdef USE_PARALLEL_ALLOCATOR
		constexpr auto execution_policy = ExecutionPolicy{};

		const pstl::numa_allocator<ValueType, ExecutionPolicy> allocator(execution_policy);
		Container                                              vec(size, allocator);
#else
		Container vec(size);
#endif
		return vec;
	}

	/**
     * Allows to create an empty vector using the allocation strategy configured
     * @tparam ExecutionPolicy the execution policy to use. Only considered when using the flag `USE_PARALLEL_ALLOCATOR`
     * @tparam Container the container type to create
     * @tparam ValueType the value type of the container
     * @tparam Size_type the size type of the container
     * @param size the actual size of the container we want to create
     * @return  the newly created container
     */
	template<typename ExecutionPolicy, typename ValueType = pstl::elem_t,
	         typename Container = pstl::vec<ValueType, ExecutionPolicy>,
	         typename Size_type = typename Container::size_type>
	Container get_emtpy_vec()
	{
#ifdef USE_PARALLEL_ALLOCATOR
		constexpr auto execution_policy = ExecutionPolicy{};

		const pstl::numa_allocator<ValueType, ExecutionPolicy> allocator(execution_policy);
		Container                                              vec(allocator);
#else
		Container vec;
#endif
		return vec;
	}

	/**
     * Fills the given container with the provided value
     * @tparam ExecutionPolicy the execution policy to use for filling
     * @tparam Container  the container type to fill
     * @tparam ValueType  the value type of the given container
     * @param container the container to fill
     * @param value the value that should be filled in
     */
	template<typename ExecutionPolicy, typename ValueType = pstl::elem_t,
	         typename Container = pstl::vec<ValueType, ExecutionPolicy>>
	void fill_init(Container & container, const ValueType value)
	{
		constexpr auto execution_policy = ExecutionPolicy{};
		std::fill(execution_policy, container.begin(), container.end(), value);
	}

	template<typename ExecutionPolicy, typename T>
	auto generate_uniform_dist_vec(const std::size_t & size, const T & lower_bound, const T & upper_bound)
	{
#if ONLY_GPU
		constexpr auto execution_policy = std::execution::seq;
#else
		constexpr auto execution_policy = ExecutionPolicy{};
#endif

		std::mt19937                     mt_engine(std::random_device{}());
		std::uniform_real_distribution<> dist(lower_bound, upper_bound);

		auto dist_vec = pstl::get_vec<ExecutionPolicy, pstl::vec<T, ExecutionPolicy>>(size);

		std::generate(execution_policy, dist_vec.begin(), dist_vec.end(), [&]() { return (T) dist(mt_engine); });

		return dist_vec;
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
	template<typename ExecutionPolicy, typename ValueType = pstl::elem_t,
	         typename Container = pstl::vec<ValueType, ExecutionPolicy>,
	         typename Size_type = typename Container::size_type>
	Container generate_increment(const ExecutionPolicy execution_policy, const Size_type & size, const ValueType start,
	                             const ValueType increment)
	{
		auto generatedVec = pstl::get_vec<ExecutionPolicy, ValueType, Container>(size);

		auto begin_ptr = generatedVec.data();

		auto body = [=](auto & val) {
			const auto i = &val - begin_ptr;
			val          = start + i * increment;
		};

#ifdef USE_PARALLEL_ALLOCATOR
#if defined(USE_HPX)
		hpx::for_each(execution_policy, generatedVec.begin(), generatedVec.end(), body);
#elif defined(USE_GNU)
		__gnu_parallel::for_each(generatedVec.begin(), generatedVec.end(), body);
#else
		std::for_each(execution_policy, generatedVec.begin(), generatedVec.end(), body);
#endif
#else
		std::for_each(generatedVec.begin(), generatedVec.end(), body);
#endif

		return generatedVec;
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
	template<typename ExecutionPolicy, typename ValueType = pstl::elem_t,
	         typename Container = pstl::vec<ValueType, ExecutionPolicy>,
	         typename Size_type = typename Container::size_type>
	Container generate_decrement(const ExecutionPolicy execution_policy, const Size_type & size,
	                             const ValueType start_val, const ValueType decrement = 1)
	{
		return generate_increment(execution_policy, size, start_val, -decrement);
	}

	/**
     * Generates a vector of type T that contains size elements where the first element is 0
     * and then every next element is incremented by increment
     *
     * @tparam T the type of the vector
     * @param size the number of elements
     * @param increment the increment to use
     */
	template<typename ExecutionPolicy, typename ValueType = pstl::elem_t,
	         typename Container = pstl::vec<ValueType, ExecutionPolicy>,
	         typename Size_type = typename Container::size_type>
	Container generate_increment(const ExecutionPolicy execution_policy, const Size_type size,
	                             const ValueType increment)
	{
		return pstl::generate_increment(execution_policy, size, {}, increment);
	}

	/**
     * Generates a vector of type T that contains size elements where the first element is 0
     * and then every next element is incremented by increment
     *
     * @tparam T the type of the vector
     * @param size the number of elements
     * @param increment the increment to use
     */
	template<typename ExecutionPolicy, typename ValueType = pstl::elem_t,
	         typename Container = pstl::vec<ValueType, ExecutionPolicy>,
	         typename Size_type = typename Container::size_type>
	Container generate_increment(const ExecutionPolicy execution_policy, const Size_type size)
	{
		return pstl::generate_increment(execution_policy, size, ValueType{ 1 }, ValueType{ 1 });
	}

	/**
	 * Computes (an estimation) the amount of bytes used by a container
	 * @param container the container to compute the size for
	 * @return the amount of (estimated) bytes used by the container
	 */
	static auto container_size(const auto & container)
	{
		return sizeof(base_type<decltype(container)>) * container.size() + sizeof(container);
	}

	/**
	 * Compute the amount of bytes computed by a benchmark
	 *
	 * @param state the benchmark state
	 * @param containers the containers used by the benchmark
	 * @return the amount of bytes computed by the benchmark
	 */
	static auto computed_bytes(const ::benchmark::State & state, const auto &... containers)
	{
		std::size_t bytes = 0;

		const auto accumulate_bytes = [&bytes](const auto & container) {
			bytes += pstl::container_size(container);
		};

		// Use fold expression to iterate over all containers even when they have different types
		(accumulate_bytes(containers), ...);

		return bytes * state.iterations();
	}

	/**
	 * Check if two values are equivalent, i.e. if they are equal or if they are within a certain tolerance
	 * @param v1 First value
	 * @param v2 Second value
	 * @return
	 */
	template<typename T, typename U, std::enable_if_t<std::is_integral_v<T> and std::is_integral_v<U>, bool> = true>
	static bool are_equivalent(const T & v1, const U & v2)
	{
		const auto are_eq = v1 == v2;

		if (not are_eq) { std::cerr << "Values are not equivalent: " << v1 << " != " << v2 << std::endl; }

		return are_eq;
	}

	/**
	 * Check if two values are equivalent, i.e. if they are equal or if they are within a certain tolerance
	 * @param v1 First value
	 * @param v2 Second value
	 * @return
	 */
	template<typename T, typename U,
	         std::enable_if_t<std::is_floating_point_v<T> and std::is_floating_point_v<U>, bool> = true>
	static bool are_equivalent(const T & v1, const U & v2)
	{
		using fp_t = std::decay_t<decltype(v1)>;

		static constexpr auto ABSOLUTE_TOLERANCE = std::numeric_limits<fp_t>::epsilon();
		static constexpr auto RELATIVE_TOLERANCE = 0.01; // 1% tolerance

		const auto abs_error = std::abs(v1 - v2);
		const auto rel_error = abs_error / std::max(std::abs(v1), std::abs(v2));

		const auto are_eq = abs_error <= ABSOLUTE_TOLERANCE or rel_error <= RELATIVE_TOLERANCE;

		if (not are_eq)
		{
			std::cerr << "Values are not equivalent: " << v1 << " != " << v2 << ". Abs. error: " << abs_error
			          << ", rel. error: " << rel_error << ". Abs. tol.: " << ABSOLUTE_TOLERANCE
			          << ", rel. tol.: " << RELATIVE_TOLERANCE << std::endl;
		}

		return are_eq;
	}

	/**
	 * Check if two values are equivalent, i.e. if they are equal or if they are within a certain tolerance
	 * @param v1 First value
	 * @param v2 Second value
	 * @return
	 */
	template<typename T, typename U,
	         std::enable_if_t<not std::is_arithmetic_v<T> or not std::is_arithmetic_v<U>, bool> = true>
	static bool are_equivalent(const T & v1, const U & v2)
	{
		return v1 == v2;
	}
} // namespace pstl

#endif //PSTL_BENCH_UTILS_H
