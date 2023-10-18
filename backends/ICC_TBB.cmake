# adding tbb compile definition for icc
if (CMAKE_CXX_COMPILER_ID STREQUAL "Intel" OR CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
    # set USE_TBB option to ON
    option(USE_TBB "Use Intel TBB" ON)
    add_compile_definitions(USE_TBB)
else ()
    message(WARNING "Compiler ID does NOT match Intel compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()

# require tbb
find_package(TBB REQUIRED)

if (NOT TBB_FOUND)
    message(FATAL_ERROR "TBB not found")
endif ()

list(APPEND BACKEND_LINK_LIBRARIES "TBB::tbb")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")