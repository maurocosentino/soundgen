cmake_minimum_required(VERSION 3.16)

project(SoundGenCLI
        VERSION 0.1.0
        DESCRIPTION "CLI tool for generating WAV audio"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(soundgen
        src/main.cpp
)

# Directorios de includes
target_include_directories(soundgen PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include
)

# Warnings
target_compile_options(soundgen PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)