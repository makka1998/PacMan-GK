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
    }else if(keyStates[SDL_SCANCODE_ESCAPE]){
       closeGame=true;
    }
    //getDirection();
}

void eventHandler::moveCharacter(SDL_Rect& coordinates,SDL_Texture*& texture, SDL_Renderer* tegnemann) {
    int speed = 1;
    if(keyStates[SDL_SCANCODE_TAB]){
        speed = 4;
    }
    if(_direction == direction::RIGHT)
    {
        coordinates.x += speed;
        texture = IMG_LoadTexture(tegnemann, "../Resources/Real_Pacman_RIGHT.png");
    } else if(_direction == direction::LEFT)
    {
        coordinates.x += -speed;
        texture = IMG_LoadTexture(tegnemann, "../Resources/Real_Pacman_LEFT.png");
    } else if(_direction == direction::UP)
    {
        coordinates.y += -speed;
        texture = IMG_LoadTexture(tegnemann, "../Resources/Real_Pacman_UP.png");
    } else if(_direction == direction::DOWN)
    {
        coordinates.y += speed;
        texture = IMG_LoadTexture(tegnemann, "../Resources/Real_Pacman_DOWN.png");
    }

    //Checking to see if player leaves screen.
     if(coordinates.x < 0){
        _direction = direction::NONE;
        coordinates.x = 1;
    }
    if(coordinates.y < 0) {
        _direction = direction::NONE;
        coordinates.y = 1;
    }
    if(coordinates.x > 868) {
        _direction = direction::NONE;
        coordinates.x = 867;
    }
    if (coordinates.y > 968){
        _direction = direction::NONE;
        coordinates.y = 967;
    }


}

direction eventHandler::getDirection() {
    if(_direction == direction::UP){
        last_direction = direction::UP;
        return _direction;
        std::cout << "UP" << std::endl;
    } else if (_direction == direction::LEFT){
        last_direction = direction::LEFT;
        return _direction;
        std::cout << "LEFT" << std::endl;
    } else if (_direction == direction::RIGHT) {
        last_direction = direction::RIGHT;
        return _direction;
        std::cout << "RIGHT" << std::endl;
    } else if (_direction == direction::DOWN){
        last_direction = direction::DOWN;
        return _direction;
        std::cout << "DOWN" << std::endl;
    } else if (_direction == direction::NONE) {
        return _direction;
        std::cout << "NONE" << std::endl;
    }
}

void eventHandler::setDirection(direction dir){
    _direction = dir;
}
