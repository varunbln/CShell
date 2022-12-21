cmake_minimum_required(VERSION 3.10)
project(CShell)

set(CMAKE_C_STANDARD 11)

set(SOURCES
        src/builtins.c
        src/main.c
        )

set(HEADERS
        src/builtins.h
        )

add_executable(cshell ${SOURCES} ${HEADERS})