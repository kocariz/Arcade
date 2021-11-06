/*
** EPITECH PROJECT, 2021
** globalProject
** File description:
** Created by aespejo,
*/
#ifndef GLOBALPROJECT_PLAYER_HPP
#define GLOBALPROJECT_PLAYER_HPP

#include <map>

#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

class Player
{
    typedef void (Player::*fnc_ptr)();
    typedef std::map<int , fnc_ptr> map_t;
    public:
        Player();
        ~Player() = default;
        int getDirection() const;
        void setDirection(int direction);
        void turnLeft();
        void turnRight();
        int getX() const;
        int getY() const;
        void setPosition(int y, int x);
        void move();

    protected:
        map_t _map;
        void moveUP();
        void moveDOWN();
        void moveLEFT();
        void moveRIGHT();
        int _direction = 1;
        int _x = 5;
        int _y = 5;
};

#endif //GLOBALPROJECT_PLAYER_HPP
