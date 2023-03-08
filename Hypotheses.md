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

* Later we can compare the performance portability calculated above from machine to machine (aka nebula vs tesla vs
  vsc)

## H2

> The order of the parallelism (outer seq, inner par vs outer par, inner seq) has a significant impact on performance.

**Why important:**

* C++ provides a variety of execution policies to use. Choosing the "right order" in nested parallelism may change
  performance.
* Obviously, this will be true but how significant the impact is might vary per backend.

**How to test it:**

1. *Time*
    1. Compare the runtime of `b1_2_for_each_quadratic_outer_std::execution::sequenced_policy_par` with the runtime
       of `b1_2_for_each_quadratic_outer_std::execution::parallel_policy_seq` for each compiler and for every input size

2. *Strong Scaling*
    1. Compare strong scaling of `b1_2_for_each_quadratic_outer_std::execution::sequenced_policy_par` with the runtime
       of `b1_2_for_each_quadratic_outer_std::execution::parallel_policy_seq` for each compiler and fixed input size (
       32.768)

**Metrics Involved:**

* Time
* Strong scaling

**What benchmarks cover it:**

1. `b1_2_for_each_quadratic_outer_std::execution::sequenced_policy_par`: outer loop sequential inner loop parallel
2. `b1_2_for_each_quadratic_outer_std::execution::parallel_policy_seq`: outer loop parallel inner loop sequential

**Compilers/Backends**

* GCC(TBB)
* NVC(OMP)

**GPU COMPATIBILITY:**

* NO

**Hypothesis is true when:**

* There is a significant difference between the runtime of (par, seq) and (seq, par). HINT: already tested and depends
  on compiler

**Performance Portability Calculation:**

* Since we know that (par, seq) will be better than (seq,par) we can check the stddev of the performance improvement
  from (seq, par) to (par,seq) for every compiler. For example:

  |          | (seq,par) | (par,seq) | faster |
                      |----------|-----------|--------|------------|
  | GCC(TBB) | 10s       | 5s        | 2x     |
  | NVC(OMP) | 12s       | 8s        | 1.5x   |
  | NVC(GPU) | 0         | 0         | 0      |
  | Intel    | 9         | 1         | 9x     |

  stddev(2,1.5,9) = 3.4 inidcating that the difference is quite significant when changing compilers.
  stddev(2,1.5) = 0.25 inidcating that the difference is not significant when changing compilers.

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

**Hypothesis is true when:**

* There is a significant different in strong scaling / runtime between compilers for each
  type of nested parallelism.

**Performance Portability Calculation:**

* None

## H4

> Different compilers/backends may fallback to sequential algorithms, leading to better performance.

**Why important:**

* If there are fallback mechanism this will allow the developer to not think about including customized fallback
  mechanism.
* If there is a fallback (based on input size) but the computation (e.g. the predicate) is expensive the fallback may
  lead to drastically worse performance when running parallel.

**How to test it:**

1. *Time*
    1. Compare the runtime of `b4_1_merge_cutoff_wrapper_par` for every input size for every compiler
    2. Compare the runtime of `b4_2_stable_sort_cutoff_already_sorted_par` for every input size for every compiler
    3. Compare the runtime of `b4_2_stable_sort_cutoff_decrement_sorted_par` for every input size for every compiler
    4. Compare the runtime of `b4_2_stable_sort_cutoff_not_sorted_par` for every input size for every compiler
    5. Compare the runtime of `b4_3_set_union_cutoff_one_empty_par` for every input size for every compiler
    6. Compare the runtime of `b4_3_set_union_cutoff_one_wholly_greater_par` for every input size for every compiler
    7. Compare the runtime of `b4_3_set_union_cutoff_front_overhang_par` for every input size for every compiler
    8. Compare the runtime of `b4_4_set_difference_cutoff_left_empty_par` for every input size for every compiler
    9. Compare the runtime of `b4_4_set_difference_cutoff_right_empty_par` for every input size for every compiler
    10. Compare the runtime of `b4_4_set_difference_cutoff_wholly_greater_par` for every input size for every compiler
    11. Compare the runtime of `b4_4_set_difference_cutoff_intersected_par` for every input size for every compiler

2. *Mbytes/sec*
    1. Compare the Mbytes/sec of `b4_1_merge_cutoff_wrapper_par` for every input size for every compiler
    2. Compare the Mbytes/sec of `b4_2_stable_sort_cutoff_already_sorted_par` for every input size for every compiler
    3. Compare the Mbytes/sec of `b4_2_stable_sort_cutoff_decrement_sorted_par` for every input size for every compiler
    4. Compare the Mbytes/sec of `b4_2_stable_sort_cutoff_not_sorted_par` for every input size for every compiler
    5. Compare the Mbytes/sec of `b4_3_set_union_cutoff_one_empty_par` for every input size for every compiler
    6. Compare the Mbytes/sec of `b4_3_set_union_cutoff_one_wholly_greater_par` for every input size for every compiler
    7. Compare the Mbytes/sec of `b4_3_set_union_cutoff_front_overhang_par` for every input size for every compiler
    8. Compare the Mbytes/sec of `b4_4_set_difference_cutoff_left_empty_par` for every input size for every compiler
    9. Compare the Mbytes/sec of `b4_4_set_difference_cutoff_right_empty_par` for every input size for every compiler
    10. Compare the Mbytes/sec of `b4_4_set_difference_cutoff_wholly_greater_par` for every input size for every
        compiler
    11. Compare the Mbytes/sec of `b4_4_set_difference_cutoff_intersected_par` for every input size for every compiler

3. *Strong Scaling*
    1. Compare the strong scaling `b4_1_merge_cutoff_wrapper_par` for input size 1M for every compiler
    2. Compare the strong scaling `b4_2_stable_sort_cutoff_already_sorted_par` for input size 1M for every compiler
    3. Compare the strong scaling `b4_2_stable_sort_cutoff_decrement_sorted_par` for input size 1M for every compiler
    4. Compare the strong scaling `b4_2_stable_sort_cutoff_not_sorted_par` for input size 1M for every compiler
    5. Compare the strong scaling `b4_3_set_union_cutoff_one_empty_par` for input size 1M for every compiler
    6. Compare the strong scaling `b4_3_set_union_cutoff_one_wholly_greater_par` for input size 1M for every compiler
    7. Compare the strong scaling `b4_3_set_union_cutoff_front_overhang_par` for input size 1M for every compiler
    8. Compare the strong scaling `b4_4_set_difference_cutoff_left_empty_par` for input size 1M for every compiler
    9. Compare the strong scaling `b4_4_set_difference_cutoff_right_empty_par` for input size 1M for every compiler
    10. Compare the strong scaling `b4_4_set_difference_cutoff_wholly_greater_par` for input size 1M for every compiler
    11. Compare the strong scaling `b4_4_set_difference_cutoff_intersected_par` for input size 1M for every compiler

**Metrics Involved:**

* Time
* Mbytes/sec
* Strong Scaling

**What benchmarks cover it:**

1. `b4_1_merge_cutoff_wrapper_par`: straight forward std::merge with two sorted vectors
2. `b4_2_stable_sort_cutoff_already_sorted_par`: std::stablesort with already sorted input
3. `b4_2_stable_sort_cutoff_decrement_sorted_par`: std::stablesort with decremenet sorted input
4. `b4_2_stable_sort_cutoff_not_sorted_par`: std::stablesort with random data
5. `b4_3_set_union_cutoff_one_empty_par`: std::set_union where one set is empty
6. `b4_3_set_union_cutoff_one_wholly_greater_par`: std::set_union where the elements of one set are all greater than the
   other sets
7. `b4_3_set_union_cutoff_front_overhang_par`: std::set_union where the overlap is right in the middle of the sets
8. `b4_4_set_difference_cutoff_left_empty_par`: std::set_difference with one set empty
9. `b4_4_set_difference_cutoff_right_empty_par`: std::set_difference with one set empty
10. `b4_4_set_difference_cutoff_wholly_greater_par`: std::set_difference where the elements of one set are all greater
    than the other sets
11. `b4_4_set_difference_cutoff_intersected_par`: std::set_difference where the sets overlap

**Compilers/Backends**

* GCC(TBB)
* NVC(OMP)
* NVC(GPU)

**GPU COMPATIBILITY:**

* Yes this will be GPU compatible. As a side product of testing this hypothesis we not only show how good GPUs perform
  better, but we can determine at what size does it make sense to switch over from CPU to GPU (aka finding the
  sweets-pot)

**Hypothesis is true when:**

* There is a significant bump in time or instructions per second.

**Performance Portability Calculation:**

* for this group we can "calculate" a performance probability by looking at the actual MBytes/sec vs the peak) (insipred
  by [2])

  |          | achieved | perfect | efficiency     | 
            |----------|---------|----------------|-------------|
  | GCC(TBB) | 100      | 1000    | 100/1000=0.10  |
  | NVC(OMP) | 500      | 1000    | 500/1000=0.50  |
  | NVC(GPU) | 1000     | 1500    | 1000/1500=0.66 |
  | Intel    | 800      | 1000    | 800/1000=0.80  |

  Performance Portability for `{GCC(TBB), NVC(OMP), NVC(GPU), Intel}` = `4/((1/0,1)+ (1/0,5) + (1/0,66) + (1/0,8))` =
  27%


* Later we can compare the performance portability calculated above from machine to machine (aka nebula vs tesla vs
  vsc)

## References

* [1] S. J. Pennycook, J. D. Sewall, and V. W. Lee. “A Metric for Performance Portability”. In: CoRR abs/1611.07409 (
  2016).
* [2] T. Deakin, J. Price, M. Martineau, and S. McIntosh-Smith. GPUSTREAM v2.0: Benchmarking the Achievable Memory
  Bandwidth of Many-Core Processors Across Diverse Parallel Programming Models. Lecture Notes in Computer Science.
  Springer, 5 2016. 1, 4, 5

## Template for Hypos

> HYPO

**Why important:**

*

**How to test it:**

1. *CAT A*
    1.

2. *CAT B*
    1.

**Metrics Involved:**

*

**What benchmarks cover it:**

1.

**Compilers/Backends**

*

**GPU COMPATIBILITY:**

*

**Hypothesis is true when:**

*

**Performance Portability Calculation:**

* 