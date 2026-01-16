cmake_minimum_required(VERSION 4.1)
project(clox5 C)

set(CMAKE_C_STANDARD 23)

add_executable(clox5 main.c
        common.h
        chunk.h
        chunk.c
        memory.h
        memory.c
        debug.h
        debug.c
        value.h
        value.c
        vm.h
        vm.c
        compiler.h
        compiler.c
        scanner.h
        scanner.c)
