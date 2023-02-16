
#ifndef MASTER_BENCHMARKS_B4_1_MERGE_CUTOFF_H
#define MASTER_BENCHMARKS_B4_1_MERGE_CUTOFF_H

#include <algorithm>
#include <vector>

template<class ExecutionPolicy>
inline std::vector<int>
b4_1_merge_cutoff(ExecutionPolicy &&policy, const std::vector<int> &v1, const std::vector<int> &v2) {

    std::vector<int> result(v1.size() + v2.size());

    std::merge(policy, v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());

    return result;
}


#endif //MASTER_BENCHMARKS_B4_1_MERGE_CUTOFF_H
