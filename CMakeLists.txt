cmake_minimum_required(VERSION 3.17)
project(DZ1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

set(LIB_SOURCE_FILES src/main.c src/test_main.cpp)

add_library(url_parse_std_lib STATIC ${LIB_SOURCE_FILES})

if (EN_TESTS)
    # sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
    enable_testing()
    find_package(GTest REQUIRED)
    # adds the gtest include directory
    include_directories(${GTEST_INCLUDE_DIRS})

    # html tag
    add_executable(test_main.out src/test_main.cpp)
    target_link_libraries(test_main.out url_parse_std_lib)
    # links gtest
    target_link_libraries(test_main.out ${GTEST_LIBRARIES})
    target_link_libraries(test_main.out pthread)
endif ()

if (VALGRIND_EN)
    message("Valgrind enabled")
    find_program(VALGRIND valgrind REQUIRED)

    if(VALGRIND)
        message("Valgrind found")
        set(VALGRIND_OPTIONS "--leak-check=full --track-origins=yes --error-exitcode=1")
    endif ()

endif ()