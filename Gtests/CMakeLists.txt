include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

if (ENABLE_GCOV)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage -fprofile-arcs")
endif ()


foreach (file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp"
            )
    target_link_libraries("${name}_tests"
            libmoodfinder_s
            gtest_main
            )
    add_test(NAME ${name}
            COMMAND "${name}_tests"
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            )
endforeach ()