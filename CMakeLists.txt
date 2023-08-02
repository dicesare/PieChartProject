# cmake_minimum_required(VERSION 3.5)
# project(ProjetLibGD LANGUAGES C)

# set(CMAKE_C_STANDARD 99)

# find_path(GD_INCLUDE_DIR NAMES gd.h)
# find_library(GD_LIBRARY NAMES gd)

# add_executable(pie main.c)

# target_include_directories(pie PRIVATE ${GD_INCLUDE_DIR})
# target_link_libraries(pie ${GD_LIBRARY} m)

# install(TARGETS pie
# LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

cmake_minimum_required(VERSION 3.5)
project(PieChartProject LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)

# Find the GD library
find_path(GD_INCLUDE_DIR NAMES gd.h)
find_library(GD_LIBRARY NAMES gd)

# Create the executable
add_executable(PieChart main.c)

# Link the GD library
target_include_directories(PieChart PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${GD_INCLUDE_DIR})
target_link_libraries(PieChart ${GD_LIBRARY} m)

# Specify installation destination
install(TARGETS PieChart
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
