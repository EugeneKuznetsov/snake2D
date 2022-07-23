cmake_minimum_required(VERSION 3.20)

project(
    Snake2D
    VERSION 1.2.0
    LANGUAGES CXX)

include(BuildSettings)
include(CompilerSettings)
include(Packages)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
