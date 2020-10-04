# Copyright (C) 2018 Tomasz Gałaj

cmake_minimum_required(VERSION 3.5)
project(OpenGL)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)


# Configure assets header file
include_directories(${CMAKE_BINARY_DIR}/src)

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#######################################
# LOOK for the packages that we need! #
#######################################

# OpenGL
find_package(OpenGL REQUIRED)

# GLM
# OpenGL Mathematics (GLM) is a header only C++ mathematics library
# Enable Matrix, Vec, etc
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW
# It provides a simple API for creating windows, contexts and surfaces, receiving input and events.
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# GLEW
#find_package(GLEW REQUIRED)
#message(STATUS "GLEW included at ${GLEW_INCLUDE_DIR}")

# GLAD
add_library(GLAD "thirdparty/glad.c")

# STB_IMAGE
add_library(STB_IMAGE "thirdparty/stb_image.cpp")

# ASSIMP
# Open Asset Import Library (Assimp)
# A portable Open-Source library to import various well-known 3D model formats in a uniform manner.
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

# Put all libraries into a variable
set(LIBS glfw3 opengl32 assimp STB_IMAGE GLAD)

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/include"
)

add_subdirectory(src)

#Define the link libraries
#target_link_libraries(${PROJECT_NAME} ${LIBS})

