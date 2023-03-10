
#ifndef MASTER_BENCHMARKS_B5_3_UNIQUE_COPY_H
#define MASTER_BENCHMARKS_B5_3_UNIQUE_COPY_H

#include <algorithm>
#include <vector>
#include <cmath>


namespace B5 {

    template<class ExecutionPolicy>
    inline void
    b5_3_unique_copy_default(ExecutionPolicy &&policy, std::vector<int> &container, std::vector<int> &result) {

        std::unique_copy(policy, container.begin(), container.end(), result.begin());
    }

}

#endif //MASTER_BENCHMARKS_B5_3_UNIQUE_COPY_H
