/*
** EPITECH PROJECT, 2021
** B-OOP-400-BAR-4-1-arcade-oriol.moles-teiga
** File description:
** Utils
*/

#include "utils.hpp"

void utils::usagePrompt()
{
    std::cout << "USAGE" << std::endl;
    std::cout << "./arcade [graphical library]" << std::endl;
    std::cout << "Possible graphical libraries:" << std::endl;
    std::cout << "\t- lib/arcade_sfml.so" << std::endl;
    std::cout << "\t- lib/arcade_sdl2.so" << std::endl;
    std::cout << "\t- lib/arcade_ncurses.so" << std::endl;
}