cmake_minimum_required(VERSION 3.15)
project(tik_lab1_pure C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_RELEASE "-O3 -lm")
set(CMAKE_C_FLAGS_DEBUG  "-lm")

add_executable(tik_lab1_pure main.c)