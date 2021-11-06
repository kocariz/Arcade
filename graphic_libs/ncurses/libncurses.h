#ifndef LIB1_LIBRARY_H
#define LIB1_LIBRARY_H

#include <ncurses.h>
#include <map>
#include "iDisplayModule.hpp"
#include <iostream>
#include "exception.hpp"

#define WALL '#'
#define BLANK ' '
#define PLAYER 'P'
#define FOOD 'F'

class Libncurses : public IDisplayModule {
    public:
        Libncurses();
        ~Libncurses() override = default;
        bool isActive() override;
        void refresh() override;
        char getInput(bool) override;
        void printLevel(array_t array, unsigned int height, unsigned int width
        ) override;
        void initMenu() override;
        void clearScreen() override;
        bool getQuit() override;
        std::string getUsername() override;
        void printInfo(std::string, std::string, std::string) override;
    private:
        void init() override;
        void stop() override;
        const std::string &getName() const override;

        void printWall(int x, int y);
        void printBlank(int x, int y);
        void printPlayer(int x, int y);
        void printFood(int x, int y);

        typedef void (Libncurses::*fnc_ptr)(int, int);
        std::map<char, fnc_ptr> displayMap;
};

#endif //LIB1_LIBRARY_H
