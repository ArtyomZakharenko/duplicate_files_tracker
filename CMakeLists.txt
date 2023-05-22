cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

project(Duplicate_File_Tracker)
set(CMAKE_MAKE_PROGRAM /usr/bin/make)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        dft
        main.cpp
        logger.cpp
        logger.h
        hash_generator.cpp
        hash_generator.h
        duplicates_handler.cpp
        duplicates_handler.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto")