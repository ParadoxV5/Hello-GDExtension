cmake_minimum_required(VERSION 3.25)
project(hello.gdextension C)
set(CMAKE_C_STANDARD 17)

add_library(hello.gdextension SHARED hello.gdextension.c)
