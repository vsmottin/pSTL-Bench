add_compile_definitions(PSTL_BENCH_USE_HPX)

add_compile_definitions(PSTL_BENCH_BACKEND="HPX")

# Find package HPX
find_package(HPX REQUIRED)
if (NOT TARGET HPX::hpx)
    message(FATAL_ERROR "HPX not found!")
else ()
    message(STATUS "HPX found")
    list(APPEND LINK_LIBRARIES HPX::hpx HPX::wrap_main)
endif ()
