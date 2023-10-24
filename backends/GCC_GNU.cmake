if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(WARNING "Make sure you use a GCC compiler. Your compiler ID: ${CMAKE_CXX_COMPILER_ID}")
endif ()

option(USE_GNU_PSTL "Use GNU PSTL" ON)
add_compile_definitions(USE_GNU_PSTL)

# Find package OpenMP
find_package(OpenMP REQUIRED)
if (NOT TARGET OpenMP::OpenMP_CXX)
    message(FATAL_ERROR "OpenMP target not found")
else ()
    list(APPEND BACKEND_LINK_LIBRARIES "OpenMP::OpenMP_CXX")
endif ()