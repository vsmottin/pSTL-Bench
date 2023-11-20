if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "PGI" AND
        NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "NVIDIA" AND
        NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "NVHPC")
    message(WARNING "To use NVHPC_CUDA backend, make sure you use a NVIDIA compiler. Your compiler ID: ${CMAKE_CXX_COMPILER_ID}")
endif ()

add_compile_definitions(USE_PSTL)
add_compile_definitions(USE_GPU)

add_compile_definitions(BENCHMARK_BACKEND="CUDA")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdpar")