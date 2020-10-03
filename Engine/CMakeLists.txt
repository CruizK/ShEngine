cmake_minimum_required(VERSION 3.1)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Engine VERSION 0.1 DESCRIPTION "ShEngine" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

#GLFW Build Settings
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (FREETYPE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}deps/freetype-2.9/include)
set (FREETYPE_LIBRARIES freetype)

#Find opengl
find_package(OpenGL REQUIRED)

add_subdirectory(deps/glad)
add_subdirectory(deps/glfw)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/glm)
add_subdirectory(deps/imgui)

add_subdirectory(deps/freetype-2.9)
add_subdirectory(deps/freetype-gl/ftgl)

file(GLOB STB_IMAGE deps/stb_image/stb_image.h deps/stb_image/stb_image.c)
file(GLOB CORE_SRC src/core/*.cpp src/core/*.h)
file(GLOB GFX_SRC src/gfx/*.cpp src/gfx/*.h)
file(GLOB BUFFER_SRC src/gfx/buffers/*.cpp src/gfx/buffers/*.h) 

add_library(Engine STATIC 
  ${CORE_SRC} 
  ${GFX_SRC}
  ${BUFFER_SRC} 
  ${STB_IMAGE}
)

target_link_libraries(Engine PUBLIC
  glfw
  spdlog
  imgui
  glad
  freetype-gl
  freetype
  ${OPENGL_gl_LIBRARY}
)

set_target_properties(
    glfw
    spdlog
    imgui
    glad
    freetype-gl
    freetype
    PROPERTIES
        FOLDER "deps"
)

target_include_directories(Engine PUBLIC 
  deps/glm 
  deps/freetype-2.9/include 
  deps/freetype-gl
  deps/stb_image
)

#Visual Studio Folders

source_group("core" FILES ${CORE_SRC})
source_group("gfx" FILES ${GFX_SRC})
source_group("gfx\\buffers" FILES ${BUFFER_SRC})
