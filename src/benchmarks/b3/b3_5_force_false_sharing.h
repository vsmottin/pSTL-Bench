
#ifndef MASTER_BENCHMARKS_B3_5_FORCE_FALSE_SHARING_H
#define MASTER_BENCHMARKS_B3_5_FORCE_FALSE_SHARING_H

#include <vector>
#include <algorithm>
#include <new>
#include <ranges>

struct force_false_sharing_struct {
    int number;
    int second_field;
};

// statically assert that the struct indeed does not fill a whole cache line
static_assert((sizeof(force_false_sharing_struct) <= suite::hardware_constructive_interference_size));

template<class ExecutionPolicy>
inline std::size_t
b3_5_force_false_sharing(ExecutionPolicy &policy, const std::vector<force_false_sharing_struct> &input_data) {

    const auto &view = std::views::iota(0, static_cast<int>(input_data.size()));

    // we use the range because we do not want to move the input data array around.
    // this call should result in two threads touching the same cache lines (if not properly scheduled)
    return std::count_if(policy, view.begin(), view.end(), [&](const auto &index) {
        return input_data[index].number + input_data[index].second_field >= 0;
    });
}

#endif //MASTER_BENCHMARKS_B3_5_FORCE_FALSE_SHARING_H
