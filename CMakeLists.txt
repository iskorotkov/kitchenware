cmake_minimum_required(VERSION 3.16)
project(kitchenware)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER "C:/Users/korot/scoop/apps/llvm/9.0.0/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Users/korot/scoop/apps/llvm/9.0.0/bin/clang++.exe")

enable_testing()

include_directories(src/containers)
include_directories(src/kitchen)
include_directories(src/containers/views)
include_directories(src/containers/balancing)
include_directories(src/ui)
include_directories(src/containers/errors)

add_executable(kitchenware
        src/containers/binary_tree.h
        src/kitchen/electric_stove.cpp
        src/kitchen/electric_stove.h
        src/kitchen/gas_stove.cpp
        src/kitchen/gas_stove.h
        src/kitchen/kitchenware.cpp
        src/kitchen/kitchenware.h
        src/kitchen/saucepan.cpp
        src/kitchen/saucepan.h
        src/kitchen/slow_cooker.cpp
        src/kitchen/slow_cooker.h
        src/kitchen/stove.cpp
        src/kitchen/stove.h
        src/containers/binary_node.h
        src/containers/views/prefix_view.h
        src/containers/views/postfix_view.h
        src/containers/views/infix_view.h
        src/containers/declarations.h
        src/containers/poly_tree.h
        src/containers/balancing/red_black.h
        src/ui/dialogue.cpp
        src/ui/dialogue.h
        src/containers/errors/value_exists_error.cpp
        src/containers/errors/value_exists_error.h
        src/main.cpp)
