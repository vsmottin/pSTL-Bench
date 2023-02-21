
#ifndef MASTER_BENCHMARKS_B3_1_EXPENSIVE_BRANCHING_H
#define MASTER_BENCHMARKS_B3_1_EXPENSIVE_BRANCHING_H


#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

template<class ExecutionPolicy>
inline bool
b3_1_expensive_branching(ExecutionPolicy &policy, const std::vector<int> &input_data, const int &magic_number) {

    // we have here an expensive branch that if predicted wrongly we waste a lot of time.
    return std::all_of(policy, input_data.begin(), input_data.end(), [&magic_number](const auto &entry) {
        if (magic_number < entry) {
            // we know this branch is not likely to be hit because our input will satisfy `entry <= magic_number`
            return (3 * std::pow(std::tan(entry), std::cos(entry)) >= 1);
        } else {
            return std::sin(entry) < 1;
        }
    });


}

#endif //MASTER_BENCHMARKS_B3_1_EXPENSIVE_BRANCHING_H
