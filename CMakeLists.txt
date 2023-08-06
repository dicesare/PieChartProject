cmake_minimum_required(VERSION 3.5)
project(PieChartProject LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)

# Find the GD library
find_path(GD_INCLUDE_DIR NAMES gd.h)
find_library(GD_LIBRARY NAMES gd)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${GD_INCLUDE_DIR})

# Source files
set(SOURCES 
    src/main.c 
    src/model/model.c 
    src/view/view.c 
    src/controller/controller.c
    src/utils/utils.c
)

# Create the executable
add_executable(PieChart ${SOURCES})

# Link the GD library
target_link_libraries(PieChart ${GD_LIBRARY} m)

# Specify installation destination
install(TARGETS PieChart
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
