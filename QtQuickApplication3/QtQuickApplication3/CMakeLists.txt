cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Project4)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Project4a
main.cpp
ingredient.cpp
dish.cpp
mainwindow.cpp
)

set(CMAKE_AUTOUIC ON)