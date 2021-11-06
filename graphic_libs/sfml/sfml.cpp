/*
** EPITECH PROJECT, 2021
** globalProject
** File description:
** Created by aespejo,
*/

#include "sfml.h"

extern "C" IDisplayModule* create()
{
    return new LibSFML();
}

void LibSFML::init()
{
    _window = new sf::RenderWindow(sf::VideoMode(WIN_W, WIN_H), "");
}

void LibSFML::stop()
{
    _window->close();
}

const std::string &LibSFML::getName() const
{
    return _name;
}

bool LibSFML::isActive()
{
    return false;
}

void LibSFML::refresh()
{
    _window->display();
}

char LibSFML::getInput(bool input)
{
    sf::Event event{};
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window->close();
            _quit = true;
            return '\0';
        }
        if (input) {
            if (event.key.code == sf::Keyboard::Up)
                return KEYUP;
            if (event.key.code == sf::Keyboard::Down)
                return KEYDOWN;
            return manageMenu(event);
        }
        if (event.type == sf::Event::KeyPressed && input == false) {
            if (event.key.code == sf::Keyboard::Up)
                return KEYUP;
            if (event.key.code == sf::Keyboard::Down)
                return KEYDOWN;
            if (event.key.code == sf::Keyboard::W)
                return 'w';
            if (event.key.code == sf::Keyboard::S)
                return 's';
            if (event.key.code == sf::Keyboard::A)
                return 'a';
            if (event.key.code == sf::Keyboard::D)
                return 'd';
        }
    }
    return '\0';
}

void LibSFML::printLevel(array_t array, unsigned int height, unsigned int width)
{
    _window->clear();
    _block_type.insert(std::make_pair('7', &LibSFML::drawBlackSquare));
    _block_type.insert(std::make_pair('0', &LibSFML::drawWhiteSquare));
    _block_type.insert(std::make_pair('1', &LibSFML::drawWhiteSquare));
    _block_type.insert(std::make_pair('2', &LibSFML::drawWhiteSquare));
    _block_type.insert(std::make_pair('3', &LibSFML::drawWhiteSquare));
    _block_type.insert(std::make_pair('4', &LibSFML::drawWhiteSquare));
    _block_type.insert(std::make_pair('5', &LibSFML::drawWhiteSquare));
    _block_type.insert(std::make_pair('A', &LibSFML::drawRedSquare));
    _block_type.insert(std::make_pair('8', &LibSFML::drawBlueCircle));
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

LibSFML::LibSFML()
{
    _name = "sfml";
    _window = nullptr;
    if(!_background_image.loadFromFile(BACKGROUND_PATH))
        exit(46);
    _background.setTexture(_background_image);
    _fontOne.loadFromFile(FONTONE_PATH);
    _fontTwo.loadFromFile(FONTTWO_PATH);
    _title = sf::Text("ARCADE", _fontOne, 100);
    _username_txt = sf::Text("", _fontOne, 50);
    _game_txt = sf::Text("NIBBLER:\t PRESS 1\nPACMAN:\tPRESS 2", _fontOne, 50);
    sf::FloatRect textRect = _title.getLocalBounds();
    _title.setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);
    _username_txt.setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);
    _game_txt.setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);
    _title.setPosition(sf::Vector2f(WIN_W / 2.0f,WIN_H / 2.0f - 200));
    _game_txt.setPosition(sf::Vector2f(WIN_W / 2.0f,WIN_H / 2.0f + 150));
    _username_txt.setPosition(sf::Vector2f(WIN_W / 2.0f,WIN_H / 2.0f));
}

void LibSFML::drawBlackSquare(int x, int y)
{
    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(10,10));
    cell.setFillColor(sf::Color::Black);
    cell.setPosition(x, y);
    _window->draw(cell);
}

void LibSFML::drawWhiteSquare(int x, int y)
{
    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(10,10));
    cell.setFillColor(sf::Color::White);
    cell.setPosition(x, y);
    _window->draw(cell);
}

void LibSFML::drawRedSquare(int x, int y)
{
    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(10,10));
    cell.setFillColor(sf::Color::Red);
    cell.setPosition(x, y);
    _window->draw(cell);
}

void LibSFML::drawBlueCircle(int x, int y)
{
    sf::CircleShape cell;
    cell.setRadius(5);
    cell.setFillColor(sf::Color::Blue);
    cell.setPosition(x, y);
    _window->draw(cell);
}

void LibSFML::initMenu()
{
    _window->draw(_background);
    _window->draw(_username_txt);
    _window->draw(_lib_txt);
    _window->draw(_game_txt);
    _window->draw(_title);
}

bool LibSFML::getQuit()
{
    return _quit;
}

std::string LibSFML::getUsername()
{
    return _username;
}

void LibSFML::printInfo(std::string username, std::string lib, std::string game)
{
    _lib_txt.setString("Lib:\t\t" + lib);
    //_game_txt.setString("Game:\t\t" + game);
    _username_txt.setString("Player:\t\t" + username);
}

char LibSFML::manageMenu(sf::Event event)
{
    if (event.type == sf::Event::TextEntered) {
        int textSize = (int)_username.size();
        unsigned short unicode = event.text.unicode;
        if (unicode == '1' || unicode == '2')
            return (char)unicode;
        if (unicode == 8 && textSize > 0)
            _username.erase(textSize - 1, 1);
        if (isalpha(unicode))
            _username += (char)unicode;
    }
    return '\0';
}

void LibSFML::clearScreen()
{

}
