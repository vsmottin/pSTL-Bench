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

## Getting Started

To run pSTL-Bench, follow these steps:

1. Clone the repository:

```shell
git clone https://github.com/diegokrupitza/pSTL-Bench.git
```

2. Build the project with the desired parallel STL Backend

```shell
cmake -DBACKEND=TBB -DCMAKE_CXX_COMPILER=g++ -S . -B ./cmake-build-gcc
cmake --build cmake-build-gcc/ --target pSTL-Bench
```

One must define which backend to be used and which compiler.
You can define the backend with `-DBACKEND=...` and the compiler with `-DCMAKE_CXX_COMPILER=...`.
In the example above we will use g++ with TBB.
A list of supported backends can be seen in `./cmake/`.

Other options are:

* `-DDATA_TYPE=...` to define the data type (`int`, `float`, `double`...).
* `-DMIN_INPUT_SIZE=...` and `-DMAX_INPUT_SIZE=...` to define the range of input sizes.
* `-DUSE_PARALLEL_ALLOCATOR=ON|OFF` to use a parallel allocator designed for NUMA systems.
* `-DUSE_LIKWID=ON|OFF` and `-DUSE_PAPI=ON|OFF` to use performance counters
  with [LIKWID](https://github.com/RRZE-HPC/likwid) or [PAPI](https://github.com/icl-utk-edu/papi).
* `-DGPU_CONTINUOUS_TRANSFERS=ON|OFF` to enable continuous transfers between the CPU and GPU so will be transferred
  between host and device before and after each kernel. When OFF, data will be transferred only once before the first
  call.

_Note_: we recommend to use `ccmake` to see all the possible flags and options.

## USAGE

After building the binary for a desired backend compiler pairing, you can simply call it.
Since we are using [Google benchmark](https://github.com/google/benchmark) under the hood, you can use all the possible
command line parameters.
For example:

```shell
./build/pSTL-Bench --benchmark_filter="std::sort"
```

The full set of options can be printed with `./pSTL-Bench --help`.

To get the full list of benchmarks, you can use the `--benchmark_list_tests` flag.

By default, `pSTL-Bench` will capture the `OMP_NUM_THREADS` environment variable to set the number of threads.
However, for [HPX](https://github.com/STEllAR-GROUP/hpx) argument `--hpx:threads` must be used.

Other environment variables that can be used are:

* `PSTL_ABS_TOL` and `PSTL_REL_TOL` to define the absolute and relative tolerance when asserting the results of floating
  point operations.

## Citation

If you use pSTL-Bench in your research, please cite the following papers:

```bibtex
@misc{laso2024pstlbench,
      title={{pSTL-Bench}: A Micro-Benchmark Suite for Assessing Scalability of {C++} Parallel {STL} Implementations},
      author={Ruben Laso and Diego Krupitza and Sascha Hunold},
      year={2024},
      eprint={2402.06384},
      archivePrefix={arXiv},
      primaryClass={cs.DC}
}
```

## Dependencies

Some parallel STL backends have dependencies:

- TBB can be found on their [GitHub](https://github.com/oneapi-src/oneTBB) or
  their [website](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb.html).
- HPX can be found on their [GitHub](https://github.com/STEllAR-GROUP/hpx) or
  their [website](https://hpx.stellar-group.org/).