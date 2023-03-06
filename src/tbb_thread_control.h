
#ifndef MASTER_BENCHMARKS_TBB_THREAD_CONTROL_H
#define MASTER_BENCHMARKS_TBB_THREAD_CONTROL_H

#include <cstdlib>
#include <sstream>
#include <string>

#include <tbb/global_control.h>

/**
 * Limits the number of threads globally used by tbb.
 * To do so just set the env `OMP_NUM_THREADS`
 */
void init_tbb_thread_control() {

    const auto number_of_threads_env = std::getenv("OMP_NUM_THREADS");

    if (number_of_threads_env == nullptr) {
        // no number_of_threads defined
        return;
    }

    std::stringstream sstream(number_of_threads_env);

    std::size_t number_of_threads;
    sstream >> number_of_threads;


    [[maybe_unused]] tbb::global_control global_limit(tbb::global_control::max_allowed_parallelism, number_of_threads);
}


#endif //MASTER_BENCHMARKS_TBB_THREAD_CONTROL_H
