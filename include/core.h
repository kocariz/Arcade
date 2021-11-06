/*
** EPITECH PROJECT, 2021
** globalProject
** File description:
** Created by aespejo,
*/
#ifndef GLOBALPROJECT_CORE_H
#define GLOBALPROJECT_CORE_H

#include <cstring>
#include <vector>
#include <fstream>
#include "iDisplayModule.hpp"
#include "IGame.hpp"
#include <dlfcn.h>
#include <utils.hpp>
#include <exception.hpp>
#include <utils.hpp>
#include <exception.hpp>
#include <unistd.h>

#define NCURSES_FILE "arcade_ncurses.so"
#define SFML_FILE "arcade_sfml.so"
#define SDL2_FILE "arcade_sdl2.so"
#define NIBBLER_PATH "./lib/arcade_nibbler.so"
#define LIBRARY_PATH "./lib/"

class Core {
    public:
        Core(const std::string&);
        ~Core() = default;
        void mainLoop();

    private:
        const std::vector<IDisplayModule *> &getLibs() const;
        IDisplayModule *getActiveGfx() const;
        const std::vector<IGame *> &getGames() const;
        void loadlib(const std::string &lib_path, const std::string &active_path);
        void loadgame(const std::string &game_path);
        int getNumLib(std::string lib);
        void gameLoop();
        void menuLoop();
        void sepEvents();
        void resetGames();
        IDisplayModule *_activeGfx;
        IGame *_activeGame;
        std::vector<IDisplayModule*> _libs;
        std::vector<IGame*> _games;
        char _key;
        int _i;
        bool _menu = true;
        bool _game;
        bool _running = true;
        std::string _name;
};

#endif //GLOBALPROJECT_CORE_H
