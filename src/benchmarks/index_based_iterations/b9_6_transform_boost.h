
#ifndef PSTL_BENCH_B9_6_TRANSFORM_BOOST_H
#define PSTL_BENCH_B9_6_TRANSFORM_BOOST_H

#ifndef SKIP_BOOST

#include <boost/iterator/counting_iterator.hpp>
#include <vector>
#include <algorithm>
#include <benchmark_utils.h>

namespace B9 {

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>
    >
    inline void
    b9_6_transform_boost(ExecutionPolicy &&policy,
                         const suite::int_vec<BASE_POLICY> &input_data,
                         suite::int_vec<BASE_POLICY> &res) {

        std::transform(policy,
                       boost::counting_iterator<int>(0),
                       boost::counting_iterator<int>(input_data.size()),
                       res.begin(), [&](const auto &index) {
                    return input_data[index] + 10;
                });

    }

}

#endif

#endif //PSTL_BENCH_B9_6_TRANSFORM_BOOST_H
