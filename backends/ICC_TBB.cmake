if (NOT (CMAKE_CXX_COMPILER_ID STREQUAL "Intel" OR CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM"))
    message(WARNING "Make sure you use an Intel compiler. Your compiler ID: ${CMAKE_CXX_COMPILER_ID}")
endif ()

option(USE_TBB "Use TBB" ON)
add_compile_definitions(USE_TBB)
add_compile_definitions(USE_PSTL)

# Find package TBB
find_package(TBB REQUIRED)
if (NOT TARGET TBB::tbb)
    message(FATAL_ERROR "TBB not found")
else ()
    list(APPEND BACKEND_LINK_LIBRARIES "TBB::tbb")
endif ()