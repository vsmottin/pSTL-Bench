# Hypotheses

## H1

> Certain parallel backend perform/scale better on nested parallelism for homogeneous workloads

**Why important:**

* If this hypothesis is true, this may have an impact the decision-making process on what backend a
  developer may choose when working on a project. If parallel backend A scaled better on nested parallelism than B, a
  developer may prefer to use A over B for a certain subset of application.
* If this hypothesis is false, we can say the performance portability increases.

**How to test it:**

1. *TIME*
    1. Compare the parallel (std::execution::par) runtimes of `b1_1_for_each_linear` on all compilers for all input
       sizes.
    2. Compare the parallel (std::execution::par,std::execution::par) runtimes of `b1_2_for_each_quadratic` on all
       compilers
       for all input sizes.
    3. Compare the parallel (std::execution::par) runtimes of `b1_4_for_each_exponential` on all compilers for all input
       sizes.


2. *Strong Scaling*
    1. Compare strong scaling of `b1_1_for_each_linear` for all compilers on fixed input size (1 million)
    2. Compare strong scaling of `b1_2_for_each_quadratic` for all compilers on fixed input size (1 million)
    3. Compare strong scaling of `b1_4_for_each_exponential` for all compilers on fixed input size (32 -> will result in
       2^32 calls)

**Metrics Involved:**

* Just Time
* Strong scaling

**What benchmarks cover it:**

1. `b1_1_for_each_linear_seq`: has homogeneous workflow `std::min(std::sin(entry), std::tan(entry))`
2. `b1_1_for_each_linear_par`: has homogeneous workflow `std::min(std::sin(entry), std::tan(entry))`
3. `b1_2_for_each_quadratic_outer_std::execution::sequential_policy_seq`: has homogeneous
   workflow `std::min(std::sin(entry), std::tan(entry))`
4. `b1_2_for_each_quadratic_outer_std::execution::parallel_policy_par`: has homogeneous
   workflow `std::min(std::sin(entry), std::tan(entry))`
5. `b1_4_for_each_exponential_seq`: has homogeneous workflow `std::min(std::sin(entry), std::tan(entry))`
6. `b1_4_for_each_exponential_par`: has homogeneous workflow `std::min(std::sin(entry), std::tan(entry))`

**Compilers/Backends**

* GCC(TBB)
* NVC(OMP)

**GPU COMPATIBILITY:**

* NO this sadly does not work since NVC(GPU) does not support nested parallelism.

**Hypothesis is true when:**

* There is a significant different in strong scaling / runtime between compilers for each
  type of nested parallelism.

**Performance Portability Calculation:**

* for this group we can "calculate" a performance probability by looking at the strong scaling speedup every compiler
  has when using
  the max amount of cores. (aka running with 1M entries at max core) (insipred by [1])

  |          | achieved | perfect | efficiency  | 
        |----------|----------|---------|-------------|
  | GCC(TBB) | 12       | 16      | 12/16=0.75  |
  | NVC(OMP) | 16       | 16      | 16/16=1     |
  | NVC(GPU) | 0        | 0       | 0           |
  | Intel    | 14       | 16      | 14/16=0.875 |

  Performance Portability for `{GCC(TBB), NVC(OMP), NVC(GPU), Intel}` = 0

  Performance Portability for `{GCC(TBB), NVC(OMP), Intel}` = `3/((1/0,75)+ (1/1) + (1/0,875))` = 86.3%

* Later we can compare the performance compatibilty calculated above from machine to machine (aka nebula vs tesla vs
  vsc)

## H2

> When using nested parallelism

## H3

> Certain parallel backend perform/scale better on nested parallelism for heterogeneous workloads

**Why important:**

* Same as H1
* Heterogeneous workloads leads to some threads having less computation to perform than others.

**How to test it:**

1. *TIME*
    1. Compare the parallel (std::execution::par) runtimes of `b1_1_for_each_linear_mandelbrot` on all compilers for all
       input
       sizes.
    2. Compare the parallel (std::execution::par,std::execution::par) runtimes of `b1_2_for_each_quadratic_mandelbrot`
       on all
       compilers
       for all input sizes.

2. *Strong Scaling*
    1. Compare strong scaling of `b1_1_for_each_linear_mandelbrot` for all compilers on fixed input size (1 million)
    2. Compare strong scaling of `b1_2_for_each_quadratic_mandelbrot` for all compilers on fixed input size (1 million)

3. *Instructions per Second (ips)*
    1. Compare ips for `b1_1_for_each_linear_mandelbrot` for all compilers on for all input size
    2. Compare ips for `b1_1_for_each_quadratic_mandelbrot` for all compilers on for all input size

**Metrics Involved:**

* Just Time
* Strong scaling
* Instructions per Second (ips)

**What benchmarks cover it:**

* `b1_1_for_each_linear_mandelbrot_seq`: computes the first row (pixels `[0,0] - [0,size]`) of mandelbrot.
* `b1_1_for_each_linear_mandelbrot_par`: computes the first row (pixels `[0,0] - [0,size]`) of mandelbrot.
* `b1_2_for_each_quadratic_mandelbrot_outer_std::execution::parallel_policy_seq`: computes a mandelbrot image (
  pixels `[0,0] - [size,size]`).
* `b1_2_for_each_quadratic_mandelbrot_outer_std::execution::parallel_policy_par`: computes a mandelbrot image (
  pixels `[0,0] - [size,size]`).

**Compilers/Backends**

* GCC(TBB)
* NVC(OMP)

**GPU COMPATIBILITY:**
The quadratic implementation sadly does not work since NVC(GPU) does not support nested parallelism. But for linear I
have to check.

## References

* [1] S. J. Pennycook, J. D. Sewall, and V. W. Lee. “A Metric for Performance Portability”. In: CoRR abs/1611.07409 (
  2016). 
