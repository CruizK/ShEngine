cmake_minimum_required(VERSION 3.1)

project(glad VERSION 1.0)

add_library(glad STATIC src/glad.c include/glad/glad.h)
target_include_directories(glad PUBLIC include)
