cmake_minimum_required(VERSION 3.5)
project(GeoSim)
set (CMAKE_CXX_STANDARD 14)

#LINKING SHARED LIBRARIES
set( PROJECT_LINK_LIBS libGL.so.1)

#glfw library
set( GLFW_LINK_LIBS libglfw.so )

link_directories(/snap/gnome-3-26-1604/74/usr/lib/x86_64-linux-gnu/mesa/ /usr/local/lib/)

#ADDING INCLUDE DIRECTORIES
include_directories(/usr/local/include/)

add_executable(geosim main.cpp glad.c)

target_link_libraries(geosim ${PROJECT_LINK_LIBS} ${GLFW_LINK_LIBS} ${CMAKE_DL_LIBS})
