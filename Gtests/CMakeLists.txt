include_directories("../src/trivial")
include_directories("../src/parallel")

file(GLOB tests "*.cpp")
list(REMOVE_ITEM tests "main.cpp")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage -fprofile-arcs")
enable_testing()
foreach (file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${file}
            "main.cpp"
            )
    target_link_libraries("${name}_tests"
            libtest_algo
            gtest_main
            )
    add_test(NAME ${name}
            COMMAND "${name}_tests"
            WORKING_DIRECTORY ..
            )
endforeach ()