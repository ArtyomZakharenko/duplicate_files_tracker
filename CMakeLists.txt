cmake_minimum_required(VERSION 3.25)

project(Duplicate_File_Tracker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic  -std=c++11 -lcrypto")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb -O0")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror -O3")

set(SOURCE src/main.cpp
        src/logger.cpp
        src/hash_generator.cpp
        src/duplicates_handler.cpp
        )

set(HEADER include/logger.h
        include/hash_generator.h
        include/duplicates_handler.h
        )

add_executable(dft ${SOURCE} ${HEADER})

