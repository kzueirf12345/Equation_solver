cmake_minimum_required(VERSION 3.5.0)
project(mygame VERSION 0.1.0 LANGUAGES C)

set (CMAKE_C_STANDARD 23)

find_package(SDL2 REQUIRED)
if (APPLE)
    find_package(SDL2_ttf REQUIRED)
endif()

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR})

add_executable(mygame main.c
    classes/list/list.c
    classes/my_string/my_string.c
    classes/errors/errors.c
    classes/render/render.c
    classes/constants/constants.c
)
if (APPLE)
    target_link_libraries(mygame PRIVATE ${SDL2_LIBRARIES} SDL2_ttf::SDL2_ttf)
else()
    target_link_libraries(mygame PRIVATE ${SDL2_LIBRARIES} SDL2_ttf)
endif()