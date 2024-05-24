add_compile_definitions(PSTL_BENCH_USE_TBB)
add_compile_definitions(PSTL_BENCH_USE_PSTL)

add_compile_definitions(PSTL_BENCH_BACKEND="TBB")

# Find package TBB
find_package(TBB REQUIRED)
if (NOT TARGET TBB::tbb)
    message(FATAL_ERROR "TBB not found")
else ()
    message(STATUS "TBB found")
    list(APPEND LINK_LIBRARIES TBB::tbb)
endif ()