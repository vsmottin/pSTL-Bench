# master_benchmarks

## How to build

To build the benchmarks use the following commands in the command line.

### GCC

```bash
cmake -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_CXX_COMPILER=g++ -G Ninja -S . -B ./cmake-build-debug

cmake --build cmake-build-debug --target master_benchmarks -j 8
```

### NVHPC

```bash
cmake -DCMAKE_MAKE_PROGRAM=ninja -DCMAKE_CXX_COMPILER=g++ -G Ninja -DCMAKE_CXX_FLAGS=-stdpar=multicore -S . -B ./cmake-build-debug

cmake --build cmake-build-debug --target master_benchmarks -j 8
```

