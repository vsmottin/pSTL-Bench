cmake_minimum_required(VERSION 3.22)
project(master_benchmarks)

set(CMAKE_CXX_STANDARD 20)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

file(GLOB SOURCES
        src/*.h
        src/*.cpp
        )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++20")
add_compile_definitions(BENCHMARK_PREFIX=${BENCHMARK_PREFIX})

add_executable(${PROJECT_NAME}
        ${SOURCES}
        src/main.cpp)

add_subdirectory(ext/google-benchmark)

target_include_directories(${PROJECT_NAME}
        PRIVATE ext/google-benchmark/include
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE benchmark
        )

if (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${PROJECT_NAME}
            PUBLIC TBB::tbb # for gcc only
            )
    find_package(TBB REQUIRED) # for gcc only
endif ()


#target_compile_options(${PROJECT_NAME} PRIVATE -O3) # TODO: find way to integrate optimization
