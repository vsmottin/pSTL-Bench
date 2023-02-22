
#ifndef MASTER_BENCHMARKS_B5_4_MINMAX_ELEMENT_H
#define MASTER_BENCHMARKS_B5_4_MINMAX_ELEMENT_H

#include <algorithm>
#include <vector>
#include <utility>

namespace B5 {

    template<class ExecutionPolicy>
    inline std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
    b5_4_minmax_element(ExecutionPolicy &&policy, const std::vector<int> &container) {
        return std::minmax_element(policy, container.begin(), container.end());
    }

}

#endif //MASTER_BENCHMARKS_B5_4_MINMAX_ELEMENT_H
