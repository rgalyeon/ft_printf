cmake_minimum_required(VERSION 3.15)
project(ft_printf C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)
include_directories(libft/includes)
aux_source_directory(srcs/ src)

add_executable(ft_printf ${src})
target_link_libraries(ft_printf ${PROJECT_SOURCE_DIR}/libft/libft.a)