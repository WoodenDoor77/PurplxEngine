cmake_minimum_required(VERSION 3.30.3)
project(Purplx)

include_directories(${CMAKE_SOURCE_DIR}/include/GLFW ${CMAKE_SOURCE_DIR}/include/Purplx ${CMAKE_SOURCE_DIR}/include)

add_executable(Purplx src/main.c src/Purplx.c src/Mesh.c lib/glad.c)

find_package(glfw3 REQUIRED)

target_link_libraries(Purplx PRIVATE glfw GL)