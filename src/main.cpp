#ifdef USE_TBB
// we have the case that we use gcc. this means tbb will be used for parallel stl
// potential thread limits have to be configured

#include <tbb_thread_control.h>

#endif

#include "benchmarks/find/group.h"
#include "benchmarks/count_if/group.h"
#include "benchmarks/index_based_iterations/b9_group.h"
#include "benchmarks/nested_parallelism/b1_group.h"
#include "benchmarks/optimization_scans/b6_group.h"
#include "benchmarks/reduce/group.h"
#include "benchmarks/sequential_fallback/b4_group.h"
#include "benchmarks/specialized_techniques/b5_group.h"
#include "benchmarks/specific_versus_custom/b7_group.h"
#include <benchmark/benchmark.h>

COUNT_IF_GROUP
FIND_GROUP
REDUCE_GROUP
NESTED_PARALLELISM_GROUP
SEQUENTIAL_FALLBACK_GROUP
SPECIALIZED_TECHNIQUES_GROUP
OPTIMIZED_SCAN_GROUP
SPECIFIC_VS_CUSTOM_GROUP
INDEX_BASED_ITERATIONS_GROUP

// Run the benchmark
int main(int argc, char ** argv)
{
#ifdef USE_TBB
	auto tbbThreadControl = init_tbb_thread_control();
#endif

	char   arg0_default[] = "benchmark";
	char * args_default   = arg0_default;
	if (!argv)
	{
		argc = 1;
		argv = &args_default;
	}
	benchmark::Initialize(&argc, argv);
	if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();

#ifdef USE_TBB
	tbbThreadControl = nullptr;
#endif

	return 0;
}
