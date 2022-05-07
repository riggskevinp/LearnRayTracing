cmake_minimum_required(VERSION 3.16)

project(RayTracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

message(STATUS "Current cmake version: ${CMAKE_VERSION}")

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(eigen eigen/Eigen)

set(CPP_SOURCES
        main.cpp
        vec3.h
        color.h
        ray.h
        sqrt_help.h
        hittable.h
        sphere.h
        hittable_list.h
        rtweekend.h
        camera.h
        material.h
)

add_executable(RayTracingCli
        ${CPP_SOURCES}
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
            ${CPP_SOURCES}
    )
    target_link_libraries(ray_test
        gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(ray_test)
endif()


