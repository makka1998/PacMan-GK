cmake_minimum_required(VERSION 3.15)

project(PacMan-GK)
INCLUDE(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS}  ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS}  )

add_executable(PacMan-GK main.cpp Managers/GameManager.h Managers/GameManager.cpp Managers/RenderManager.cpp Managers/RenderManager.h Managers/WindowLoader.cpp Managers/WindowLoader.h Map.cpp Map.h Tile.cpp Tile.h Characters/GameCharacter.cpp Characters/GameCharacter.h Characters/Pacman.cpp Characters/Pacman.h Characters/Ghost.cpp Characters/Ghost.h Characters/RedGhost.cpp Characters/RedGhost.h Characters/PinkGhost.cpp Characters/PinkGhost.h Characters/OrangeGhost.cpp Characters/OrangeGhost.h Characters/BlueGhost.cpp Characters/BlueGhost.h Managers/TextManager.cpp Managers/TextManager.h Managers/CollisionManager.cpp Managers/CollisionManager.h Managers/MovementManager.cpp Managers/MovementManager.h Managers/SoundManager.cpp Managers/SoundManager.h)
target_link_libraries(PacMan-GK ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}  ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})