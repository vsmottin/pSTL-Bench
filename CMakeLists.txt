cmake_minimum_required(VERSION 3.22)
project(master_benchmarks)

set(CMAKE_CXX_STANDARD 20)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

file(GLOB SOURCES
        src/*.h
        src/*.cpp
        )

add_executable(${PROJECT_NAME}
        ${SOURCES}
        src/main.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++20")
add_compile_definitions(BENCHMARK_PREFIX=${BENCHMARK_PREFIX})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_definitions(USE_TBB)
endif ()

SET(USE_PARALLEL_ALLOCATOR ON)

if (USE_PARALLEL_ALLOCATOR)
    message("Using parallel allocator")
    add_compile_definitions(USE_PARALLEL_ALLOCATOR)
else()
    message("Using no allocator")
endif ()

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

# region input size
if (NOT DEFINED ${MAX_INPUT_SIZE})
    set(MAX_INPUT_SIZE 67108864) # default is 2^26
endif ()

add_compile_definitions(MAX_INPUT_SIZE=${MAX_INPUT_SIZE})

# endregion

# enable google benchmark performance counters
set(BENCHMARK_ENABLE_LIBPFM ON)

# make sure google benchmark builds no mather
set(BENCHMARK_ENABLE_WERROR OFF)

add_subdirectory(ext/google-benchmark)

target_include_directories(${PROJECT_NAME}
        PUBLIC SYSTEM ext/google-benchmark/include
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC benchmark
        )

if (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${PROJECT_NAME}
            PUBLIC TBB::tbb # for gcc only
            )
    find_package(TBB REQUIRED) # for gcc only
endif ()

# we need cassert even in release builds to make sure certain vars are not optimised aways
string(REPLACE "-DNDEBUG" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native)
