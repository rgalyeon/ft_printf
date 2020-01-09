cmake_minimum_required(VERSION 3.15)
project(ft_printf C)

set(CMAKE_C_STANDARD 99)

add_executable(ft_printf main.c ft_printf.c includes/ft_printf.h)