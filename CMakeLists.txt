cmake_minimum_required(VERSION 3.20)

project(NierE_AllToBeNice)

set(CMAKE_CXX_STANDARD 23)

# copy from https://github.com/JoeyDeVries/LearnOpenGL#CMakeLists.txt
IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF (NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

if (WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif (WIN32)

#link_directories(${CMAKE_SOURCE_DIR}/lib)

# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")
# find_package(SOIL REQUIRED)
# message(STATUS "Found SOIL in ${SOIL_INCLUDE_DIR}")
# find_package(GLEW REQUIRED)
# message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")
find_package(Freetype REQUIRED)
message(STATUS "Found Freetype in ${FREETYPE_INCLUDE_DIRS}")

if (WIN32)
    set(LIBS glfw3 opengl32 assimp freetype irrKlang)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
    find_package(OpenGL REQUIRED)
    add_definitions(${OPENGL_DEFINITIONS})
    find_package(X11 REQUIRED)
    # note that the order is important for setting the libs
    # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
    set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype ${ASSIMP_LIBRARY})
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
elseif (APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
    include_directories(/System/Library/Frameworks)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKit_LIBRARY IOKit)
    find_library(CoreVideo_LIBRARY CoreVideo)
    mark_as_advanced(COCOA_LIBRARY OpenGL_LIBRARY)
    set(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
    set(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY} ${FREETYPE_LIBRARIES})
    set(LIBS ${LIBS} ${APPLE_LIBS})
else ()
    set(LIBS)
endif (WIN32)

link_libraries(${LIBS})

include_directories(
        ${CMAKE_SOURCE_DIR}/
        ${CMAKE_SOURCE_DIR}/3rdparty/
        ${CMAKE_SOURCE_DIR}/src/
)

add_executable(NierE_AllToBeNice
        # 3rdparty
        # 3rdparty/glad/glad.c
        3rdparty/stb/stb_image.cc

        # project NierE_AllToBeNice
        src/main.cc

        src/atn/common/utility.h

        src/atn/base/game_window.cc
        src/atn/base/game_window.h
        src/atn/base/window_context.h
        src/atn/base/game_engine.cc
        src/atn/base/game_engine.h
        src/atn/base/object.cc
        src/atn/base/object.h
        src/atn/base/game_object.cc
        src/atn/base/game_object.h
        src/atn/base/text_object.cc
        src/atn/base/text_object.h
        src/atn/base/garbage_collection.cc
        src/atn/base/garbage_collection.h

        src/atn/render/render_engine.cc
        src/atn/render/render_engine.h
        src/atn/render/render_context.h
        src/atn/render/shader.cc
        src/atn/render/shader.h
        src/atn/render/text_render.cc
        src/atn/render/text_render.h

        src/atn/logic/logic_engine.cc
        src/atn/logic/logic_engine.h
        src/atn/logic/logic_context.h

        src/atn/physics/physics_engine.cc
        src/atn/physics/physics_engine.h
        src/atn/physics/physics_context.h

        src/atn/game/game_control.cc
        src/atn/game/game_control.h
        src/atn/game/pod.cc
        src/atn/game/pod.h
        src/atn/game/light.cc
        src/atn/game/light.h
        src/atn/game/pod_bullet.cc
        src/atn/game/pod_bullet.h
        src/atn/game/enemy.cc
        src/atn/game/enemy.h
        src/atn/game/enemy_bullet.cc
        src/atn/game/enemy_bullet.h
        src/atn/game/enemy_trace.cc
        src/atn/game/enemy_trace.h
        src/atn/game/enemy_attack.cc
        src/atn/game/enemy_attack.h)
