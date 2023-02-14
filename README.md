# master_benchmarks

## How to build

To build the benchmarks use the following commands in the command line.

### GCC

```bash
cmake -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_CXX_COMPILER=g++ -G Ninja -S . -B ./cmake-build-debug

cmake --build cmake-build-debug --target master_benchmarks -j 8
```

### NVHPC

The Nvidia HPC compiler for C++ (nvc++) supports parallel STL with two backends. For multicore architectures we have
OpenMP and for GPUs CUDA.

#### Multicore using OMP Backend

```bash
cmake -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_CXX_COMPILER=nvc++ -G Ninja -DCMAKE_CXX_FLAGS=-stdpar=multicore -S . -B ./cmake-build-debug

cmake --build cmake-build-debug --target master_benchmarks -j 8
```

#### Multicore using CUDA Backend

```bash
cmake -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_CXX_COMPILER=nvc++ -G Ninja -DCMAKE_CXX_FLAGS=-stdpar -S . -B ./cmake-build-debug

cmake --build cmake-build-debug --target master_benchmarks -j 8
```

### FLAGS

The build systems with CMAKE provides a set of flags you can set to customize the build.

* `-DBENCHMARK_PREFIX` allows to set a prefix for every benchmark (e.g. `-DBENCHMARK_PREFIX=nvhpc_multicore` will result
  in `nvhpc_multicore_B1_NAME`)
