cmake_minimum_required(VERSION 3.15)

project(PacMan-GK-master)
INCLUDE(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS}  ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS}  )

add_executable(PacMan-GK-master main.cpp GameManager.h GameManager.cpp renderManager.cpp renderManager.h windowLoader.cpp windowLoader.h Map.cpp Map.h Obstacle.cpp Obstacle.h GameCharacter.cpp GameCharacter.h Pacman.cpp Pacman.h Ghost.cpp Ghost.h RedGhost.cpp RedGhost.h PinkGhost.cpp PinkGhost.h OrangeGhost.cpp OrangeGhost.h BlueGhost.cpp BlueGhost.h scoreDisplay.cpp scoreDisplay.h)
target_link_libraries(PacMan-GK-master ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}  ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})