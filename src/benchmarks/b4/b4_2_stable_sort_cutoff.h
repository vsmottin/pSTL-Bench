
#ifndef MASTER_BENCHMARKS_B4_2_STABLE_SORT_CUTOFF_H
#define MASTER_BENCHMARKS_B4_2_STABLE_SORT_CUTOFF_H

#include <algorithm>
#include <vector>

namespace B4 {

    template<class ExecutionPolicy>
    inline void
    b4_2_stable_sort_cutoff(ExecutionPolicy &&policy, std::vector<int> &input_data) {

        std::stable_sort(policy, input_data.begin(), input_data.end());

    }

}

#endif //MASTER_BENCHMARKS_B4_2_STABLE_SORT_CUTOFF_H
