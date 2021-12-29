#include <iostream>
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

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    ncwrap nc;

    Board board(22, 80);
    board.draw();
    board.move();
    board.draw();
    board.wait();
}