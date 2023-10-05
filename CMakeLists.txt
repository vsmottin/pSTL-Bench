cmake_minimum_required(VERSION 3.22)
project(pSTL-Bench)

set(CMAKE_CXX_STANDARD 20)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

option(ONLY_GPU "Only enable GPU benchmarks" OFF)

# register backends we supports right now
include(cmake/register_backend.cmake)

register_backend(GCC_TBB)
register_backend(NVC_OMP)
register_backend(NVC_CUDA)

# select the backend
if (NOT DEFINED BACKEND)
    # Select a default backend
    set(BACKEND GCC_TBB CACHE STRING "Select the backend to use")
    message(WARNING "No backend selected, using default: ${BACKEND}")
endif ()

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

# region Setup CPM (for dependencies)
set(CPM_USE_LOCAL_PACKAGES ON)
set(CPM_USE_NAMED_CACHE_DIRECTORIES ON)
set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_BINARY_DIR}/deps_cache/")
include(cmake/get_cpm.cmake)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
# endregion Setup CPM (for dependencies)

# region skip boost option
message("Setting of the SKIP_BOOST FLAG: ${SKIP_BOOST}")

if (DEFINED SKIP_BOOST)
    message("Skipping boost option enabled")
    add_compile_definitions(SKIP_BOOST)
else ()
    message("Using boost in benchmarks")
    CPMAddPackage(
            NAME Boost
            GITHUB_REPOSITORY "boostorg/boost"
            VERSION 1.81.0
            GIT_TAG "boost-1.81.0"
            OPTIONS
            "Boost_USE_STATIC_LIBS ON"
            "BOOST_USE_RELEASE_LIBS ON"
            "Boost_USE_MULTITHREADED ON"
            "Boost_USE_STATIC_RUNTIME OFF"
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::thread)
endif ()
# endregion skip boost option

# region only GPU benchmarks
# -DONLY_GPU=OFF
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
# endregion input size

# region google benchmark stuff
CPMAddPackage(
        NAME benchmark
        GITHUB_REPOSITORY google/benchmark
        VERSION 1.8.3
        OPTIONS
        "BENCHMARK_ENABLE_TESTING Off" # disable tests
        "BENCHMARK_ENABLE_LIBPFM ON" # enable performance counters
        "BENCHMARK_ENABLE_WERROR OFF" # make sure google benchmark builds no mather what
)

if (benchmark_ADDED)
    # enable the C++ standard to avoid errors
    set_target_properties(benchmark PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
    target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark)
else ()
    message(FATAL_ERROR "Failed to add google benchmark")
endif ()
# endregion google benchmark stuff

target_link_libraries(${PROJECT_NAME} PRIVATE ${BACKEND_LINK_LIBRARIES})

target_include_directories(${PROJECT_NAME}
        PRIVATE include/
)

# we need cassert even in release builds to make sure certain vars are not optimised away
string(REPLACE "-DNDEBUG" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

# append backend specific compile options
target_compile_options(${PROJECT_NAME} PRIVATE ${BACKEND_COMPILE_OPTIONS})

# append further optimization options
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native)
endif ()
