cmake_minimum_required(VERSION 3.30)
project(webserver C)

set(CMAKE_C_STANDARD 11)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(webserver main.c
        connect.c
        analysisHTTP.c
        include/analysisHTTP.h
        include/connect.h
        configure.c
        include/configure.h)
