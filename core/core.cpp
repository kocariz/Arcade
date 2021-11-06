/*
** EPITECH PROJECT, 2021
** globalProject
** File description:
** Created by aespejo,
*/

#include "core.h"

void Core::loadlib(const std::string& lib_path, const std::string &active_path)
{
    IDisplayModule *lib;
    typedef IDisplayModule* (*fptr)();
    fptr func;
    std::string fullPath = LIBRARY_PATH + lib_path;
    void *handle = dlopen(fullPath.c_str() , RTLD_LAZY);

    if (!handle) {
        std::cout << dlerror() << std::endl;
        return;
    }
    dlerror();
    func = (fptr)dlsym(handle, "create");
    lib = (IDisplayModule*)func();
    if (active_path.find(lib_path) != std::string::npos)
        _activeGfx = lib;
    _libs.push_back(lib);
}

const std::vector<IDisplayModule *> &Core::getLibs() const
{
    return _libs;
}

Core::Core(const std::string& lib)
{
    _i = getNumLib(lib);
    _key = 0;
    _activeGfx = nullptr;
    _activeGame = nullptr;
    loadlib(SFML_FILE, lib);
    loadlib(SDL2_FILE, lib);
    loadlib(NCURSES_FILE, lib);
    loadgame(NIBBLER_PATH);
}

IDisplayModule *Core::getActiveGfx() const
{
    return _activeGfx;
}

void Core::loadgame(const std::string &game_path)
{
    IGame *game;
    typedef IGame* (*fptr)();
    fptr func;
    void *handle = dlopen(game_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cout << dlerror() << std::endl;
        return;
    }
    dlerror();
    func = (fptr)dlsym(handle, "create");
    game = (IGame*)func();
    _activeGame = game;
    _games.push_back(game);
}

const std::vector<IGame *> &Core::getGames() const
{
    return _games;
}

int Core::getNumLib(std::string lib)
{
    std::ifstream my_file(lib);

    if (my_file.good()) {
        if (lib.find(SFML_FILE) != std::string::npos)
            return 0;
        else if (lib.find(SDL2_FILE) != std::string::npos)
            return 1;
        else if (lib.find(NCURSES_FILE) != std::string::npos)
            return 2;
    }
    throw MainException("Incorrect or corrupt library\n");
}

void Core::gameLoop()
{
    _activeGame->update(_key);
    _activeGfx->printLevel(_activeGame->getArray(), 10, 10);
    if (_activeGfx->getQuit())
        _running = false;
    if (_activeGame->isGameOver()) {
        _activeGfx->clearScreen();
        _menu = true;
        _activeGame = nullptr;
        resetGames();
    }
}

void Core::mainLoop()
{
    if (_activeGfx == nullptr)
        throw MainException("No library has been found.\n");
    _activeGfx->init();
    while (_running) {
        _key = _activeGfx->getInput(_menu);
        sepEvents();
        if (_menu)
            menuLoop();
        else
            gameLoop();
        _activeGfx->refresh();
    }
    _activeGfx->stop();
}

void Core::menuLoop()
{
    _name = _activeGfx->getUsername();
    _activeGfx->initMenu();
    _activeGfx->printInfo(_name, _activeGfx->getName(), "nibbler");
    if (_activeGfx->getQuit())
        _running = false;
    if (_key == '1' || _key == MOUSELEFT) {
        _activeGfx->clearScreen();
        _activeGame = _games[0];
        _activeGame->loadMap();
        _menu = false;
    }
}
void Core::sepEvents()
{
    switch (_key) {
        case KEYUP:
            _i += 1;
            if (_i > 2)
                _i = 0;
            _activeGfx->stop();
            usleep(100000);
            _activeGfx = getLibs()[_i];
            _activeGfx->init();
            break;
        case KEYDOWN:
            _i -= 1;
            if (_i < 0)
                _i = 2;
            _activeGfx->stop();
            usleep(100000);
        _activeGfx = getLibs()[_i];
            _activeGfx->init();
            break;
    }
}

void Core::resetGames()
{
    _games.clear();
    loadgame(NIBBLER_PATH);
}
