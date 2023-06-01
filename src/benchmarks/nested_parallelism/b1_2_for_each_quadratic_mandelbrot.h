
#ifndef PSTL_BENCH_B1_2_FOR_EACH_QUADRATIC_MANDELBROT_H
#define PSTL_BENCH_B1_2_FOR_EACH_QUADRATIC_MANDELBROT_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <benchmark/benchmark.h>

#include <benchmark_utils.h>


namespace B1 {

    // adjusted from
    // https://github.com/dario-marvin/Mandelbrot/blob/master/Mandelbrot.cc
    inline int b1_2_mandelbrot(double real, double imag) {
        constexpr auto limit = 100;
        auto zReal = real;
        auto zImag = imag;

        for (int i = 0; i < limit; ++i) {
            const auto r2 = zReal * zReal;
            const auto i2 = zImag * zImag;

            if (r2 + i2 > 4.0) return i;

            zImag = 2.0 * zReal * zImag + imag;
            zReal = r2 - i2 + real;
        }
        return limit;
    }

    template<class OuterExecutionPolicy, class InnerExecutionPolicy>
    inline void
    b1_2_for_each_quadratic_mandelbrot(OuterExecutionPolicy &&outerExecutionPolicy,
                                       InnerExecutionPolicy &&innerExecutionPolicy,
                                       const suite::int_vec<suite::base_type<InnerExecutionPolicy>> &input_data) {

        const auto width = input_data.size();
        const auto heigth = input_data.size();

        constexpr auto x_start = -2.0;
        constexpr auto x_fin = 1.0;
        constexpr auto y_start = -1.0;
        constexpr auto y_fin = 1.0;

        const auto dx = (x_fin - x_start) / (width - 1);
        const auto dy = (y_fin - y_start) / (heigth - 1);


        // quite straight forward std::for_each. The body of the lambda has no intention behind it, the goal was just
        // to have a big enough computation that takes some amount of time.
        std::for_each(outerExecutionPolicy, input_data.begin(), input_data.end(), [&](const auto &i) {

            // nested parallel loop with same strategy
            std::for_each(innerExecutionPolicy, input_data.begin(), input_data.end(), [&](const auto &j) {

                const auto x = x_start + j * dx; // current real value
                const auto y = y_fin - i * dy; // current imaginary value

                int value = b1_2_mandelbrot(x, y);

                benchmark::DoNotOptimize(value);
            });

        });

    }
}

#endif //PSTL_BENCH_B1_2_FOR_EACH_QUADRATIC_MANDELBROT_H
