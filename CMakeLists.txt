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


add_subdirectory(ext/google-benchmark)

target_include_directories(${PROJECT_NAME}
        PRIVATE ext/google-benchmark/include
        )


target_link_libraries(${PROJECT_NAME}
        PRIVATE benchmark
        PUBLIC TBB::tbb # for gcc only [TODO: find better way to do this]
        )
find_package(TBB REQUIRED) # for gcc only [TODO: find better way to do this]

#target_compile_options(${PROJECT_NAME} PRIVATE -O3) # TODO: find way to integrate optimization
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#target_link_options(${PROJECT_NAME} PRIVATE "SHELL:-ltbb")
