#ifdef PSTL_BENCH_USE_HPX
#include <hpx/hpx_main.hpp>
#endif

#include <thread>

#include <benchmark/benchmark.h>

#include <execution> 

#if defined(PSTL_BENCH_USE_TBB) or defined(PSTL_BENCH_USE_HPX)
#include "pstl/utils/thread_control.h"
#endif

#ifdef PSTL_BENCH_USE_LIKWID
#include <likwid-marker.h>
#endif

#include "pstl/benchmarks/pstl-benchmarks.h"

// Run the benchmark
int main(int argc, char ** argv)
{
#ifdef PSTL_BENCH_USE_TBB
	auto tbbThreadControl = init_tbb_thread_control();
#endif

	benchmark::AddCustomContext("std::thread::hardware_concurrency()",
	                            std::to_string(std::thread::hardware_concurrency()));

#if defined(PSTL_BENCH_USE_TBB)
	benchmark::AddCustomContext("tbb #threads", std::to_string(tbb::global_control::active_value(
	                                                tbb::global_control::max_allowed_parallelism)));
#elif defined(PSTL_BENCH_USE_GNU_PSTL)
	benchmark::AddCustomContext("omp #threads", std::to_string(omp_get_max_threads()));
#elif defined(PSTL_BENCH_USE_HPX)
	benchmark::AddCustomContext("hpx #threads", std::to_string(hpx::get_num_worker_threads()));
#endif

#ifdef PSTL_BENCH_USE_PAPI
	benchmark::AddCustomContext("PAPI", "enabled");
#endif

#ifdef PSTL_BENCH_USE_LIKWID
	benchmark::AddCustomContext("LIKWID", "enabled");
	LIKWID_MARKER_INIT;
#endif

	benchmark::Initialize(&argc, argv);
	if (benchmark::ReportUnrecognizedArguments(argc, argv)) { return 1; }
	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();

#ifdef PSTL_BENCH_USE_LIKWID
	LIKWID_MARKER_CLOSE;
#endif

	return EXIT_SUCCESS;
}
