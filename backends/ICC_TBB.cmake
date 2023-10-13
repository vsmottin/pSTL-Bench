# adding tbb compile definition for icc
if (CMAKE_CXX_COMPILER_ID STREQUAL "Intel" OR CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
    add_compile_definitions(USE_TBB)
else ()
    message(WARNING "Compiler ID does NOT match Intel compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()

# require tbb
find_package(TBB REQUIRED)

list(APPEND BACKEND_LINK_LIBRARIES "TBB::tbb")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")