cmake_minimum_required(VERSION 3.15)

project(PacMan-GK-master)
INCLUDE(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

include_directories(${SDL2_INCLUDE_DIRS}  ${SDL2_IMAGE_INCLUDE_DIRS} )

add_executable(PacMan-GK-master main.cpp GameManager.h GameManager.cpp renderManager.cpp renderManager.h TextureManager.h TextureManager.cpp windowLoader.cpp windowLoader.h)
target_link_libraries(PacMan-GK-master ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})