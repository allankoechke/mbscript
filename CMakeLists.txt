cmake_minimum_required(VERSION 4.1)
project(mbscript)

set(CMAKE_CXX_STANDARD 20)

add_executable(mbs
        src/main.cpp

        includes/mbs/frontend/lexer.h
        src/frontend/lexer.cpp

        includes/mbs/frontend/parser.h
        src/frontend/parser.cpp
        includes/mbs/frontend/token.h
        src/frontend/token.cpp
        includes/mbs/frontend/exceptions.h
        src/frontend/exceptions.cpp
        includes/mbs/frontend/ast.h
        src/frontend/ast.cpp
        src/backend/runtime.cpp
        includes/mbs/backend/runtime.h
        includes/mbs/backend/interpreter.h
        src/backend/interpreter.cpp
)
