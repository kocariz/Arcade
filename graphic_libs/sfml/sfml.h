/*
** EPITECH PROJECT, 2021
** globalProject
** File description:
** Created by aespejo,
*/
#ifndef GLOBALPROJECT_SFML_H
#define GLOBALPROJECT_SFML_H

#include "SFML/Graphics.hpp"
#include "iDisplayModule.hpp"
#include "inputs.h"

#define BACKGROUND_PATH "./resources/images/b4638aa66c9882cbb725d1adf0fed6b0.jpg"
#define FONTONE_PATH "./resources/font/OpenSans-Bold.ttf"
#define FONTTWO_PATH "./resources/font/OpenSans-Bold.ttf"
#define WIN_H 768
#define WIN_W 1366

class LibSFML : public IDisplayModule {
    typedef void (LibSFML::*fnc_ptr)(int x, int y);
    typedef std::map<char, fnc_ptr> map_t;
    public:
        LibSFML();
        ~LibSFML() override = default;
        bool isActive() override;
        void refresh() override;
        char getInput(bool) override;
        void printLevel(array_t array, unsigned int height, unsigned int width
        ) override;
        void initMenu() override;
        bool getQuit() override;
        void clearScreen() override;
    private:
        char manageMenu(sf::Event);
        void init() override;
        void stop() override;
        const std::string &getName() const override;
        sf::RenderWindow *_window;
        map_t _block_type;
        void drawBlackSquare(int x, int y);
        void drawWhiteSquare(int x, int y);
        void drawRedSquare(int x, int y);
        void drawBlueCircle(int x, int y);
        std::string getUsername() override;
        void printInfo(std::string, std::string, std::string) override;
        sf::Texture _background_image;
        sf::Sprite _background;
        sf::Font _fontOne;
        sf::Font _fontTwo;
        sf::Text _username_txt;
        sf::Text _lib_txt;
        sf::Text _game_txt;
        sf::Text _title;
    //void init(const array_t& array);
};

#endif //GLOBALPROJECT_SFML_H
