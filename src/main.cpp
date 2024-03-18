#ifdef USE_HPX
#include <hpx/hpx_main.hpp>
#endif

#include <thread>

#include <benchmark/benchmark.h>

#ifdef USE_TBB
#include <tbb_thread_control.h>
#endif

#ifdef USE_LIKWID
#include <likwid-marker.h>
#endif

#include "pstl/benchmarks/pstl-benchmarks.h"

// Run the benchmark
int main(int argc, char ** argv)
{
#ifdef USE_TBB
	auto tbbThreadControl = init_tbb_thread_control();
#endif

	char   arg0_default[] = "benchmark";
	char * args_default   = arg0_default;
	if (argc == 0)
	{
		argc = 1;
		argv = &args_default;
	}

	benchmark::AddCustomContext("std::thread::hardware_concurrency()",
	                            std::to_string(std::thread::hardware_concurrency()));

#ifdef USE_TBB
	benchmark::AddCustomContext("tbb #threads", std::to_string(tbb::global_control::active_value(
	                                                tbb::global_control::max_allowed_parallelism)));
#endif


#if defined(USE_OMP) or defined(USE_GNU_PSTL)
	benchmark::AddCustomContext("omp_get_max_threads()", std::to_string(omp_get_max_threads()));
#endif

#ifdef USE_PAPI
	benchmark::AddCustomContext("PAPI", "enabled");
#endif

#ifdef USE_LIKWID
	benchmark::AddCustomContext("LIKWID", "enabled");
	LIKWID_MARKER_INIT;
#endif

	benchmark::Initialize(&argc, argv);
	if (benchmark::ReportUnrecognizedArguments(argc, argv)) { return 1; }
	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();

#ifdef USE_TBB
	tbbThreadControl = nullptr;
#endif

#ifdef USE_LIKWID
	LIKWID_MARKER_CLOSE;
#endif

	return 0;
}
