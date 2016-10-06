cmake_minimum_required(VERSION 3.6) #当前使用CMake版本
project(dataStructure) #工程名称

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static") #编译选项,包括gcc的参数

add_subdirectory(linearStructure) #到指定位置寻找CMakeLists.txt
add_subdirectory(treeStructure)
add_subdirectory(graphStructure)