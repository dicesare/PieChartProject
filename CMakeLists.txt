cmake_minimum_required(VERSION 3.5)

project(PieChartProject LANGUAGES C)

find_package(gd)

add_executable(PieChartProject main.c)

install(TARGETS PieChartProject
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
