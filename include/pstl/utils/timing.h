#pragma once

#include <benchmark/benchmark.h>

#include <chrono>

#include <numa.h>

#ifdef USE_PAPI
#include <papi.h>

#define PRINT_PAPI_ERROR(retval, zone_name)                                                                          \
	{                                                                                                                \
		std::cerr << "Error " << retval << " for zone " << zone_name << " : " << PAPI_strerror(retval) << std::endl; \
	}
#endif

#ifdef USE_LIKWID
#include <likwid.h>
#endif

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
			std::forward<Function>(f)();
		}

		// 2. Reset the affinity to the default bitmask
		sched_setaffinity(0, sizeof(default_cpuset), &default_cpuset);
	}

	inline void hw_counters_begin(const benchmark::State & state)
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

	inline void hw_counters_end(const benchmark::State & state)
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

	// This function is used to wrap the timing of a function call -> F(args...) returning void
	template<typename F, typename... Args>
	auto wrap_timing(benchmark::State & state, F && f, Args &&... args)
	    -> std::enable_if_t<std::is_void_v<std::invoke_result_t<F, Args...>>> // SFINAE
	{
		hw_counters_begin(state);
		const auto start = std::chrono::high_resolution_clock::now();
		std::forward<F>(f)(std::forward<Args>(args)...);
		const auto end = std::chrono::high_resolution_clock::now();
		hw_counters_end(state);
		state.SetIterationTime(std::chrono::duration<double>(end - start).count());
	}

	// This function is used to wrap the timing of a function call -> F(args...) returning a value
	template<typename F, typename... Args>
	auto wrap_timing(benchmark::State & state, F && f, Args &&... args)
	    -> std::enable_if_t<not std::is_void_v<std::invoke_result_t<F, Args...>>, std::invoke_result_t<F, Args...>>
	{
		using return_t = std::invoke_result_t<F, Args...>;
		hw_counters_begin(state);
		const auto start = std::chrono::high_resolution_clock::now();
		return_t   rv    = std::forward<F>(f)(std::forward<Args>(args)...);
		const auto end   = std::chrono::high_resolution_clock::now();
		hw_counters_end(state);
		state.SetIterationTime(std::chrono::duration<double>(end - start).count());
		return rv;
	}
} // namespace pstl