cmake_minimum_required(VERSION 3.5)

project(RayTracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")


################################
# GTest
################################
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY (googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


################################
# Unit Tests
################################
add_executable(ray_test
    test/test.cpp
)
target_link_libraries(ray_test
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(ray_test)



add_executable(RayTracingCli
    main.cpp
    )
