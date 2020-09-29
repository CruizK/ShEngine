cmake_minimum_required(VERSION 3.1)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Sandbox VERSION 0.1 DESCRIPTION "Sandbox" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SRC_FILES src/*.h src/*.cpp)

add_executable(Sandbox ${SRC_FILES})

target_link_libraries(Sandbox PRIVATE
    Engine
)

target_include_directories(Sandbox PRIVATE
    ../Engine/src)