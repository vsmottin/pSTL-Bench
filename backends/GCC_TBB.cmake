# adding tbb compile definition
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # set USE_TBB option to ON
    option(USE_TBB "Use TBB" ON)
    add_compile_definitions(USE_TBB)
endif ()

# require tbb
if (CMAKE_COMPILER_IS_GNUCXX)
    find_package(TBB REQUIRED) # for gcc only
    list(APPEND BACKEND_LINK_LIBRARIES "TBB::tbb")
endif ()


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")