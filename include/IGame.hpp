/*
** EPITECH PROJECT, 2021
** globalProject
** File description:
** Created by aespejo,
*/
#ifndef GLOBALPROJECT_IGAME_HPP
#define GLOBALPROJECT_IGAME_HPP

#include <vector>
#include <algorithm>
#include "../game_libs/snake/include/player.hpp"
#include <set>

#define VERTICAL_LINE '0'
#define HORIZONTAL_LINE '1'
#define UPPER_LEFT_CORNER '2'
#define UPPER_RIGHT_CORNER '3'
#define LOWER_RIGHT_CORNER '4'
#define LOWER_LEFT_CORNER '5'
#define EMPTY_SPACE '7'
#define HEAD 'A'

typedef std::vector<std::vector<char>> array_t;

class IGame {
    public:
        virtual ~IGame() = default;
        virtual void loadMap() = 0;
        virtual void update(char input) = 0;
        virtual array_t getArray() {return _array;};
        virtual void put(unsigned int y, unsigned int x, char item) = 0;
        virtual Player* getPlayer() {return _player;};
        virtual bool isGameOver() const = 0;

    protected:
        std::string _name;
        array_t _array;
        Player *_player;
        std::set<char>SOLID_OBJECT = {VERTICAL_LINE, HORIZONTAL_LINE, HEAD};
};

#endif //GLOBALPROJECT_IGAME_HPP
