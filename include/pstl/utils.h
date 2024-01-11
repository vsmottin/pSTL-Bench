
#ifndef PSTL_BENCH_UTILS_H
#define PSTL_BENCH_UTILS_H

#include <algorithm>
#include <atomic>
#include <chrono>
#include <concepts>
#include <ctime>
#include <execution>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

#ifdef USE_PARALLEL_ALLOCATOR
#include "parallel_allocator.h"
#endif

#include "elem_t.h"

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


#define WRAP_TIMING(code)                                                                          \
	auto start = std::chrono::high_resolution_clock::now();                                        \
	code;                                                                                          \
	auto end             = std::chrono::high_resolution_clock::now();                              \
	auto elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(end - start); \
	state.SetIterationTime(elapsed_seconds.count());


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

		std::mt19937                     mt_engine(std::time(nullptr));
		std::uniform_real_distribution<> dist(lower_bound, upper_bound);

		auto dist_vec = pstl::get_vec<ExecutionPolicy, pstl::vec<T, ExecutionPolicy>>(size);

		std::generate(execution_policy, dist_vec.begin(), dist_vec.end(), [&]() { return (T) dist(mt_engine); });

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
	template<typename ExecutionPolicy, typename ValueType = pstl::elem_t,
	         typename Container = pstl::vec<ValueType, ExecutionPolicy>,
	         typename Size_type = typename Container::size_type>
	Container generate_decrement(const ExecutionPolicy execution_policy, const Size_type & size,
	                             const ValueType start_val, const ValueType decrement = 1)
	{
		auto generatedVec = pstl::get_vec<ExecutionPolicy, ValueType, Container>(size);

		// this vector of indices does not need to be parallel allocated since it is not performance critical
		for (Size_type index = 0; index < size; ++index)
		{
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
	template<typename ExecutionPolicy, typename ValueType = pstl::elem_t,
	         typename Container = pstl::vec<ValueType, ExecutionPolicy>,
	         typename Size_type = typename Container::size_type>
	Container generate_increment(const ExecutionPolicy execution_policy, const Size_type & size, const ValueType start,
	                             const ValueType increment)
	{
		return pstl::generate_decrement(execution_policy, size, start, -increment);
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


	template<typename T>
	concept printable = requires(T t) {
		{
			std::cout << t
		} -> std::same_as<std::ostream &>;
	};

	/**
	 * Check if two values are equivalent, i.e. if they are equal or if they are within a certain tolerance
	 * @param v1 First value
	 * @param v2 Second value
	 * @return
	 */
	static bool are_equivalent(const auto & v1, const auto & v2)
	{
		return v1 == v2;
	}

	/**
	 * Check if two values are equivalent, i.e. if they are equal or if they are within a certain tolerance
	 * @param v1 First value
	 * @param v2 Second value
	 * @return
	 */
	static bool are_equivalent(const std::integral auto & v1, const std::integral auto & v2)
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
	static bool are_equivalent(const std::floating_point auto & v1, const std::floating_point auto & v2)
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

} // namespace pstl

#endif //PSTL_BENCH_UTILS_H
