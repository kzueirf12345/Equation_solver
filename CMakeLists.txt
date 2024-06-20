cmake_minimum_required(VERSION 3.5.0)
project(mygame VERSION 0.1.0 LANGUAGES C)

set (CMAKE_C_STANDARD 23)

find_package(SDL2 REQUIRED)
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

add_executable(mygame main.c list.c my_string.c)
target_link_libraries(mygame PRIVATE ${SDL2_LIBRARIES})