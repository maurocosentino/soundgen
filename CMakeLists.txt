cmake_minimum_required(VERSION 3.16)
project(soundgen)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        src
)

add_executable(soundgen
        src/main.cpp

        src/cli/CommandParser.cpp
        src/audio/WaveGenerator.cpp
        src/wav/WavWriter.cpp
)