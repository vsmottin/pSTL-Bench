# pSTL-Bench

pSTL-Bench is a comprehensive benchmark suite designed to assist developers in evaluating the most suitable parallel
STL (Standard Template Library) backend for their needs. This tool allows developers to benchmark a wide variety of
parallel primitives and offers the flexibility to choose the desired backend for execution during compile time.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

## Introduction

pSTL-Bench is an invaluable resource for developers seeking to assess the performance and suitability of different
parallel STL backends. By providing a rich benchmark suite, it facilitates the evaluation of parallel primitives across
various implementations, aiding in the selection of the optimal backend for specific requirements.

## Features

- Comprehensive benchmark suite for parallel STL backends
- Benchmarks a wide variety of parallel primitives
- Flexibility to choose the desired backend at compile time
- Facilitates performance comparison and evaluation of different implementations

## Installation

To install pSTL-Bench, follow these steps:

1. Clone the repository:

```shell
git clone https://github.com/diegokrupitza/pSTL-Bench.git
```

2. Build the project with the desired parallel STL Backend

```shell
cmake -DBACKEND=GCC_TBB -DCMAKE_CXX_COMPILER=g++ -S . -B ./cmake-build-gcc
cmake --build cmake-build-gcc/ --target pSTL-Bench
```

It is important that one defines what backend to be used and what compiler. You can define the backend
with `-DBACKEND=...` and the compiler with `-DCMAKE_CXX_COMPILER=...`. In the example above we will use g++ with GCC
TBB. A list of supported backends can be seen in `./cmake/`

_Note_: we advise to use `ninja` in order to speedup the compile time (aka add the flag `-G Ninja`)

## USAGE

After building the binary for a desired backend compiler pairing, you can simply call it. Since we are
using [Google benchmark](https://github.com/google/benchmark) under the hood, you can use all the possible command line
parameters (e.g. `--benchmark_filter=...`).

```shell
./cmake-build-gcc/master_benchmarks --benchmark_filter="b7_1"
```

## pSTL-paper

To reproduce the results of the pSTL-paper:

1. Compile for the combinations: `GCC_TBB`, `GCC_GNU`, `ICC_TBB`, `NVC_OMP`. 

```shell
cmake -DCMAKE_BUILD_TYPE=Release -DBACKEND=GCC_TBB ./cmake-build-gcc-tbb
cmake -DCMAKE_BUILD_TYPE=Release -DBACKEND=GCC_TBB -DUSE_GNU_PSTL=ON ./cmake-build-gcc-gnu
cmake -DCMAKE_BUILD_TYPE=Release -DBACKEND=NVC_OMP -DCMAKE_CXX_COMPILER=nvc++ ./cmake-build-nvc-omp
cmake -DCMAKE_BUILD_TYPE=Release -DBACKEND=ICC_TBB -DCMAKE_CXX_COMPILER=icpx -DCMAKE_CXX_FLAGS=-static-libstdc++ ./cmake-build-icc-tbb
```

2. Run benchmarks: `count_if`, `find`, `for_each`, `reduce`, `sort`
   * Recommended to use: `find_random`, `for_each_linear_par`, `sort_random`
   * There are also other benchmarks like `find_first`, `find_last`, `for_each_linear_mandelbrot`, ... 

```shell
./pSTL-Bench --benchmark_filter=count_if
./pSTL-Bench --benchmark_filter=find
./pSTL-Bench --benchmark_filter=for_each
./pSTL-Bench --benchmark_filter=reduce
./pSTL-Bench --benchmark_filter=sort
```

3. To export CSV files and aggregations, append the following options: `--benchmark_out_format=csv --benchmark_repetitions=10 --benchmark_min_time=1s`

```shell
./pSTL-Bench --benchmark_filter=count_if --benchmark_out_format=csv --benchmark_repetitions=10 --benchmark_min_time=1s
...
```

## Dependencies

Some parallel STL backends have dependencies. For example GCC_TBB requires oneTBB to be installed. In case you did not
install it you can see here how to get
it https://www.intel.com/content/www/us/en/docs/onetbb/get-started-guide/2021-6/install-onetbb-on-linux-os.html 
