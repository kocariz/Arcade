#include "libncurses.h"

extern "C" IDisplayModule* create()
{
    return new Libncurses;
}

extern "C" int destroy()
{
    return 0;
}

Libncurses::Libncurses() {
    _name = "ncurses";
    displayMap.insert(std::make_pair('A', &Libncurses::printPlayer));
    displayMap.insert(std::make_pair('0', &Libncurses::printWall));
    displayMap.insert(std::make_pair('1', &Libncurses::printWall));
    displayMap.insert(std::make_pair('2', &Libncurses::printWall));
    displayMap.insert(std::make_pair('3', &Libncurses::printWall));
    displayMap.insert(std::make_pair('4', &Libncurses::printWall));
    displayMap.insert(std::make_pair('5', &Libncurses::printWall));
    displayMap.insert(std::make_pair('7', &Libncurses::printBlank));
    displayMap.insert(std::make_pair('8', &Libncurses::printFood));
}

void Libncurses::init()
{
    initscr();
    erase();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    curs_set(0);
    if (has_colors()) {
        start_color();
        init_pair(WALL, COLOR_CYAN, COLOR_CYAN);
        init_pair(BLANK, COLOR_WHITE, COLOR_WHITE);
        init_pair(PLAYER, COLOR_RED, COLOR_RED);
        init_pair(FOOD, COLOR_BLUE, COLOR_BLUE);
    }
}

void Libncurses::stop()
{
    endwin();
}

const std::string &Libncurses::getName() const
{
    return _name;
}

bool Libncurses::isActive()
{
    return false;
}

void Libncurses::refresh()
{
}

char Libncurses::getInput(bool input)
{
    int ch = getch();
    if (ch == KEY_UP)
        return KEYUP;
    if (ch == KEY_DOWN)
        return KEYDOWN;
    if (ch == KEY_ENTER || ch == 10 || ch == 13) {
        return MOUSELEFT;
    }
    return ch;
}

void Libncurses::printLevel(array_t array, unsigned int height,
    unsigned int width
)
{
    int f = 0;
    int s = 0;

    for (std::vector<char> line : array) {
        for (char pixel : line) {
            auto it = displayMap.find(pixel);
            if (it == displayMap.end())
                continue;
            (this->*it->second)(s + 2, f + width);
            f++;
        }
        f = 0;
        s++;
    }
}

void Libncurses::printWall(int x, int y)
{
    if (has_colors())
        attron(COLOR_PAIR(WALL));
    mvprintw(x, y, "%c", WALL);
}

void Libncurses::printBlank(int x, int y)
{
    if (has_colors())
        attron(COLOR_PAIR(BLANK));
    mvprintw(x, y, "%c", BLANK);
}

void Libncurses::printPlayer(int x, int y)
{
    if (has_colors())
        attron(COLOR_PAIR(PLAYER));
    mvprintw(x, y, "%c", PLAYER);
}

void Libncurses::printFood(int x, int y)
{
    if (has_colors())
        attron(COLOR_PAIR(FOOD));
    mvprintw(x, y, "%c", FOOD);
}

void Libncurses::initMenu()
{
    refresh();
    mvprintw(LINES / 4, COLS / 3, " _______  _______  _______  _______  ______   _______ ");
    mvprintw(LINES / 4 + 1, COLS / 3, "(  ___  )(  ____ )(  ____ \\(  ___  )(  __  \\ (  ____ \\");
    mvprintw(LINES / 4 + 2, COLS / 3, "| (   ) || (    )|| (    \\/| (   ) || (  \\  )| (    \\/");
    mvprintw(LINES / 4 + 3, COLS / 3, "|  ___  ||     __)| |      |  ___  || |   | ||  __)    ");
    mvprintw(LINES / 4 + 4, COLS / 3, "| (   ) || (\\ (   | |      | (   ) || |   ) || (      ");
    mvprintw(LINES / 4 + 5, COLS / 3, "| )   ( || ) \\ \\__| (____/\\| )   ( || (__/  )| (____/\\ ");
    mvprintw(LINES / 4 + 6, COLS / 3, "|/     \\||/   \\__/(_______/|/     \\|(______/ (_______/");
    mvprintw(LINES / 2 , COLS / 3 + 3, "GAME:");
    mvprintw(LINES / 2 + 1, COLS / 3 + 3, "LIBRARY:");
    mvprintw(LINES / 2 + 9, COLS / 2 - 20, "Press Enter to start playing");
}

void Libncurses::printInfo(std::string name, std::string lib, std::string game)
{
    mvprintw(LINES / 2, COLS / 2, lib.c_str());
    mvprintw(LINES / 2 + 1, COLS / 2, game.c_str());
}

bool Libncurses::getQuit() {
    return _quit;
}

std::string Libncurses::getUsername()
{
    return std::string();
}

void Libncurses::clearScreen()
{
    if (has_colors()) {
        attroff(COLOR_PAIR(FOOD));
        attroff(COLOR_PAIR(PLAYER));
        attroff(COLOR_PAIR(WALL));
        attroff(COLOR_PAIR(BLANK));
    }
    erase();
    refresh();
}
