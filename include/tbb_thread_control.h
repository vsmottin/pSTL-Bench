
#ifndef PSTL_BENCH_TBB_THREAD_CONTROL_H
#define PSTL_BENCH_TBB_THREAD_CONTROL_H

#include <string>

#include <tbb/global_control.h>

/**
 * Limits the number of threads globally used by tbb.
 * To do so just set the env `OMP_NUM_THREADS`
 */
std::unique_ptr<tbb::global_control> init_tbb_thread_control()
{
	const char * number_of_threads_env = std::getenv("OMP_NUM_THREADS");

	if (number_of_threads_env == nullptr)
	{
		// no number_of_threads defined
		return nullptr;
	}

	const auto number_of_threads = std::stoi(number_of_threads_env);

	return std::make_unique<tbb::global_control>(tbb::global_control::max_allowed_parallelism, number_of_threads);
}


#endif //PSTL_BENCH_TBB_THREAD_CONTROL_H
