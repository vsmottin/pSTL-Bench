
#ifndef MASTER_BENCHMARKS_B5_1_FIND_H
#define MASTER_BENCHMARKS_B5_1_FIND_H

#include <algorithm>
#include <vector>

namespace B5 {

    template<class ExecutionPolicy, class C,
            typename T = typename C::value_type,
            typename Iterator = typename C::const_iterator>
    inline Iterator b5_1_find(ExecutionPolicy &&policy, const C &container, const T &find_val) {
        return std::find(policy, container.begin(), container.end(), find_val);
    }

}

#endif //MASTER_BENCHMARKS_B5_1_FIND_H
