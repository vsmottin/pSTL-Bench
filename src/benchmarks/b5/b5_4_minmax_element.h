
#ifndef MASTER_BENCHMARKS_B5_4_MINMAX_ELEMENT_H
#define MASTER_BENCHMARKS_B5_4_MINMAX_ELEMENT_H

#include <algorithm>
#include <vector>
#include <utility>

namespace B5 {

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>,
            typename VEC = typename suite::int_vec<BASE_POLICY>,
            typename CONST_ITERATOR = VEC::const_iterator
    >
    inline std::pair<CONST_ITERATOR, CONST_ITERATOR>
    b5_4_minmax_element(ExecutionPolicy &&policy, const VEC &container) {
        return std::minmax_element(policy, container.begin(), container.end());
    }

}

#endif //MASTER_BENCHMARKS_B5_4_MINMAX_ELEMENT_H
