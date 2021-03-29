cmake_minimum_required(VERSION 3.8)
project(DZ1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage -fprofile-arcs")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${EXTRA_BINCFLAGS})

include(configure_test.cmake)
add_subdirectory(Gtests)
include(configure_cppcheck.cmake)

include_directories(src)
set(libtest_algo_sources
        ${PROJECT_SOURCE_DIR}/src/parallel/parallel.h
        ${PROJECT_SOURCE_DIR}/src/parallel/parallel.c
        ${PROJECT_SOURCE_DIR}/src/trivial/trivial.h
        ${PROJECT_SOURCE_DIR}/src/trivial/trivial.c
        ${PROJECT_SOURCE_DIR}/src/main.c
        )

#include_directories("${PROJECT_SOURCE_DIR}/src/trivial")
include_directories("${PROJECT_SOURCE_DIR}/src/parallel")

add_library(libtest_algo STATIC ${libtest_algo_sources})

set(main_sources
        ${PROJECT_SOURCE_DIR}/src/main.c
        ${PROJECT_SOURCE_DIR}/src/trivial/trivial.h
        ${PROJECT_SOURCE_DIR}/src/parallel/parallel.h
        )

add_executable(main ${main_sources})
target_link_libraries(main libtest_algo)