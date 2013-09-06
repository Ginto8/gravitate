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
    src/Perlin.cpp
    src/Perlin.hpp
)

set(SFML_STATIC_LIBRARIES TRUE)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 COMPONENTS main system window graphics REQUIRED)
message(STATUS "Libraries [${SFML_LIBRARIES}]")
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
if(WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
    set_target_properties(gravitate PROPERTIES LINK_FLAGS "-static-libgcc")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
endif()
