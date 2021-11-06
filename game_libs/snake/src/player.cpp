/*
** EPITECH PROJECT, 2021
** globalProject
** File description:
** Created by aespejo,
*/
#include "../include/player.hpp"

int Player::getDirection() const
{
    return _direction;
}

void Player::setDirection(int direction)
{
    _direction = direction;
}

int Player::getX() const
{
    return _x;
}

int Player::getY() const
{
    return _y;
}

void Player::setPosition(int y, int x)
{
    _y = y;
    _x = x;
}

void Player::move()
{
    auto it = _map.find(_direction);
    if (it == _map.end())
        exit(84);
    (this->*it->second)();
}

void Player::moveUP()
{
    _y--;
}

void Player::moveDOWN()
{
    _y++;
}

void Player::moveLEFT()
{
    _x--;
}

void Player::moveRIGHT()
{
    _x++;
}

Player::Player()
{
    _map.insert(std::make_pair(UP, &Player::moveUP));
    _map.insert(std::make_pair(DOWN, &Player::moveDOWN));
    _map.insert(std::make_pair(LEFT, &Player::moveLEFT));
    _map.insert(std::make_pair(RIGHT, &Player::moveRIGHT));
}

void Player::turnLeft()
{
    _direction--;
    if (_direction < 1)
        _direction = 4;
}

void Player::turnRight()
{
    _direction++;
    if (_direction > 4)
        _direction = 1;
}