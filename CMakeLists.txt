cmake_minimum_required(VERSION 3.11)
project(SudokuSolver)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
set(CMAKE_CXX_STANDARD 17)

add_executable(SudokuSolver main.cpp Matrix.cpp Matrix.h)
#add_executable(SudokuSolver main.cpp)
