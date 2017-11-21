cmake_minimum_required(VERSION 2.6)
project(Raycasting)

# SETTING UP DIRECTORIES

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

# END DIRECTORY SETUP


# SETTING UP PERSONAL ENGINE EXE
add_executable(Raycasting
  src/main.cpp
  src/Maths.cpp
  src/Mesh.cpp
  src/Ray.cpp
  src/lodepng.cpp
  src/tinyobjloader/tiny_obj_loader.cc
)