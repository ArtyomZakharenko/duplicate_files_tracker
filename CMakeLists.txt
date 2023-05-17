cmake_minimum_required(VERSION 3.25)
project(Dublicate_File_Tracker)

set(CMAKE_CXX_STANDARD 14)

add_executable(Dublicate_File_Tracker main.cpp logger.cpp logger.h file_hasher.cpp file_hasher.h)
