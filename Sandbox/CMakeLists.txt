cmake_minimum_required(VERSION 3.16)

if (${CMAKE_VERSION} VERSION_LESS 3.16)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Sandbox VERSION 0.1 DESCRIPTION "Sandbox" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES src/*.h src/*.cpp)
file(GLOB SHADER_FILES res/shaders/*.shader)
file(GLOB TEXTURE_FILES res/textures/*.png)

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

add_executable(Sandbox 
    ${SRC_FILES}
    ${SHADER_FILES}
    ${TEXTURE_FILES}
)

target_link_libraries(Sandbox PRIVATE
    Engine
)

target_include_directories(Sandbox PRIVATE
    ../Engine/src)

source_group("src" FILES ${SRC_FILES})
source_group("res\\shaders" FILES ${SHADER_FILES})
source_group("res\\textures" FILES ${TEXTURE_FILES})
