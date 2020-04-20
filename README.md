# PG4401 Programming Home Exam 2020

##
Msys Command Lines to install the SDL Packages for Clion
~~~~
pacman -S mingw-w64-x86_64-toolchain
pacman -S mingw-w64-x86_64-SDL2
pacman -S mingw-w64-x86_64-SDL2_ttf
pacman -S mingw-w64-x86_64-SDL2_mixer
pacman -S mingw-w64-x86_64-SDL2_image
~~~~

## CmakeLists
cmake_minimum_required(VERSION 3.15)
project(PacMan-GK)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
INCLUDE(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
include_directories(${SDL2_INCLUDE_DIRS}  ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS}  )
add_executable(PacMan-GK main.cpp Managers/GameManager.h Managers/GameManager.cpp Managers/RenderManager.cpp Managers/RenderManager.h 
Managers/WindowLoader.cpp Managers/WindowLoader.h Map.cpp Map.h Tile.cpp Tile.h Characters/GameCharacter.cpp Characters/GameCharacter.h Characters/Pacman.cpp Characters/Pacman.h 
Characters/Ghost.cpp Characters/Ghost.h Characters/Ghosts/RedGhost.cpp Characters/Ghosts/RedGhost.h Characters/Ghosts/PinkGhost.cpp Characters/Ghosts/PinkGhost.h 
Characters/Ghosts/OrangeGhost.cpp Characters/Ghosts/OrangeGhost.h Characters/Ghosts/BlueGhost.cpp Characters/Ghosts/BlueGhost.h Managers/TextManager.cpp Managers/TextManager.h 
Managers/CollisionManager.cpp Managers/CollisionManager.h Managers/MovementManager.cpp Managers/MovementManager.h Managers/SoundManager.cpp Managers/SoundManager.h)
target_link_libraries(PacMan-GK ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}  ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})
