cmake_minimum_required(VERSION 3.10)

project(RayTracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

message(STATUS "Current cmake version: ${CMAKE_VERSION}")

include_directories(eigen eigen/Eigen)

add_executable(RayTracingCli
        main.cpp
        vec3.h
        color.h
        ray.h
        sqrt_help.h
)



#Comment out to disable testing
include(CTest)
enable_testing()

if(BUILD_TESTING)
####################################
##### Unit Tests: GTest
####################################
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    ADD_SUBDIRECTORY (googletest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    add_executable(ray_test
            test/test.cpp
            vec3.h
            color.h
            ray.h
            sqrt_help.h
    )
    target_link_libraries(ray_test
        gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(ray_test)
endif()


