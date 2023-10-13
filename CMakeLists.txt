cmake_minimum_required(VERSION 3.22)
project(pSTL-Bench)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# region options
option(ONLY_GPU "Only enable GPU benchmarks" OFF)
option(USE_BOOST "Use Boost's parallel implementation in benchmarks" OFF)
option(USE_GNU_PSTL "Use GNU's parallel implementation of STL in benchmarks" OFF)
option(USE_OMP "Use custom OpenMP parallel implementation in benchmarks" OFF)
option(USE_PARALLEL_ALLOCATOR "Use the parallel allocator to avoid first-touch bottlenecks" ON)

set(BACKEND GCC_TBB CACHE STRING "Select the backend to use")
set_property(CACHE BACKEND PROPERTY STRINGS GCC_TBB ICC_TBB GCC_OMP NVC_OMP NVC_CUDA)
# endregion options

# region register backends
include(cmake/register_backend.cmake)

register_backend(GCC_TBB)
register_backend(ICC_TBB)
register_backend(NVC_OMP)
register_backend(NVC_CUDA)

# load backend specific stuff
use_backend(${BACKEND})
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
else ()
    message(STATUS "Using no allocator")
endif ()
# endregion parallel allocator

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

# region use boost option
if (USE_BOOST)
    message(STATUS "Using boost in benchmarks")
    add_compile_definitions(USE_BOOST)

    CPMAddPackage(
            NAME Boost
            GITHUB_REPOSITORY "boostorg/boost"
            VERSION 1.74.0
            GIT_TAG "boost-1.74.0"
            OPTIONS
            "Boost_USE_STATIC_LIBS ON"
            "BOOST_USE_RELEASE_LIBS ON"
            "Boost_USE_MULTITHREADED ON"
            "Boost_USE_STATIC_RUNTIME OFF"
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)
endif ()
# endregion use boost option

# region use OpenMP option
if (USE_OMP)
    message(STATUS "Using OpenMP in benchmarks")
    add_compile_definitions(USE_OMP)
    find_package(OpenMP REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif ()
# endregion use OpenMP option

# region use GNU PSTL option
if (USE_GNU_PSTL)
    message(STATIUS "Using GNU PSTL in benchmarks")
    add_compile_definitions(USE_GNU_PSTL)
    find_package(OpenMP REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif ()

# region only GPU benchmarks
if (ONLY_GPU)
    message(STATUS "Using ONLY_GPU")
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
