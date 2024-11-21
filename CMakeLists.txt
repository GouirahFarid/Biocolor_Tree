cmake_minimum_required(VERSION 3.10)

# Project name
project(RedBlackAndAVLTreeProject)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Source files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCES
    ${SRC_DIR}/rbtree.c
    ${SRC_DIR}/avltree.c
    ${SRC_DIR}/main.c
)

# Include directories
include_directories(${SRC_DIR})

# Create the executable
add_executable(rb_avl_trees ${SOURCES})
