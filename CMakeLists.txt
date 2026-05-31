cmake_minimum_required(VERSION 3.20)

project(Titan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Required for clangd / Firebase Studio IntelliSense.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Titan
    Source/Titan/Main.cpp

    Source/Titan/Lexer/Lexer.cpp

    Source/Titan/Language/Keywords.cpp

    Source/Titan/Tests/TestRunner.cpp
    Source/Titan/Tests/LexerTests.cpp
)

target_include_directories(Titan PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Titan
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Titan/Lexer
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Titan/Language
)

if (MSVC)
    target_compile_options(Titan PRIVATE
        /W4
        /permissive-
    )
else()
    target_compile_options(Titan PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()