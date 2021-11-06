/*
** EPITECH PROJECT, 2021
** globalProject
** File description:
** Created by aespejo,
*/
#ifndef GLOBALPROJECT_SNAKEGAME_HPP
#define GLOBALPROJECT_SNAKEGAME_HPP

#include "IGame.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <exception.hpp>
#include <cmath>
#include <random>

#define HEAD 'A'
#define FOOD '8'

#define IS_WALL 1
#define IS_FOOD 2
#define IS_EMPTY 3

class SnakeGame : public IGame {
    public:
        SnakeGame();
        ~SnakeGame() = default;
        void put(unsigned int y, unsigned int x, char item) override;
        void createMap(unsigned int width, unsigned int height);
        void loadMap() override;
        array_t getArray() override;
        void update(char input) override;
        bool isGameOver() const override;

    private:
    struct point {
        int x;
        int y;
        bool operator==(const point &rhs) const;
        bool operator!=(const point &rhs) const;
    };
    int height = 50;
        int width = 50;
        void generateFood();
        bool game_over;
        int check_ahead();
        int check_pos(int x, int y);
        const float num_sec = 0.2;
        clock_t _current;
        clock_t _last;
        double _time_counter = 0;
        int _len;
        void SnakeLogic();
        std::map<char, int> movement_Input;
        std::vector<point> _snake;
};

#endif //GLOBALPROJECT_SNAKEGAME_HPP
