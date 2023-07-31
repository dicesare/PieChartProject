cmake_minimum_required(VERSION 3.5)
project(ProjetLibGD LANGUAGES C)

set(CMAKE_C_STANDARD 99)

find_path(GD_INCLUDE_DIR NAMES gd.h)
find_library(GD_LIBRARY NAMES gd)

add_executable(pie main.c)

target_include_directories(pie PRIVATE ${GD_INCLUDE_DIR})
target_link_libraries(pie ${GD_LIBRARY})

install(TARGETS pie
LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
