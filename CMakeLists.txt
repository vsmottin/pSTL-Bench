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


find_package(TBB REQUIRED) # for gcc only
add_subdirectory(ext/google-benchmark)

target_include_directories(${PROJECT_NAME}
        PRIVATE ext/google-benchmark/include
        )


target_link_libraries(${PROJECT_NAME}
        PRIVATE benchmark
        PUBLIC TBB::tbb # for gcc only
        )
