/*
** EPITECH PROJECT, 2021
** Exception
** File description:
** Exception
*/

#include "exception.hpp"

MainException::MainException()
{
    exceptionMessage = "An exception has ocurred";
}

MainException::MainException(std::string str)
{
    exceptionMessage = str;
}

char const *MainException::what() const noexcept
{
    return exceptionMessage.c_str();
}