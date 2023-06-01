cmake_minimum_required(VERSION 3.22)
project(master_benchmarks)

set(CMAKE_CXX_STANDARD 20)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

# register backends we supports right now
include(cmake/register_backend.cmake)

register_backend(GCC_TBB)
register_backend(NVC_OMP)
register_backend(NVC_CUDA)

# select the backend
set(BACKEND "GCC_TBB")


# load backend specific stuff
use_backend(${BACKEND})


# region set default build type to release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif ()
# endregion

file(GLOB SOURCES
        src/*.h
        src/*.cpp
        )

add_executable(${PROJECT_NAME}
        ${SOURCES}
        src/main.cpp)

# region benchmark prefix

set(BENCHMARK_PREFIX ${BACKEND})
add_compile_definitions(BENCHMARK_PREFIX=${BENCHMARK_PREFIX})

# endregion benchmark prefix

# region parallel allocator

option(USE_PARALLEL_ALLOCATOR "Use the parallel allocator to avoid first-touch bottlenecks" ON)
message("Setting of the USE_PARALLEL_ALLOCATOR FLAG: ${USE_PARALLEL_ALLOCATOR}")

if (USE_PARALLEL_ALLOCATOR)
    message("Using parallel allocator")
    add_compile_definitions(USE_PARALLEL_ALLOCATOR)
else ()
    message("Using no allocator")
endif ()

# endregion parallel allocator

# region skip boost option

message("Setting of the SKIP_BOOST FLAG: ${SKIP_BOOST}")

if (DEFINED SKIP_BOOST)
    message("Skipping boost option enabled")
    add_compile_definitions(SKIP_BOOST)
else ()
    message("Using boost in benchmarks")
    target_include_directories(${PROJECT_NAME}
            PRIVATE ext/boost_1_81
            )
endif ()

#endregion

# region only GPU benchmarks

#-DONLY_GPU=OFF
option(ONLY_GPU "Only enable GPU benchmarks" OFF)
message("Setting of the ONLY_GPU FLAG: ${ONLY_GPU}")

if (ONLY_GPU)
    message("Using ONLY_GPU")
    add_compile_definitions(ONLY_GPU)
endif ()

# endregion only GPU benchmarks

# region input size
if (NOT DEFINED ${MAX_INPUT_SIZE})
    set(MAX_INPUT_SIZE 67108864) # default is 2^26
endif ()

add_compile_definitions(MAX_INPUT_SIZE=${MAX_INPUT_SIZE})

# endregion

#region google benchmark stuff

# enable google benchmark performance counters
set(BENCHMARK_ENABLE_LIBPFM ON)

# make sure google benchmark builds no mather
set(BENCHMARK_ENABLE_WERROR OFF)

add_subdirectory(ext/google-benchmark)

target_include_directories(${PROJECT_NAME}
        PUBLIC SYSTEM ext/google-benchmark/include
        )
# endregion

target_link_libraries(${PROJECT_NAME} PRIVATE benchmark ${BACKEND_LINK_LIBRARIES})


# we need cassert even in release builds to make sure certain vars are not optimised aways
string(REPLACE "-DNDEBUG" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native)
