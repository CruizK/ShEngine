cmake_minimum_required(VERSION 3.16)

if (${CMAKE_VERSION} VERSION_LESS 3.16)
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

file(GLOB_RECURSE SRC_FILES
    LIST_DIRECTORIES false
    "src/*.cpp" "src/*.h")

file(GLOB STB_IMAGE deps/stb_image/stb_image.h deps/stb_image/stb_image.c)
#file(GLOB CORE_SRC src/core/*.cpp src/core/*.h)
#file(GLOB GFX_SRC src/gfx/*.cpp src/gfx/*.h)
#file(GLOB IMGUI_SRC src/imgui/*.cpp src/imgui/*.h)
#file(GLOB BUFFER_SRC src/gfx/buffers/*.cpp src/gfx/buffers/*.h) 

#add_library(Engine STATIC 
#  ${CORE_SRC} 
#  ${GFX_SRC}
#  ${BUFFER_SRC} 
#  ${STB_IMAGE}
#)

add_library(Engine STATIC ${SRC_FILES} ${STB_IMAGE})

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

target_precompile_headers(Engine PRIVATE src/pch.h)

#Visual Studio Folders

set(SRC_ROOT_PATH "${Engine_SOURCE_DIR}/src")

foreach(SRC_FILE IN ITEMS ${SRC_FILES})
    get_filename_component(SRC_PATH "${SRC_FILE}" PATH)
    file(RELATIVE_PATH SRC_PATH_REL "${SRC_ROOT_PATH}" "${SRC_PATH}")
    string(REPLACE "/" "\\" GROUP_PATH "${SRC_PATH_REL}")
    source_group("${GROUP_PATH}" FILES ${SRC_FILE})
endforeach()


#source_group("core" FILES ${CORE_SRC})
#source_group("gfx" FILES ${GFX_SRC})
#source_group("gfx\\buffers" FILES ${BUFFER_SRC})
#source_group("imgui" FILES ${IMGUI_SRC})
