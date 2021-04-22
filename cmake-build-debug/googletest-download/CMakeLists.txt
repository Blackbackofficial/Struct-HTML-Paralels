cmake_minimum_required(VERSION 3.8)

project(extern-download NONE)


include(ExternalProject)
ExternalProject_Add(
googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           release-1.10.0
  SOURCE_DIR        "/Users/ivanchernov/CLionProjects/DZ1/cmake-build-debug/googletest-src"
  BINARY_DIR        "/Users/ivanchernov/CLionProjects/DZ1/cmake-build-debug/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
