cmake_minimum_required(VERSION 3.21)
project(Coursework-AC-Waveform-Final)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Coursework-AC-Waveform-Final
        io.c
        io.h
        waveform.c
        waveform.h
        main.c )