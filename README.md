# pSTL-Bench

pSTL-Bench is a comprehensive benchmark suite designed to assist developers in evaluating the most suitable parallel
STL (Standard Template Library) backend for their needs.
This tool allows developers to benchmark a wide variety of parallel primitives and offers the flexibility to choose the
desired backend for execution during compile time.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

## Introduction

pSTL-Bench is a resource for developers seeking to assess the performance and suitability of different
parallel STL backends.
By providing a rich benchmark suite, it facilitates the evaluation of parallel primitives across various
implementations, aiding in the selection of the optimal backend for specific requirements.

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
cmake -DBACKEND=TBB -DCMAKE_CXX_COMPILER=g++ -S . -B ./cmake-build-gcc
cmake --build cmake-build-gcc/ --target pSTL-Bench
```

It is important that one defines which backend to be used and which compiler.
You can define the backend with `-DBACKEND=...` and the compiler with `-DCMAKE_CXX_COMPILER=...`.
In the example above we will use g++ with TBB.
A list of supported backends can be seen in `./cmake/`.

_Note_: we advise to use `ninja` in order to speed up the compile time (aka add the flag `-G Ninja`)

## USAGE

After building the binary for a desired backend compiler pairing, you can simply call it.
Since we are using [Google benchmark](https://github.com/google/benchmark) under the hood, you can use all the possible
command line parameters (e.g. `--benchmark_filter=...`).

```shell
./build/pSTL-Bench --benchmark_filter="std::sort"
```

## pSTL-paper

To reproduce the results of the pSTL-paper:

1. Compile for the combinations: `TBB`, `GNU`, `HPX`, `NVHPC_OMP`, `NVHPC_CUDA` (experimental).

```shell
cmake -DCMAKE_BUILD_TYPE=Release -DBACKEND=TBB -DCMAKE_CXX_COMPILER=g++ ./cmake-build-gcc-tbb
cmake -DCMAKE_BUILD_TYPE=Release -DBACKEND=GNU -DCMAKE_CXX_COMPILER=g++ ./cmake-build-gcc-gnu
cmake -DCMAKE_BUILD_TYPE=Release -DBACKEND=HPX -DCMAKE_CXX_COMPILER=g++ ./cmake-build-gcc-hpx
cmake -DCMAKE_BUILD_TYPE=Release -DBACKEND=TBB -DCMAKE_CXX_COMPILER=icpx ./cmake-build-icc-tbb
cmake -DCMAKE_BUILD_TYPE=Release -DBACKEND=NVHPC_OMP -DCMAKE_CXX_COMPILER=nvc++ ./cmake-build-icc-tbb
```

_Note_: You can use an allocator designed for NUMA systems with the flag `-DUSE_PARALLEL_ALLOCATOR=ON`.

2. Run benchmarks: `find`, `for_each`, `inclusive_scan`, `reduce`, `sort`
    * There are also other benchmarks like `any_of`, `generate`, `min_element`, ...

```shell
./pSTL-Bench --benchmark_filter=find
./pSTL-Bench --benchmark_filter=for_each
./pSTL-Bench --benchmark_filter=inclusive_scan
./pSTL-Bench --benchmark_filter=reduce
./pSTL-Bench --benchmark_filter=sort
```

3. To export CSV files and aggregations, append the following
   options: `--benchmark_out_format=csv --benchmark_repetitions=10 --benchmark_min_time=1s`

```shell
./pSTL-Bench --benchmark_filter=reduce --benchmark_out_format=csv --benchmark_repetitions=10 --benchmark_min_time=1s
...
```

## Dependencies

Some parallel STL backends have dependencies:

- TBB can be found on their [GitHub](https://github.com/oneapi-src/oneTBB) or
their [website](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb.html).
- HPX can be found on their [GitHub](https://github.com/STEllAR-GROUP/hpx) or
their [website](https://hpx.stellar-group.org/). 