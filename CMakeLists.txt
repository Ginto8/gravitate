cmake_minimum_required(VERSION 2.6)
project(gravitate)

set(CMAKE_MODULE_PATH 
    "/usr/local/share/SFML/cmake/Modules/;${CMAKE_MODULE_PATH}")

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# Define sources and executable
set(EXECUTABLE_NAME "gravitate")
add_executable(${EXECUTABLE_NAME}
    src/main.cpp
    src/Planet.cpp
    src/Planet.hpp
    src/PlanetSystem.cpp
    src/PlanetSystem.hpp
    src/Vector.hpp
)

# Detect and add SFML
find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

