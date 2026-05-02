cmake_minimum_required(VERSION 3.21)
project(Coursework_AC_Waveform C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Coursework_AC_Waveform
        io.c
        io.h
        waveform.c
        waveform.h
        main.c )
