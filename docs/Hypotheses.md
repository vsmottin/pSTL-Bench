# Hypotheses

## H1

> Some parallel backends exhibit better performance and scalability when handling nested parallelism for homogeneous
> workloads

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

> The performance is significantly impacted by the order in which parallelism is applied, whether it is outer loop
> sequential and inner loop parallel, or outer loop parallel and inner loop sequential.

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

> Some parallel backends exhibit better performance and scalability when handling nested parallelism for heterogeneous
> workloads

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

* There is a significant bump in time (and mbytes per second).

**Performance Portability Calculation:**

* for this group we can "calculate" a performance probability by looking at the actual MBytes/sec vs the peak) (insipred
  by [2])

  |          | achieved | best     | efficiency    | 
  |----------|----------|---------------|----------------|
  | GCC(TBB) | 100      | 1000     | 100/1000=0.10 |
  | NVC(OMP) | 1000     | 1000     | 1000/1000=1   |
  | Intel    | 800      | 1000     | 800/1000=0.80 |

  Performance Portability for `{GCC(TBB), NVC(OMP), NVC(GPU), Intel}` = `3/((1/0,1) +  (1/1) + (1/0,8))` =
  27%


* Later we can compare the performance portability calculated above from machine to machine (aka nebula vs tesla vs
  vsc)

## H5

> Parallel stl backends use special parallelism techniques for linear algorithms, which have no clear reference
> implementation, leading to significant differences in terms of performance and their strong scaling properties.

**Why important:**

* Various linear algorithms in CPP have no clear reference implementation for parallel. Meaning as long as they follow
  the interface and return the correct results, they can do any special tricks to speed up or optimize the solution.
* Linear algorithms can be paralleled using chunking (if the original operation allows it) or other interesting tricks.

**How to test it:**

1. *Time*
    1. Compare the runtime of `b5_1_find_std::vector<int>_first_entry_par` for every input size for every compiler
    2. Compare the runtime of `b5_1_find_std::vector<int>_last_entry_par` for every input size for every compiler
    3. Compare the runtime of `b5_1_find_std::vector<int>_non_existing_entry_par` for every input size for every
       compiler
    4. Compare the runtime of `b5_2_partition_par` for every input size for every compiler
    5. Compare the runtime of `b5_3_unique_copy_default_par` for every input size for every compiler
    6. Compare the runtime of `b5_4_minmax_element_all_equal_par` for every input size for every compiler
    7. Compare the runtime of `b5_4_minmax_element_increasing_par` for every input size for every compiler

2. *Strong Scaling*
    1. Compare the strong scaling of `b5_1_find_std::vector<int>_first_entry_par` for fixed size 1M for every compiler
    2. Compare the strong scaling of `b5_1_find_std::vector<int>_last_entry_par` for fixed size 1M for every compiler
    3. Compare the strong scaling of `b5_1_find_std::vector<int>_non_existing_entry_par` for fixed size 1M size for
       every
       compiler
    4. Compare the strong scaling of `b5_2_partition_par` for fixed size 1M for every compiler
    5. Compare the strong scaling of `b5_3_unique_copy_default_par` for fixed size 1M for every compiler
    6. Compare the strong scaling of `b5_4_minmax_element_all_equal_par` for fixed size 1M for every compiler
    7. Compare the strong scaling of `b5_4_minmax_element_increasing_par` for fixed size 1M for every compiler

**Metrics Involved:**

* Time
* Strong Scaling

**What benchmarks cover it:**

1. `b5_1_find_std::vector<int>_first_entry_par`
2. `b5_1_find_std::vector<int>_last_entry_par`
3. `b5_1_find_std::vector<int>_non_existing_entry_par`
4. `b5_2_partition_par`
5. `b5_3_unique_copy_default_par`
6. `b5_4_minmax_element_all_equal_par`
7. `b5_4_minmax_element_increasing_par`

**Compilers/Backends**

* GCC(TBB)
* NVC(OMP)
* NVC(GPU)

**GPU COMPATIBILITY:**

* Yes this will be GPU compatible. As a side product of testing this hypothesis we not only show how good GPUs perform
  better, but we can determine at what size does it make sense to switch over from CPU to GPU (aka finding the
  sweets-pot)

**Hypothesis is true when:**

* When we see a significant difference in runtime from compiler to compiler.

**Performance Portability Calculation:**

* for this group we can "calculate" a performance probability by looking at the actual vs best time) (insipred
  by [2])

  |          | achieved | perfect | efficiency     | 
        |----------|---------|----------------|-------------|
  | GCC(TBB) | 100      | 1000    | 100/1000=0.10  |
  | NVC(OMP) | 500      | 1000    | 500/1000=0.50  |
  | Intel    | 800      | 1000    | 800/1000=0.80  |

  Performance Portability for `{GCC(TBB), NVC(OMP), NVC(GPU), Intel}` = `4/((1/0,1)+ (1/0,5) + (1/0,66) + (1/0,8))` =
  27%


* Later we can compare the performance portability calculated above from machine to machine (aka nebula vs tesla vs
  vsc)

## H6

> Parallel STL backends leverage specialized parallelism techniques for inclusive and exclusive scans, resulting in
> significant variations in performance and strong scaling properties.

**Why important:**

* Inclusive and Exclusive scans are building blocks for many parallel algorithms, hence it is important to analyse their
  characteristics.

**How to test it:**

1. *Time*
    1. Compare the runtime of `b6_1_inclusive_scan_par` for every input and for every compiler.
    2. Compare the runtime of `b6_2_exclusive_scan_par` for every input and for every compiler.

2. *Strong Scaling*
    1. Compare the strong scaling of `b6_1_inclusive_scan_par` for fixed input 1M for every compiler.
    2. Compare the strong scaling of `b6_2_exclusive_scan_par` for fixed input 1M for every compiler.

**Metrics Involved:**

* Time
* Strong Scaling

**What benchmarks cover it:**

1. `b6_1_inclusive_scan_par`: straight forward inclusive scan
2. `b6_2_exclusive_scan_par`: straight forward exclusive scan

**Compilers/Backends**

* GCC(TBB)
* NVC(OMP)
* NVC(GPU)

**GPU COMPATIBILITY:**

* Yes this will be GPU compatible. As a side product of testing this hypothesis we not only show how good GPUs perform
  better, but we can determine at what size does it make sense to switch over from CPU to GPU (aka finding the
  sweets-pot)

**Hypothesis is true when:**

* we can see a signifcant perofrmance differnce between various backends

**Performance Portability Calculation:**

* for this group we can "calculate" a performance probability by looking at the actual vs best time) (insipred
  by [2])

  |          | achieved | perfect | efficiency     | 
          |----------|---------|----------------|-------------|
  | GCC(TBB) | 100      | 1000    | 100/1000=0.10  |
  | NVC(OMP) | 500      | 1000    | 500/1000=0.50  |
  | Intel    | 800      | 1000    | 800/1000=0.80  |

  Performance Portability for `{GCC(TBB), NVC(OMP), NVC(GPU), Intel}` = `4/((1/0,1)+ (1/0,5) + (1/0,66) + (1/0,8))` =
  27%


* Later we can compare the performance portability calculated above from machine to machine (aka nebula vs tesla vs
  vsc)

## H7

> Employing specific parallel algorithms tends to yield superior performance/strong scaling compared to utilizing custom
> implementations that rely on various other parallel algorithm functions.

**Why important:**

* There exist parallel algorithms that can be reduced to others, implying that it is possible to achieve the same
  semantics by implementing the same logic using two different parallel algorithm functions.
* If the semantics are the same but one is superior, it makes sense to use the better one.

**How to test it:**

1. *TIME*
    1. Copy vs for_each
        1. Compare the runtime of `b7_1_copy_par` to `b7_1_custom_copy_with_foreach_par` for every input and for every
           compiler

    2. All_Of vs transform_reduce
        1. Compare the runtime of `b7_2_all_of_all_true_par` to `b7_2_custom_all_of_with_transform_reduce_all_true_par`
           for every input and for every compiler
        2. Compare the runtime of `b7_2_all_of_first_false_par`
           to `b7_2_custom_all_of_with_transform_reduce_first_false_par` for every input and for every compiler
        3. Compare the runtime of `b7_2_all_of_last_false_par`
           to `b7_2_custom_all_of_with_transform_reduce_last_false_par` for every input and for every compiler
        4. Compare the runtime of `b7_2_all_of_auto_false_par`
           to `b7_2_custom_all_of_with_transform_reduce_auto_false_par` for every input and for every compiler

    3. Count_if vs transform_reduce vs for_each
        1. Compare the runtime of `b7_3_count_if_all_hit_par`
           to `b7_3_custom_count_if_with_transform_reduce_all_hit_par`
           and `b7_3_custom_count_if_with_for_each_all_hit_par` for every input and for every compiler.
        2. Compare the runtime of `b7_3_count_if_half_hit_par`
           to `b7_3_custom_count_if_with_transform_reduce_half_hit_par`
           and `b7_3_custom_count_if_with_for_each_half_hit_par` for every input and for every compiler.
        3. Compare the runtime of `b7_3_count_if_orders_struct_par`
           to `b7_3_custom_count_if_with_transform_reduce_orders_struct_par`
           and `b7_3_custom_count_if_with_for_each_orders_struct_par` for every input and for every compiler.

    4. Stencil transform vs for_each
        1. Compare the runtime of `b7_4_stencil_transform_number_to_neightbours_stdev_par`
           to `b7_4_stencil_for_each_to_neightbours_stdev_par` for every input and for every compiler

    5. Scalar transform vs for_each
        1. Compare the runtime of `b7_5_scalar_transform_number_par` to `b7_5_scalar_for_each_par` for every input and
           for every compiler

    6. Serial transform and reduce vs transform_reduce
        1. Compare the runtime of `b7_6_serial_transform_reduce_par` to `b7_6_transform_reduce_par` for every input and
           for every compiler


2. *MBytes/sec*
    1. Copy vs for_each
        1. Compare the Mbytes/sec of `b7_1_copy_par` to `b7_1_custom_copy_with_foreach_par` for every input and for
           every compiler

    2. All_Of vs transform_reduce
        1. Compare the Mbytes/sec of `b7_2_all_of_all_true_par`
           to `b7_2_custom_all_of_with_transform_reduce_all_true_par` for every input and for every compiler
        2. Compare the Mbytes/sec of `b7_2_all_of_first_false_par`
           to `b7_2_custom_all_of_with_transform_reduce_first_false_par` for every input and for every compiler
        3. Compare the Mbytes/sec of `b7_2_all_of_last_false_par`
           to `b7_2_custom_all_of_with_transform_reduce_last_false_par` for every input and for every compiler
        4. Compare the Mbytes/sec of `b7_2_all_of_auto_false_par`
           to `b7_2_custom_all_of_with_transform_reduce_auto_false_par` for every input and for every compiler

    3. Count_if vs transform_reduce vs for_each
        1. Compare the Mbytes/sec of `b7_3_count_if_all_hit_par`
           to `b7_3_custom_count_if_with_transform_reduce_all_hit_par`
           and `b7_3_custom_count_if_with_for_each_all_hit_par` for every input and for every compiler.
        2. Compare the Mbytes/sec of `b7_3_count_if_half_hit_par`
           to `b7_3_custom_count_if_with_transform_reduce_half_hit_par`
           and `b7_3_custom_count_if_with_for_each_half_hit_par` for every input and for every compiler.
        3. Compare the Mbytes/sec of `b7_3_count_if_orders_struct_par`
           to `b7_3_custom_count_if_with_transform_reduce_orders_struct_par`
           and `b7_3_custom_count_if_with_for_each_orders_struct_par` for every input and for every compiler.

    4. Stencil transform vs for_each
        1. Compare the Mbytes/sec of `b7_4_stencil_transform_number_to_neightbours_stdev_par`
           to `b7_4_stencil_for_each_to_neightbours_stdev_par` for every input and for every compiler

    5. Scalar transform vs for_each
        1. Compare the Mbytes/sec of `b7_5_scalar_transform_number_par` to `b7_5_scalar_for_each_par` for every input
           and for every compiler

    6. Serial transform and reduce vs transform_reduce
        1. Compare the Mbytes/sec of `b7_6_serial_transform_reduce_par` to `b7_6_transform_reduce_par` for every input
           and for every compiler


3. *Strong Scaling*
    1. Copy vs for_each
        1. Compare the strong scaling of `b7_1_copy_par` to `b7_1_custom_copy_with_foreach_par` for fixed input 1M and
           for every compiler

    2. All_Of vs transform_reduce
        1. Compare the strong scaling of `b7_2_all_of_all_true_par`
           to `b7_2_custom_all_of_with_transform_reduce_all_true_par` for fixed input 1M and for every compiler
        2. Compare the strong scaling of `b7_2_all_of_first_false_par`
           to `b7_2_custom_all_of_with_transform_reduce_first_false_par` for fixed input 1M and for every compiler
        3. Compare the strong scaling of `b7_2_all_of_last_false_par`
           to `b7_2_custom_all_of_with_transform_reduce_last_false_par` for fixed input 1M and for every compiler
        4. Compare the strong scaling of `b7_2_all_of_auto_false_par`
           to `b7_2_custom_all_of_with_transform_reduce_auto_false_par` for fixed input 1M and for every compiler

    3. Count_if vs transform_reduce vs for_each
        1. Compare the strong scaling of `b7_3_count_if_all_hit_par`
           to `b7_3_custom_count_if_with_transform_reduce_all_hit_par`
           and `b7_3_custom_count_if_with_for_each_all_hit_par` for fixed input 1M and for every compiler.
        2. Compare the strong scaling of `b7_3_count_if_half_hit_par`
           to `b7_3_custom_count_if_with_transform_reduce_half_hit_par`
           and `b7_3_custom_count_if_with_for_each_half_hit_par` for fixed input 1M and for every compiler.
        3. Compare the strong scaling of `b7_3_count_if_orders_struct_par`
           to `b7_3_custom_count_if_with_transform_reduce_orders_struct_par`
           and `b7_3_custom_count_if_with_for_each_orders_struct_par` for fixed input 1M and for every compiler.

    4. Stencil transform vs for_each
        1. Compare the strong scaling of `b7_4_stencil_transform_number_to_neightbours_stdev_par`
           to `b7_4_stencil_for_each_to_neightbours_stdev_par` for fixed input 1M and for every compiler

    5. Scalar transform vs for_each
        1. Compare the strong scaling of `b7_5_scalar_transform_number_par` to `b7_5_scalar_for_each_par` for fixed
           input 1M and for every compiler

    6. Serial transform and reduce vs transform_reduce
        1. Compare the strong scaling of `b7_6_serial_transform_reduce_par` to `b7_6_transform_reduce_par` for fixed
           input 1M and for every compiler

**Metrics Involved:**

* Time
* MBytes/sec
* Strong Scaling

**What benchmarks cover it:**

1. `b7_1_copy_par`: copies values from one vector to another vector with std::copy
2. `b7_1_custom_copy_with_foreach_par`: copies values from one vector to another vector with std::for_each
3. `b7_2_all_of_all_true_par`:  std::all_of where the predicate is true for every element
4. `b7_2_custom_all_of_with_transform_reduce_all_true_par`: transform_reduce simulating std::all_of where the predicate
   is true for every element
5. `b7_2_all_of_first_false_par`:  std::all_of where the predicate is false for the first element
6. `b7_2_custom_all_of_with_transform_reduce_first_false_par`: transform_reduce simulating std::all_of where the
   predicate is false for the first element
7. `b7_2_all_of_last_false_par`:   std::all_of where the predicate is false for the last element
8. `b7_2_custom_all_of_with_transform_reduce_last_false_par`:  transform_reduce simulating std::all_of where the
   predicate is false for the last element
9. `b7_2_all_of_auto_false_par`:    std::all_of where the predicate is false for every element
10. `b7_2_custom_all_of_with_transform_reduce_auto_false_par`:   transform_reduce simulating std::all_of where the
    predicate is false for every element
11. `b7_3_count_if_all_hit_par`: std::count_if where the predicate is true for all
12. `b7_3_custom_count_if_with_transform_reduce_all_hit_par`: transform_reduce logic simulating std::count_if where the
    predicate is true for all
13. `b7_3_custom_count_if_with_for_each_all_hit_par`: for_each logic simulating std::count_if where the predicate is
    true for all
14. `b7_3_count_if_half_hit_par`: std::count_if where for only half of the entries the predicate is true
15. `b7_3_custom_count_if_with_transform_reduce_half_hit_par`: transform_reduce logic simulating std::count_if where for
    only half of the entries the predicate is true
16. `b7_3_custom_count_if_with_for_each_half_hit_par`: for_each logic simulating std::count_if where for only half of
    the entries the predicate is true
17. `b7_3_count_if_orders_struct_par`: std::count_if where only a subset of the structs inside the vector eval to true
    for the predicate
18. `b7_3_custom_count_if_with_transform_reduce_orders_struct_par`: transform_reduce logic simulating std::count_if
    where only a subset of the structs inside the vector eval to true for the predicate
19. `b7_3_custom_count_if_with_for_each_orders_struct_par`: for_each logic simulating std::count_if where only a subset
    of the structs inside the vector eval to true for the predicate
20. `b7_4_stencil_transform_number_to_neightbours_stdev_par`: stencil std::transform operation calculating the stddev of
    3 neighbouring cells.
21. `b7_4_stencil_for_each_to_neightbours_stdev_par`: stencil std::for_each operation calculating the stddev of 3
    neighbouring cells.
22. `b7_5_scalar_transform_number_par`: std::transform with a scalar operation
23. `b7_5_scalar_for_each_par`: std::for_each with a scalar operation
24. `b7_6_serial_transform_reduce_par`: first creating a std::transform followed by a std::reduce
25. `b7_6_transform_reduce_par`: single call to std::transform_reduce

**Compilers/Backends**

* GCC(TBB)
* NVC(OMP)

**GPU COMPATIBILITY:**

* Sadly not all of them work with GPU but I will present in my paper alternative how they could made runable.

**Hypothesis is true when:**

* There is a difference from specific algo to custom implemetation

**Performance Portability Calculation:**

* for this group we can "calculate" a performance probability by looking at the actual vs best time) (insipred
  by [2])

  |          | achieved | perfect | efficiency     | 
          |----------|---------|----------------|-------------|
  | GCC(TBB) | 100      | 1000    | 100/1000=0.10  |
  | NVC(OMP) | 500      | 1000    | 500/1000=0.50  |
  | Intel    | 800      | 1000    | 800/1000=0.80  |

  Performance Portability for `{GCC(TBB), NVC(OMP), NVC(GPU), Intel}` = `4/((1/0,1)+ (1/0,5) + (1/0,66) + (1/0,8))` =
  27%


* Later we can compare the performance portability calculated above from machine to machine (aka nebula vs tesla vs
  vsc)

## H8

> Parallel STL does not inherently provide support for index-based iterations, thereby requiring the developer to devise
> a custom sequence for indices. The manner in which the index values are generated by the developer can significantly
> impact the application's performance and scalability.

**Why important:**

* It can be a non-obvious bottleneck

**How to test it:**

1. *Time*
    1. Compare the runtime of `b9_1_transform_baseline_par` for every input size and every compiler.
    2. Compare the runtime of `b9_2_transform_old_iota_par` for every input size and every compiler.
    3. Compare the runtime of `b9_3_transform_views_iota_par` for every input size and every compiler.
    4. Compare the runtime of `b9_5_transform_custom_iterator_par` for every input size and every compiler.
    5. Compare the runtime of `b9_6_transform_boost_par` for every input size and every compiler.

2. *Strong Scaling*
    1. Compare the strong scaling of `b9_1_transform_baseline_par` for fixed input size 1M and every compiler.
    2. Compare the strong scaling of `b9_2_transform_old_iota_par` for fixed input size 1M and every compiler.
    3. Compare the strong scaling of `b9_3_transform_views_iota_par` for fixed input size 1M and every compiler.
    4. Compare the strong scaling of `b9_5_transform_custom_iterator_par` for fixed input size 1M and every compiler.
    5. Compare the strong scaling of `b9_6_transform_boost_par` for fixed input size 1M and every compiler.

**Metrics Involved:**

* Time
* Strong Scaling

**What benchmarks cover it:**

1. `b9_1_transform_baseline_par`: baseline transform using data driven (aka without indices)
2. `b9_2_transform_old_iota_par`: transform using std::iota generated indices
3. `b9_3_transform_views_iota_par`: using std::views::iota generated indices
4. `b9_5_transform_custom_iterator_par`: using a custom iterator that is used in a lot of papers
5. `b9_6_transform_boost_par`: using a famous boost implementation

**Compilers/Backends**

* GCC(TBB)
* NVC(OMP)

**GPU COMPATIBILITY:**

* Sadly not

**Hypothesis is true when:**

* there is a difference in the metrics from compiler to compiler

**Performance Portability Calculation:**

* for this group we can "calculate" a performance probability by looking at the strong scaling speedup every compiler
  has when using
  the max amount of cores. (aka running with 1M entries at max core) (insipred by [1])

  |          | achieved | perfect | efficiency  | 
      |----------|----------|---------|-------------|
  | GCC(TBB) | 12       | 16      | 12/16=0.75  |
  | NVC(OMP) | 16       | 16      | 16/16=1     |
  | Intel    | 14       | 16      | 14/16=0.875 |

  Performance Portability for `{GCC(TBB), NVC(OMP), NVC(GPU), Intel}` = 0

  Performance Portability for `{GCC(TBB), NVC(OMP), Intel}` = `3/((1/0,75)+ (1/1) + (1/0,875))` = 86.3%

* Later we can compare the performance portability calculated above from machine to machine (aka nebula vs tesla vs
  vsc)

## H9

> The performance implications of utilizing scatter mapping as opposed to compact mapping can vary depending on the
> compiler and backend being used.

**Why important:**

* Accessing memory from remote locations can have a significant impact on performance.

**How to test it:**

1. *Time*
    1. Copy
        1. Compare the runtime of `b7_1_copy_par` and `b7_1_custom_copy_with_foreach_par` with on same numa node for
           fixed size 1M on every compiler
        2. Compare the runtime of `b7_1_copy_par` and `b7_1_custom_copy_with_foreach_par` with on different numa node
           for fixed size 1M on every compiler
    2. Inclusive / Exclusive Scan
        1. Compare the runtime of `b6_1_inclusive_scan_par` with on same numa node for fixed size 1M on every compiler
        2. Compare the runtime of `b6_1_inclusive_scan_par` with on different numa node for fixed size 1M on every
           compiler
        3. Compare the runtime of `b6_2_exclusive_scan_par` with on same numa node for fixed size 1M on every compiler
        4. Compare the runtime of `b6_2_exclusive_scan_par` with on different numa node for fixed size 1M on every
           compiler
    3. Transform
        1. Compare the runtime of `b7_5_scalar_transform_number_par` and `b7_5_scalar_for_each_par` with on same numa
           node for fixed size 1M on every compiler
        2. Compare the runtime of `b7_5_scalar_transform_number_par` and `b7_5_scalar_for_each_par` with on different
           numa node for fixed size 1M on every compiler


2. *MBytes/sec*
    1. Copy
        1. Compare the MBytes/sec of `b7_1_copy_par` and `b7_1_custom_copy_with_foreach_par` with on same numa node for
           fixed size 1M on every compiler
        2. Compare the MBytes/sec of `b7_1_copy_par` and `b7_1_custom_copy_with_foreach_par` with on different numa node
           for fixed size 1M on every compiler
    2. Inclusive / Exclusive Scan
        1. Compare the MBytes/sec of `b6_1_inclusive_scan_par` with on same numa node for fixed size 1M on every
           compiler
        2. Compare the MBytes/sec of `b6_1_inclusive_scan_par` with on different numa node for fixed size 1M on every
           compiler
        3. Compare the MBytes/sec of `b6_2_exclusive_scan_par` with on same numa node for fixed size 1M on every
           compiler
        4. Compare the MBytes/sec of `b6_2_exclusive_scan_par` with on different numa node for fixed size 1M on every
           compiler
    3. Transform
        1. Compare the MBytes/sec of `b7_5_scalar_transform_number_par` and `b7_5_scalar_for_each_par` with on same numa
           node for fixed size 1M on every compiler
        2. Compare the MBytes/sec of `b7_5_scalar_transform_number_par` and `b7_5_scalar_for_each_par` with on different
           numa node for fixed size 1M on every compiler

**Metrics Involved:**

* Time
* MBytes/sec

**What benchmarks cover it:**

1. `b7_1_copy_par`: copies values from one vector to another vector with std::copy
2. `b7_1_custom_copy_with_foreach_par`: copies values from one vector to another vector with std::for_each
3. `b6_1_inclusive_scan_par`: straight forward inclusive scan
4. `b6_2_exclusive_scan_par`: straight forward inclusive scan
5. `b7_5_scalar_transform_number_par`: std::transform with a scalar operation
6. `b7_5_scalar_for_each_par`: std::for_each with a scalar operation

**Compilers/Backends**

* GCC(TBB)
* NVC(OMP)

**GPU COMPATIBILITY:**

* Here we will not consider it

**Hypothesis is true when:**

* there are significant differences

**Performance Portability Calculation:**

* for this group we can "calculate" a performance probability by looking at the actual MBytes/sec vs best) (insipred
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
