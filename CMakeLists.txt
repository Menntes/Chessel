cmake_minimum_required(VERSION 3.10)
project(Chessel CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate build/compile_commands.json for editor IntelliSense (clangd, VS Code C/C++).
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Chessel
    src/main.cpp
    src/Board.cpp
    src/MoveGenerator.cpp
)

# Headers live in include/, so #include "Board.h" resolves without path prefixes.
target_include_directories(Chessel PRIVATE include)
