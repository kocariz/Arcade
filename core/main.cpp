/*
** EPITECH PROJECT, 2021
** B-OOP-400-BAR-4-1-arcade-oriol.moles-teiga
** File description:
** main
*/

#include <iostream>
#include <core.h>
#include <IGame.hpp>
#include "../game_libs/snake/include/snakeGame.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        utils::usagePrompt();
        return 84;
    }
    try {
        int i;
        Core core(av[1]);
        core.mainLoop();
    } catch (MainException &exception) {
        std::cout << "Error: " << exception.what();
        return 84;
    }

    return 0;
}
