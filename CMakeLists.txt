cmake_minimum_required(VERSION 3.11)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(SudokuSolver main.cpp Matrix.cpp Matrix.h)
#add_executable(SudokuSolver main.cpp)
