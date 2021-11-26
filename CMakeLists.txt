cmake_minimum_required(VERSION 3.20)
project(Hw_Alekseenko)

set(CMAKE_CXX_STANDARD 14)

add_executable(Hw1_Alekseenko homework1/hw1.cpp)
add_executable(Hw2_Alekseenko homework2/hw2.cpp)
add_subdirectory(homework1)
add_subdirectory(homework2)
