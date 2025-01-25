cmake_minimum_required (VERSION 3.5.0)
message(STATUS "CMake version: ${CMAKE_VERSION}")

# Project name and a few useful settings. Other commands can pick up the results
project(
  example_app
  DESCRIPTION "Example Application"
  LANGUAGES CXX C)


# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
  set(CMAKE_CXX_EXTENSIONS FALSE) 
endif()


# ------------------------------------
# Add Example Application
# ------------------------------------
add_subdirectory(src/example_app)
