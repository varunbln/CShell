cmake_minimum_required(VERSION 3.10)
project(CShell)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(Readline REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${Readline_C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${Readline_EXE_LINKER_FLAGS}")

set(CMAKE_C_STANDARD 11)

set(SOURCES
        src/builtins.c
        src/main.c
        )

set(HEADERS
        src/builtins.h
        src/colors.h
        )

add_executable(cshell ${SOURCES} ${HEADERS})
target_link_libraries(cshell readline)

