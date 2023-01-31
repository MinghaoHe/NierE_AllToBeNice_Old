CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

PROJECT(NierE_AllToBeNice)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

IF(WIN32)
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
ENDIF(WIN32)

LINK_DIRECTORIES("${CMAKE_SOURCE_DIR}/3rdparty/lib")

# find the required packages
FIND_PACKAGE(GLM REQUIRED)
MESSAGE(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
FIND_PACKAGE(GLFW3 REQUIRED)
MESSAGE(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
ADD_DEFINITIONS(-DGLFW_INCLUDE_NONE)
IF(APPLE)
  FIND_PACKAGE(Freetype REQUIRED)
  MESSAGE(STATUS "Found Freetype in ${FREETYPE_INCLUDE_DIRS}")
ENDIF(APPLE)

IF(WIN32)
  SET(LIBS glfw3 opengl32 freetype)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES)
ELSEIF(APPLE)
  ADD_DEFINITIONS(-DGL_SILENCE_DEPRECATION)
  INCLUDE_DIRECTORIES(/System/Library/Frameworks)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  FIND_LIBRARY(IOKit_LIBRARY IOKit)
  FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
  MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
  SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
  SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY} ${FREETYPE_LIBRARIES})
  SET(LIBS ${LIBS} ${APPLE_LIBS})
ELSE()
  SET(LIBS)
ENDIF(WIN32)

LINK_LIBRARIES(${LIBS})

INCLUDE_DIRECTORIES(
    "${CMAKE_SOURCE_DIR}/"
    "${CMAKE_SOURCE_DIR}/3rdparty/"
    "${CMAKE_SOURCE_DIR}/src/")

SET(ATN_SOURCE_FILES
    # 3rdparty
    3rdparty/glad/glad.c
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

SET(ATN_SHADER_FILES
    src/atn/game/shader/pod.vs
    src/atn/game/shader/pod.fs
    src/atn/game/shader/pod_bullet.vs
    src/atn/game/shader/pod_bullet.fs
    src/atn/game/shader/enemy.vs
    src/atn/game/shader/enemy.fs
    src/atn/game/shader/enemy_bullet.vs
    src/atn/game/shader/enemy_bullet.fs)

ADD_EXECUTABLE(NierE_AllToBeNice ${ATN_SOURCE_FILES} ${ATN_SHADER_FILES})
SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ATN_SOURCE_FILES} ${ATN_SHADER_FILES})