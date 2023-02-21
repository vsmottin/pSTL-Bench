# Potential Benchmark Groups

## Group 1 - Nested parallelism

In this group we try to understand how various parallel stl implementation behave when having nested parallelism.
Simply speaking we try to see how the performance changes when moving arround different complexity classes (e.g. n -> n*
log(n) -> n^2 -> ...)

During my research I got the feeling certain implementations have differnt kind of overheads. With this benchmarks we
want to get to the ground through about this.


> I prefer TBB for complex and nested parallelism over OpenMP.(OpenMP has a huge over-head for the nested
> parallelism) [[mentioned here]](https://stackoverflow.com/a/71812379/7835214)

### `b1_1_for_each_linear`

In this benchmark we simply have a linear benchmark. The body of the `for_each` is just here to simulate a computation.

### `b1_2_for_each_quadratic`

In this benchmark we have nested loops. The complexity of this benchmark O(n^2). It allows use to control the execution
policy from the outside meaning we
can test how different pairings compare in terms of performance.

### `b1_3_for_each_exponential`

This is a benchmark where we have O(2^n). It is similar to calculating the Fibonacci sequence.

## Group 2 - Data types

Different data type sizes have impact on the performance of
programs ([source](https://stackoverflow.com/questions/4763455/data-type-size-impact-on-performance)). The Reason
behind this is that the smaller the size the more entries fit into cache.

As far as I can see the size of data types is architecture and compiler
dependent (https://stackoverflow.com/a/2331846/7835214). The only thing mentioned in the c++ standard is that char has
to be 1 byte and the ranges other data types have to
support (https://www.open-std.org/JTC1/SC22/WG14/www/docs/n1256.pdf  https://stackoverflow.com/questions/589575/what-does-the-c-standard-state-the-size-of-int-long-type-to-be).

NVC++ data type sizes can be found
here: https://docs.nvidia.com/hpc-sdk/compilers/hpc-compilers-ref-guide/#data-types-c-cpp

Keep in mind unfortunately not all data types are supported in nvc++ (at least `long double` does not compile with
nvc++@22.5)

### `b2_1_basic_reduce`

This is a straight forward call of `std::reduce`. The reason why we use std::reduce is that its one of the simplest
parallel algorithms. This benchmark will be called will different data types:

* char
* int
* long
* unsigned long
* float
* double
* long double

## Group 3 - Cache / Instruction Misses

As we already saw in [Group 2](#group-2) cache misses decrease performance. In this group we want to take a close look
at the types of caches and how they affect parallel executions. Process pinning because even more important here.

Great picture to explain
pipelining: http://igoro.com/archive/fast-and-slow-if-statements-branch-prediction-in-modern-processors/
Good video for `False/True Sharing`: https://www.youtube.com/watch?v=O0HCGOzFLm0&ab_channel=CoffeeBeforeArch

### `b3_1_expensive_branching`

This benchmarks forces bad branch prediction. The goal of this benchmark is to see how good the parallel implementations
deal with bad branch predictions. Are they even effected by this or does the compiler optimize this automatically

### `b3_2_expensive_branching_annotated`

This is exactly the same benchmark as [`b3_2_expensive_branching`](#b31expensivebranching). The only difference here is
that we use c++20 constructs to annotate the code so the compiler can better align the instructons to avoid instruction
cache misses.

### `b3_3_expensive_sharing`

In this benchmark we use an atomic integer as an expensive sharing operation between multiple threads, cores, ... . The
idea is to see how strong the impact is when having such expensive sharings in parallel stl espeically when sitting on
different numa nodes, sockets, ...
Since we cannot really give hints to the scheduling I expect that depending on the placement of the threads this can
have performance implications

### `b3_4_no_expensive_sharing`

This benchmark acts as baseline for [`b3_3_expensive_sharing`](#b33expensivesharing)

### `b3_5_force_false_sharing`

Cache line invalidation can have huge impact on the performance. Especially when multiple processes wrtie to the same
cache line

### `b3_6_no_false_sharing`

THe counter par of 3.5

## Group 4 - Cutoffs

Some libstdc++ implementations have cutoffs. Meaning that until a certain size seq is used and only then we will use
parallelism. It seems that for some its not always a straight forward `n < CUTOFF` but a more complicated one. We want
to see how those cutoffs compare by compiler.

Identified CUTOFFS in libstdc++

SORTING

* Merge    https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/parallel_backend_tbb.h#L1251 (
  seems to be #define _PSTL_MERGE_CUT_OFF 2000)
* Stable
  sort    https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/parallel_backend_tbb.h#L1118 (
  seems to be #define _PSTL_STABLE_SORT_CUT_OFF 500)

SET OPERATION

* set_union    https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/algorithm_impl.h#L3046 (seems
  to be constexpr auto __set_algo_cut_off = 1000; )
* set_diff    https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/algorithm_impl.h#L3202 (seems
  to be constexpr auto __set_algo_cut_off = 1000; )
* set_inter    https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/algorithm_impl.h#L3105
* set_sym_diff    https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/algorithm_impl.h#L3299

(Good source for sorted stuff https://github.com/Morwenn/cpp-sort/wiki/Benchmarks)

## Group 5 - Parallel Computation Tricks

Interesting approaches to simple problems (it is actually linear solvable but maybe they found a nice parallelism trick)

* gcc implementation of std::find has comment that maybe there is room for
  improvements https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/parallel_impl.h#L29

* partition There are a lot of possible implementation to partition a vector as showed
  here https://www.cs.upc.edu/~lfrias/research/parpar/parpar.pdf.  (https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/algorithm_impl.h#L1879)

* unique_copy in gcc seems to use a fancy use of a strict
  scan https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/algorithm_impl.h#L1350

* std::minmax_element because there is no straight reference standard implementation. For example gcc (stdlibc++) uses
  under the hood (tbb) reduce.

> https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/algorithm_impl.h#L3497

## Group 6 - Inclusive_scan/exclusive

Because it's such an important alogirhtm that is building block for so many parallel
Algos. https://escholarship.org/content/qt6j57h5zw/qt6j57h5zw.pdf

## Group 7 - Special Algo vs custom implementation (e.g for_each)

* Copy_if logic with std::foreach and once with actual std::copy_if
* inclusive_scan vs ...
* transfer_reduce vs all_off
* tranform_reduce vs count_if with structs
* count sort implementation for_each vs parallel sort
* count_if vs for_each
* transform vs for_each


The goal is to see is there a difference between writing the operation and managing the values by yourself or not.
Seems there are differences
PS run it once without reserving and once with reserving



## Group 8 - Reduce and Transform_reduce Chunking

just call std::reduce with ints and transform_reduce large structs(512 bytes maybe). Because in reduce the chunking and
the scheduling is totally work of the library and not of the standard.

Can we draw conclusions from the benchmarks of the chunking etc?
> https://github.com/oneapi-src/oneTBB/blob/0cf592bd62fd4b9673b0f7ea9964c4ec9f80b994/include/oneapi/tbb/parallel_reduce.h#L562
> https://github.com/gcc-mirror/gcc/blob/master/libstdc%2B%2B-v3/include/pstl/parallel_backend_tbb.h#L116

> We can't control the chunking size etc because this comes from the
> stl. https://oneapi-src.github.io/oneTBB/main/tbb_userguide/Controlling_Chunking_os.html

## Group 9 - Lambda Clousure Performance

Does closure type of lambdas change performance when using parallel algos? Is there something we can improve?? The
standard allows us to do stuff as long as it does not change the intention.

https://stackoverflow.com/a/32898379/7835214
https://github.com/cplusplus/draft/blob/main/papers/n4431.pdf

## Group 10 - Effective use of SIMD

* What algos make use of simd efficiently? Reduce (with no params, with SAXPY logic), fill etc
* for inclusive_scan what we try to find out, at what size do they start using simd (only for c20 because unseq is
  c20) (https://en.algorithmica.org/hpc/algorithms/prefix/), par, etc.

## Group 11

There is a huge difference between using std::ranges::views::iota and actual container when passing to std::count_if. I
implemented B3_6 and B3_5 first with iota view and it did not use any parallel stuff. Also include this range class
everyone pretty much uses in their papers.

```c++
const auto &view = std::views::iota(0, static_cast<int>(input_data.size()));

    // we use the range because we do not want to move the input data array around.
    // this call should result in two threads not touching the same cache lines (scheduling should not make this worse)
    return std::count_if(policy, view.begin(), view.end(), [&](const auto &index) {
        return input_data[index].number + input_data[index].second_field >= 0;
    });
```

Then I changed to

```c++
return std::count_if(policy, input_data.begin(), input_data.end(), [&](const auto &index) {
        return index.number + index.second_field >= 0;
    });
```

And suddenly parallel concepts where used.