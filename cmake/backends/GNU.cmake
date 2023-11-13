add_compile_definitions(USE_GNU)

add_compile_definitions(BENCHMARK_BACKEND="OMP")

# Find package OpenMP
find_package(OpenMP REQUIRED)
if (NOT TARGET OpenMP::OpenMP_CXX)
    message(FATAL_ERROR "OpenMP target not found")
else ()
    message(STATUS "OpenMP target found")
    list(APPEND LINK_LIBRARIES OpenMP::OpenMP_CXX)
endif ()