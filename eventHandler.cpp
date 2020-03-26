//
// Created by Tobias on 26.03.2020.
//
#include "eventHandler.h"
void eventHandler::checkMovementInput() {
    SDL_PumpEvents();

    if(keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP]){
        _direction = direction::UP;
    } else if(keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN]){
        _direction = direction::DOWN;
    } else if(keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT]){
        _direction = direction::RIGHT;
    } else if(keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT]){
        _direction = direction::LEFT;
    }
    getDirection();
}

void eventHandler::moveCharacter(SDL_Rect& coordinates, SDL_Texture*& texture, SDL_Renderer* tegnemann) {
    int speed = 1;
    if(keyStates[SDL_SCANCODE_TAB]){
        speed = 4;
    }
    if(_direction == direction::RIGHT)
    {
        coordinates.x += speed;
        texture = textureManager.createTexture("../Resources/Real_Pacman_RIGHT.png", tegnemann);
    } else if(_direction == direction::LEFT)
    {
        coordinates.x += -speed;
        texture = textureManager.createTexture("../Resources/Real_Pacman_LEFT.png", tegnemann);
    } else if(_direction == direction::UP)
    {
        coordinates.y += -speed;
        texture = textureManager.createTexture("../Resources/Real_Pacman_UP.png", tegnemann);
    } else if(_direction == direction::DOWN)
    {
        coordinates.y += speed;
        texture = textureManager.createTexture("../Resources/Real_Pacman_DOWN.png", tegnemann);
    }

     if(coordinates.x < 0){
        _direction = direction::NONE;
        coordinates.x = 1;
    }
    if(coordinates.y < 0) {
        _direction = direction::NONE;
        coordinates.y = 1;
    }
    if(coordinates.x > 768) {
        _direction = direction::NONE;
        coordinates.x = 767;
    }
    if (coordinates.y > 608){
        _direction = direction::NONE;
        coordinates.y = 607;
    }


}

void eventHandler::getDirection() {
    if(_direction == direction::UP){
        std::cout << "UP" << std::endl;
    } else if (_direction == direction::LEFT){
        std::cout << "LEFT" << std::endl;
    } else if (_direction == direction::RIGHT) {
        std::cout << "RIGHT" << std::endl;
    } else if (_direction == direction::DOWN){
        std::cout << "DOWN" << std::endl;
    } else if (_direction == direction::NONE) {
        std::cout << "NONE" << std::endl;
    }
}
