#ifndef PSTL_BENCH_B1_1_FOR_EACH_LINEAR_MANDELBROT_H
#define PSTL_BENCH_B1_1_FOR_EACH_LINEAR_MANDELBROT_H


#include <vector>
#include <cmath>
#include <algorithm>
#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace B1 {

    int calculate_mandelbrot(const auto &entry, const double dx) {
        constexpr auto dy = (2) / (50 - 1);

        const auto x = -2.0 + entry * dx; // current real value
        constexpr auto y =
                1.0 - 17 * dy; // current imaginary value, stays the same since only 17 row calucalted out of 50

        auto zReal = x;
        auto zImag = y;

        constexpr auto limit = 200;

        for (int i = 0; i < limit; ++i) {
            const auto r2 = zReal * zReal;
            const auto i2 = zImag * zImag;

            if (r2 + i2 > 4.0) return i;

            zImag = 2.0 * zReal * zImag + y;
            zReal = r2 - i2 + x;
        }

        return limit;
    }

    template<class ExecutionPolicy,
            typename BASE_POLICY = suite::base_type<ExecutionPolicy>>
    inline void
    b1_1_for_each_linear_mandelbrot(ExecutionPolicy &policy,
                                    const suite::int_vec<BASE_POLICY> &pixel_x) {

        // calculating the 17 row of mandelbrot with an adjustable limit.
        // adjusted from https://github.com/dario-marvin/Mandelbrot/blob/master/Mandelbrot.cc

        const auto dx = (1.0 - -2.0) / (pixel_x.size() - 1);

        std::for_each(policy, pixel_x.begin(), pixel_x.end(), [dx](const auto &entry) {
            int val = calculate_mandelbrot(entry, dx);
#ifndef ONLY_GPU
            benchmark::DoNotOptimize(val);
#endif
        });

    }

}

#endif //PSTL_BENCH_B1_1_FOR_EACH_LINEAR_MANDELBROT_H
