list(APPEND CPPCHECK_CMAKE_ARGS
        "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
        )

include(ExternalProject)
ExternalProject_Add(
        cppcheck
        GIT_REPOSITORY https://github.com/danmar/cppcheck.git
        GIT_TAG 1.79
        GIT_SHALLOW 1
        CMAKE_ARGS ${CPPCHECK_CMAKE_ARGS}
        PREFIX ${CMAKE_BINARY_DIR}/external/cppcheck/prefix
        TMP_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/tmp
        STAMP_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/stamp
        DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/download
        SOURCE_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/src
        BINARY_DIR ${CMAKE_BINARY_DIR}/external/cppcheck/build
)

list(APPEND CPPCHECK_ARGS
        --enable=warning,style,performance,portability,unusedFunction
        --std=c11
        --verbose
        --error-exitcode=1
        --language=c
        -DMAIN=main
        -I ${CMAKE_SOURCE_DIR}/src/trivial
        ${CMAKE_SOURCE_DIR}/trivial/*.h
        ${CMAKE_SOURCE_DIR}/src/*.c
        )

add_custom_target(
        check
        COMMAND ${CMAKE_BINARY_DIR}/bin/cppcheck ${CPPCHECK_ARGS}
        COMMENT "running cppcheck"
)