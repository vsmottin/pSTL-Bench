cmake_minimum_required(VERSION 3.22)
project(pSTL-Bench)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# region options
option(USE_PARALLEL_ALLOCATOR "Use the parallel allocator to avoid first-touch bottlenecks" OFF)

set(BACKEND CACHE STRING "Select the backend to use for std:: algorithms")
set_property(CACHE BACKEND PROPERTY STRINGS TBB GNU HPX NVHPC_OMP NVHPC_CUDA)
set(DATA_TYPE CACHE STRING "Select the data type to use for the benchmarks")
set_property(CACHE DATA_TYPE PROPERTY STRINGS int float double)

message(STATUS "Using ${BACKEND} backend...")
message(STATUS "Using ${DATA_TYPE} data type...")

# add compile definition if PSTL_ELEM_T is not empty
if (NOT DATA_TYPE STREQUAL "")
    add_compile_definitions(PSTL_ELEM_T=${DATA_TYPE})
endif ()
# endregion options

# region Setup CPM (for dependencies)
set(CPM_USE_LOCAL_PACKAGES ON)
set(CPM_USE_NAMED_CACHE_DIRECTORIES ON)

# check if the cache is not defined (also as an environment variable)
if (NOT DEFINED ENV{CPM_SOURCE_CACHE} AND NOT DEFINED CPM_SOURCE_CACHE)
    set(CPM_SOURCE_CACHE "${CMAKE_BINARY_DIR}/deps_cache/" CACHE PATH "CPM source cache" FORCE)
    message(STATUS "CPM_SOURCE_CACHE not defined, using ${CPM_SOURCE_CACHE}")
else ()
    if (DEFINED ENV{CPM_SOURCE_CACHE})
        message(STATUS "CPM_SOURCE_CACHE (env) defined, using $ENV{CPM_SOURCE_CACHE}")
    else ()
        message(STATUS "CPM_SOURCE_CACHE defined, using ${CPM_SOURCE_CACHE}")
    endif ()
endif ()

include(cmake/get_cpm.cmake)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CPM_SOURCE_CACHE};${CMAKE_MODULE_PATH}")
# endregion Setup CPM (for dependencies)

# region register backends
include(cmake/register_backend.cmake)

register_backend(TBB)
register_backend(HPX)
register_backend(GNU)
register_backend(NVHPC_CUDA)
register_backend(NVHPC_OMP)

# Define the BENCHMARK_COMPILER macro to ${CMAKE_CXX_COMPILER_ID}
add_compile_definitions(BENCHMARK_COMPILER="${CMAKE_CXX_COMPILER_ID}")

# load backend specific stuff
if (NOT BACKEND STREQUAL "")
    use_backend(${BACKEND})
endif ()
# endregion register backends

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
if (USE_PARALLEL_ALLOCATOR)
    message(STATUS "Using parallel allocator")
    add_compile_definitions(USE_PARALLEL_ALLOCATOR)
    find_package(TBB REQUIRED)
    list(APPEND LINK_LIBRARIES TBB::tbb)
else ()
    message(STATUS "Using no allocator")
endif ()
# endregion parallel allocator

# region input size
if (NOT DEFINED ${MIN_INPUT_SIZE})
    set(MIN_INPUT_SIZE 8)
endif ()

if (NOT DEFINED ${MAX_INPUT_SIZE})
    set(MAX_INPUT_SIZE 1073741824) # default is 2^30 elements -> 2^30 * 4 bytes = 4 GB of data
    #    set(MAX_INPUT_SIZE 2147483648) # default is 2^31 elements -> 2^31 * 4 bytes = 8 GB of data
endif ()

add_compile_definitions(MIN_INPUT_SIZE=${MIN_INPUT_SIZE})
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
    list(APPEND LINK_LIBRARIES benchmark::benchmark)
elseif (TARGET benchmark::benchmark)
    list(APPEND LINK_LIBRARIES benchmark::benchmark)
else ()
    message(FATAL_ERROR "Failed to add google benchmark")
endif ()
# endregion google benchmark stuff

# link libraries
foreach (LIB ${LINK_LIBRARIES})
    message(STATUS "Linking ${LIB}...")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB})
endforeach ()

target_include_directories(${PROJECT_NAME} PRIVATE include/)

# we need cassert even in release builds to make sure certain vars are not optimised away
string(REPLACE "-DNDEBUG" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

# append backend specific compile options
target_compile_options(${PROJECT_NAME} PRIVATE ${BACKEND_COMPILE_OPTIONS})

# append further optimization options
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native)
endif ()
