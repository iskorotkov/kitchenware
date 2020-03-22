cmake_minimum_required(VERSION 3.16)

include_directories(containers)
include_directories(kitchen)
include_directories(containers/views)
include_directories(containers/balancing)
include_directories(ui)
include_directories(containers/errors)

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
        containers/binary_node.h
        containers/views/prefix_view.h
        containers/views/postfix_view.h
        containers/views/infix_view.h
        containers/declarations.h
        containers/poly_tree.h
        containers/balancing/red_black.h
        ui/dialogue.cpp
        ui/dialogue.h
        containers/errors/value_exists_error.cpp
        containers/errors/value_exists_error.h
        main.cpp)
