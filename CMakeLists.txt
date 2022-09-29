cmake_minimum_required(VERSION 3.0.0)
project(Lexer VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Lexer 
    Sources/main.cpp
    Headers/lexer.h
    Sources/lexer.cpp
    Headers/markTable.h
    Sources/markTable.cpp
    Headers/token.h
    Sources/token.cpp
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
