include_directories(headerFiles) #设定头文件目录,以当前位置计算相对路径
add_subdirectory(exercise)

add_executable(linearList linearList.cpp linearListTest.cpp) #指定要生成的可执行文件和用来生成它的源文件cpp
add_executable(stack stackTest.cpp)
add_executable(sqList sqList.cpp sqListTest.cpp)
add_executable(doubleWayCycleChain DWCCTest.cpp doubleWayCycleChain.cpp)
add_executable(queue queueTest.cpp)