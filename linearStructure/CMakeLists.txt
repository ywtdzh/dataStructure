include_directories(headerFiles)

add_executable(linearList linearList.cpp linearListTest.cpp)
add_executable(stack stackTest.cpp)
add_executable(sqList sqList.cpp sqListTest.cpp)
add_executable(doubleWayCycleChain DWCCTest.cpp doubleWayCycleChain.cpp)