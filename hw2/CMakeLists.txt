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
        src/parallel/parallel.h
        src/parallel/parallel.c
        src/trivial/trivial.h
        src/trivial/trivial.c
        src/main.c
        )

include_directories("src/trivial")
include_directories("src/parallel")

add_library(libtest_algo STATIC ${libtest_algo_sources})
add_library(Dinlib_algo SHARED ${libtest_algo_sources})

set(main_sources
        src/main.c
        src/trivial/trivial.h
        src/parallel/parallel.h
        )

add_executable(main ${main_sources})
target_link_libraries(main ${CMAKE_DL_LIBS} Dinlib_algo)