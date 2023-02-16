
#ifndef MASTER_BENCHMARKS_B3_6_NO_FALSE_SHARING_H
#define MASTER_BENCHMARKS_B3_6_NO_FALSE_SHARING_H

#include <vector>
#include <algorithm>
#include <new>
#include <ranges>
#include "../benchmark_utils.h"

struct alignas(suite::hardware_destructive_interference_size) no_false_sharing_struct {
    int number;
    int ignored_field;
};

// statically assert that the struct indeed does fill a whole cache line
// and will not share it with other
static_assert((sizeof(no_false_sharing_struct) >= suite::hardware_destructive_interference_size));

template<class ExecutionPolicy>
inline std::size_t
b3_6_no_false_sharing(ExecutionPolicy &policy, const std::vector<no_false_sharing_struct> &input_data) {

    const auto &view = std::views::iota(1, static_cast<int>(input_data.size()) + 1);

    // we use the range because we do not want to move the input data array arround.
    return std::count_if(policy, view.begin(), view.end(), [&](const auto &index) {
        return input_data[index].number >= 0;
    });
}

#endif //MASTER_BENCHMARKS_B3_6_NO_FALSE_SHARING_H
