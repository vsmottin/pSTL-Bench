#ifdef USE_HPX
#include <hpx/hpx_main.hpp>
#endif

#include "benchmarks/adjacent_difference/group.h"
#include "benchmarks/adjacent_find/group.h"
#include "benchmarks/all_of/group.h"
#include "benchmarks/any_of/group.h"
#include "benchmarks/copy/group.h"
#include "benchmarks/copy_if/group.h"
#include "benchmarks/copy_n/group.h"
#include "benchmarks/count/group.h"
#include "benchmarks/count_if/group.h"
#include "benchmarks/equal/group.h"
#include "benchmarks/exclusive_scan/group.h"
#include "benchmarks/fill/group.h"
#include "benchmarks/find/group.h"
#include "benchmarks/for_each/group.h"
#include "benchmarks/generate/group.h"
#include "benchmarks/includes/group.h"
#include "benchmarks/inclusive_scan/group.h"
#include "benchmarks/inplace_merge/group.h"
#include "benchmarks/is_sorted/group.h"
#include "benchmarks/lexicographical_compare/group.h"
#include "benchmarks/merge/group.h"
#include "benchmarks/min_element/group.h"
#include "benchmarks/mismatch/group.h"
#include "benchmarks/none_of/group.h"
#include "benchmarks/partial_sort/group.h"
#include "benchmarks/reduce/group.h"
#include "benchmarks/sort/group.h"

#include <thread>

#include <benchmark/benchmark.h>

#ifdef USE_TBB
#include <tbb_thread_control.h>
#endif

ADJACENT_DIFFERENCE_GROUP
ADJACENT_FIND_GROUP
ANY_OF_GROUP
ALL_OF_GROUP
COPY_GROUP
COPY_IF_GROUP
COPY_N_GROUP
COUNT_GROUP
COUNT_IF_GROUP
EQUAL_GROUP
EXCLUSIVE_SCAN_GROUP
FILL_GROUP
FIND_GROUP
FOR_EACH_GROUP
GENERATE_GROUP
INCLUDES_GROUP
INPLACE_MERGE_GROUP
INCLUSIVE_SCAN_GROUP
IS_SORTED_GROUP
LEXICOGRAPHICAL_COMPARE_GROUP
MERGE_GROUP
MIN_ELEMENT_GROUP
MISMATCH_GROUP
NONE_OF_GROUP
PARTIAL_SORT_GROUP
REDUCE_GROUP
SORT_GROUP

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

	benchmark::AddCustomContext("std::thread::hardware_concurrency()",
	                            std::to_string(std::thread::hardware_concurrency()));

#ifdef USE_TBB
	benchmark::AddCustomContext("tbb #threads", std::to_string(tbb::global_control::active_value(
	                                                tbb::global_control::max_allowed_parallelism)));
#endif


#if defined(USE_OMP) or defined(USE_GNU_PSTL)
	benchmark::AddCustomContext("omp_get_max_threads()", std::to_string(omp_get_max_threads()));
#endif

	benchmark::Initialize(&argc, argv);
	if (benchmark::ReportUnrecognizedArguments(argc, argv)) { return 1; }
	benchmark::RunSpecifiedBenchmarks();
	benchmark::Shutdown();

#ifdef USE_TBB
	tbbThreadControl = nullptr;
#endif

	return 0;
}
