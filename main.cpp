#include <iostream>
#include <ctime>
#include <ncurses.h>

#include "board.hpp"


class ncwrap
{
public:
    ncwrap(bool ec = true, bool cb = true) { 
        initscr(); 
        if (ec) noecho(); 
        if (cb) cbreak();
    }

    ~ncwrap() { endwin(); }
    void refresh() { ::refresh(); }
};

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned>(time(NULL)));
    std::string name;
    // std::cout << "What's your name? ";
    // std::cin >> name;
    name = "titane";
    ncwrap nc;

    Board board(name);
    while(1)
    {
        board.draw();
        board.move();
    }
}