
#ifndef MASTER_BENCHMARKS_B3_6_NO_FALSE_SHARING_H
#define MASTER_BENCHMARKS_B3_6_NO_FALSE_SHARING_H

#include <vector>
#include <algorithm>
#include <new>
#include <ranges>
#include "../benchmark_utils.h"

//TODO: check if this really results in no false sharing

struct alignas(suite::hardware_destructive_interference_size) no_false_sharing_struct {
    int number;
    int second_field;
};

// statically assert that the struct indeed does fill a whole cache line
// and will not share it with other
static_assert((sizeof(no_false_sharing_struct) >= suite::hardware_destructive_interference_size));

template<class ExecutionPolicy>
inline std::size_t
b3_6_no_false_sharing(ExecutionPolicy &policy, const std::vector<no_false_sharing_struct> &input_data) {

    // this call should result in two threads not touching the same cache lines (scheduling should not make this worse)
    return std::count_if(policy, input_data.begin(), input_data.end(), [](const auto &v) {
        return v.number + v.second_field >= 0;
    });
}

#endif //MASTER_BENCHMARKS_B3_6_NO_FALSE_SHARING_H
