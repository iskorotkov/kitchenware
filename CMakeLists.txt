cmake_minimum_required(VERSION 3.16)
project(kitchenware)

set(CMAKE_CXX_STANDARD 17)

include_directories(containers)
include_directories(kitchen)

add_executable(kitchenware
        containers/binary_tree.h
        kitchen/electric_stove.cpp
        kitchen/electric_stove.h
        kitchen/gas_stove.cpp
        kitchen/gas_stove.h
        kitchen/kitchenware.cpp
        kitchen/kitchenware.h
        kitchen/saucepan.cpp
        kitchen/saucepan.h
        kitchen/slow_cooker.cpp
        kitchen/slow_cooker.h
        kitchen/stove.cpp
        kitchen/stove.h
        main.cpp containers/binary_node.h)
