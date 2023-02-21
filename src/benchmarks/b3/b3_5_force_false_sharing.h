
#ifndef MASTER_BENCHMARKS_B3_5_FORCE_FALSE_SHARING_H
#define MASTER_BENCHMARKS_B3_5_FORCE_FALSE_SHARING_H

#include <vector>
#include <algorithm>
#include <new>
#include <ranges>
#include "../benchmark_utils.h"

//TODO: fix! This will not result in cache line invalidation. We simple read and never write!

struct force_false_sharing_struct {
    int number;
    int second_field;
};

// statically assert that the struct indeed does not fill a whole cache line
static_assert((sizeof(force_false_sharing_struct) <= suite::hardware_constructive_interference_size));

template<class ExecutionPolicy>
inline std::size_t
b3_5_force_false_sharing(ExecutionPolicy &policy, const std::vector<force_false_sharing_struct> &input_data) {

    // this call should result in two threads touching the same cache lines (if not properly scheduled)
    return std::count_if(policy, input_data.begin(), input_data.end(), [](const auto &v) {
        return v.number + v.second_field >= 0;
    });
}

#endif //MASTER_BENCHMARKS_B3_5_FORCE_FALSE_SHARING_H
