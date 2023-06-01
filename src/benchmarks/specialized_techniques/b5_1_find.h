
#ifndef PSTL_BENCH_B5_1_FIND_H
#define PSTL_BENCH_B5_1_FIND_H

#include <algorithm>
#include <vector>
#include <benchmark_utils.h>

namespace B5 {

    template<class ExecutionPolicy, class C,
            typename T = typename C::value_type,
            typename Iterator = typename C::const_iterator>
    inline Iterator b5_1_find(ExecutionPolicy &&policy, const C &container, const T &find_val) {
        return std::find(policy, container.begin(), container.end(), find_val);
    }

}

#endif //PSTL_BENCH_B5_1_FIND_H
