cmake_minimum_required(VERSION 3.3.2)
project(SudokuSuite LANGUAGES CXX DESCRIPTION "Program suite to generate and solve sudokus of any size")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include( "common" )
