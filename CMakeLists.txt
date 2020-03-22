cmake_minimum_required(VERSION 3.16)
project(kitchenware)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER "C:/Users/korot/scoop/apps/llvm/9.0.0/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Users/korot/scoop/apps/llvm/9.0.0/bin/clang++.exe")

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
