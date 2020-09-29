
cmake_minimum_required(VERSION 3.1)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(ShEngine VERSION 0.1 DESCRIPTION "ShEngine" LANGUAGES CXX)

add_subdirectory(Engine)
add_subdirectory(Sandbox)