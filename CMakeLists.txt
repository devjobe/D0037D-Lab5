cmake_minimum_required (VERSION 3.8)

project ("Lab5")

set(CMAKE_CXX_STANDARD 17)


find_package(SDL2 CONFIG REQUIRED)
add_definitions(-DSDL_MAIN_HANDLED)

add_library(Lab5_Lib "Point2D.cpp" "Point2D.h" "Shape.h" "Shape.cpp" "Rectangle.h" "Rectangle.cpp" "Triangle.cpp" "Triangle.h" "Circle.h" "Circle.cpp" "Rgba.h" "Rgba.cpp")
target_link_libraries(Lab5_Lib PUBLIC SDL2::SDL2)

add_executable (Lab5_Task1 "task1.cpp")
target_link_libraries(Lab5_Task1 Lab5_Lib)

add_executable (Lab5_Task2 "task2.cpp")
target_link_libraries(Lab5_Task2 Lab5_Lib)


