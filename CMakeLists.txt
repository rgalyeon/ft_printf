cmake_minimum_required(VERSION 3.13.4)
project(ft_printf C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)
include_directories(libft/includes)
aux_source_directory(srcs/ src)
aux_source_directory(srcs/utils utils)
aux_source_directory(srcs/processing_types types)

add_executable(ft_printf ${src} ${utils} ${types}
		main.c)
target_link_libraries(ft_printf ${PROJECT_SOURCE_DIR}/libft/libft.a)