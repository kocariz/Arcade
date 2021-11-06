#include "sdl.h"
#include <iostream>
#include "../ncurses/libncurses.h"

#define RED 255, 0, 0, 0.7
#define COLOR 104, 227, 165, 0.9
#define GREEN 0, 255, 0, 0.7
#define WHITE 255, 255, 255, 0
#define BLUE 0, 0, 255, 0.8
#define YELLOW 255, 255, 0, 1
#define BLACK 0, 0, 0, 1
#define CYAN 124, 196, 196, 1

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;

#define SQUARE_SIZE 10, 10

extern "C" IDisplayModule* create()
{
    return new LibSDL();
}

void LibSDL::init()
{
    _white = { 255, 255, 255 };
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
        _quit = true;
    TTF_Init();
    _window = SDL_CreateWindow("arcade",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    _render = SDL_CreateRenderer(_window, -1, 0);
    SDL_SetRenderDrawColor(_render, WHITE);
    _image = IMG_Load("./resources/images/b4638aa66c9882cbb725d1adf0fed6b0.jpg");
    _font = TTF_OpenFont(FONTONE_PATH, 50);
    _font_two = TTF_OpenFont(FONTTWO_PATH, 25);
    _texture_image = SDL_CreateTextureFromSurface(_render, _image);
}

const std::string &LibSDL::getName() const
{
    return _name;
}

bool LibSDL::isActive()
{
    return false;
}

void LibSDL::refresh()
{
}

char LibSDL::manageKeyFalse()
{
    switch (_event.key.keysym.sym) {
        case SDLK_UP:
            return KEYUP;
        case SDLK_DOWN:
            return KEYDOWN;
        case SDLK_BACKSPACE:
            if (_username.length() > 0)
                _username.pop_back();
            break;
        case SDLK_a:
            return 'a';
        case SDLK_w:
            return 'w';
        case SDLK_s:
            return 's';
        case SDLK_d:
            return 'd';
    }
    return '\0';
}

char LibSDL::manageKeyTrue()
{
    switch (_event.key.keysym.sym) {
        case SDLK_UP:
            return KEYUP;
        case SDLK_DOWN:
            return KEYDOWN;
        case SDLK_BACKSPACE:
            if (_username.length() > 0)
                _username.pop_back();
            return BACKSPACE;
    }
    return '\0';
}

char LibSDL::getInput(bool input)
{
    while( SDL_PollEvent(&_event)){
        switch (_event.type) {
            case SDL_QUIT:
                stop();
                _quit = true;
                break;
            case SDL_TEXTINPUT:
                if (input)
                    _username += (static_cast<char>(*_event.text.text));
                break;
            case SDL_KEYDOWN:
                if (input)
                    return manageKeyTrue();
                else
                    return manageKeyFalse();
            case SDL_MOUSEBUTTONDOWN:
                if(_event.button.button == SDL_BUTTON_LEFT){
                    SDL_GetMouseState(&_xMouse,&_yMouse);
                    if (_xMouse >= 400 && _xMouse <= 600 && _yMouse >= 550 && _yMouse <= 650 && input)
                        return MOUSELEFT;
                }
                return 0;
        }
    }
    return '\0';
}

void LibSDL::initMenu()
{
    SDL_RenderCopy(_render, _texture_image, nullptr, nullptr);
    displayText("ARCADE", { 350, 50, 300, 100 }, _font);
    displayText("Play", { 400, 550, 200, 100 }, _font);
    displayText("Username:", { 150, 200, 225, 50 }, _font_two);
    displayText("Game:", { 150, 300, 125, 50 }, _font_two);
    displayText("Lib:", { 150, 400, 125, 50 }, _font_two);
    displayText("Key Up -> Next Lib", { 50, 500, 250, 50 }, _font_two);
    displayText( "Key Down -> Prev Lib", { 50, 550, 300, 50 }, _font_two);
}

void LibSDL::printInfo(std::string username, std::string lib, std::string game)
{
    displayText(username.c_str(), { 600, 200, static_cast<int>((username.length() * 25)), 50 }, _font_two);
    displayText(lib.c_str(), { 600, 400, 125, 50 }, _font_two);
    displayText(game.c_str(), { 600, 300, 125, 50 }, _font_two);
    SDL_RenderPresent(_render);
}

bool LibSDL::getQuit() {
    return _quit;
}

void LibSDL::stop()
{
    SDL_DestroyWindow(_window);
    TTF_Quit();
    SDL_Quit();
}

void LibSDL::displayBlackSquare(int x, int y)
{
    SDL_Rect fillRect = {x, y, SQUARE_SIZE};
    SDL_SetRenderDrawColor(_render, BLACK);
    SDL_RenderFillRect(_render, &fillRect);
    SDL_RenderPresent(_render);
}

void LibSDL::displayWhiteSquare(int x, int y)
{
    SDL_Rect fillRect = {x, y, SQUARE_SIZE};
    SDL_SetRenderDrawColor(_render, WHITE);
    SDL_RenderFillRect(_render, &fillRect);
    SDL_RenderPresent(_render);
}

void LibSDL::displayRedSquare(int x, int y)
{
    SDL_Rect fillRect = {x, y, SQUARE_SIZE};
    SDL_SetRenderDrawColor(_render, RED);
    SDL_RenderFillRect(_render, &fillRect);
    SDL_RenderPresent(_render);
}

void LibSDL::printLevel(array_t array, unsigned int height, unsigned int width)
{
    //clearScreen();
    _block_type.insert(std::make_pair('7', &LibSDL::displayBlackSquare));
    _block_type.insert(std::make_pair('0', &LibSDL::displayWhiteSquare));
    _block_type.insert(std::make_pair('1', &LibSDL::displayWhiteSquare));
    _block_type.insert(std::make_pair('2', &LibSDL::displayWhiteSquare));
    _block_type.insert(std::make_pair('3', &LibSDL::displayWhiteSquare));
    _block_type.insert(std::make_pair('4', &LibSDL::displayWhiteSquare));
    _block_type.insert(std::make_pair('5', &LibSDL::displayWhiteSquare));
    _block_type.insert(std::make_pair('A', &LibSDL::displayRedSquare));
    _block_type.insert(std::make_pair('8', &LibSDL::displayBlueCircle));
    int x = 0;
    int y = 0;
    for (auto &i: array) {
        for (auto &e : i) {
            auto it = _block_type.find(e);
            if (it == _block_type.end())
                continue;
            (this->*it->second)(x, y);
            x += 10;
        }
        x = 0;
        y += 10;
    }
}

std::string LibSDL::getUsername()
{
    return _username;
}

LibSDL::LibSDL()
{
    _name = "sdl2";
    _window = nullptr;
    _render = nullptr;
}

void LibSDL::clearScreen()
{
    SDL_SetRenderDrawColor(_render, BLACK);
    SDL_RenderClear(_render);
    SDL_RenderPresent(_render);
}

void LibSDL::displayText(const char *text, SDL_Rect rect, TTF_Font *font)
{
    _text = TTF_RenderText_Solid(font, text, _white);
    _texture_text = SDL_CreateTextureFromSurface(_render, _text);
    SDL_RenderCopy(_render, _texture_text, nullptr, &rect);
}

void LibSDL::displayBlueCircle(int x, int y)
{
    SDL_Rect fillRect = {x, y, SQUARE_SIZE};
    SDL_SetRenderDrawColor(_render, BLUE);
    SDL_RenderFillRect(_render, &fillRect);
    SDL_RenderPresent(_render);
}
